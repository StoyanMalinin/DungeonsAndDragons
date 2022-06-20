#include "Application.h"

#include <filesystem>
#include <fstream>

#include "GameLogic/FIleManagement/GameLogicFileManager.h"

#include "GameLogic/Entities/Player/WarriorPlayer.h"
#include "GameLogic/Entities/Player/HumanPlayer.h"
#include "GameLogic/Entities/Player/MagePlayer.h"
#include "GameLogic/Entities/Player/Player.h"

#include "GameLogic/Entities/Controllers/UIMoveController.h"
#include "GameLogic/Entities/Controllers/UIFightController.h"
#include "GameLogic/Entities/Controllers/OnlyDownMoveController.h"
#include "GameLogic/Entities/Controllers/UIItemManagerController.h"
#include "GameLogic/Entities/Controllers/UIPointsDistributionController.h"

#include "GameLogic/FightMaster.h"
#include "GameLogic/ItemExchangeMaster.h"

#include "GameLogic/Level.h"
#include "GameLogic/GameMap.h"

Application::Application() : Application(std::cin, std::cout)
{}

Application::Application(std::istream& is, std::ostream& os) : uih(is, os), state(ApplicationState::OK), backupFile("backup.txt")
{}

void Application::run()
{
	while (state == ApplicationState::OK)
	{
		Vector<String> tokens;
		uih.readAndParseCommand(tokens);

		try
		{
			executeCommand(tokens);
		}
		catch (std::logic_error& e)
		{
			uih.writeMessage(e.what());
		}
		catch (std::exception& e)
		{
			state = ApplicationState::ERROR;

			uih.writeMessage("Fatal error occured");
			uih.writeMessage(e.what());
		}
		catch (...)
		{
			state = ApplicationState::ERROR;
			uih.writeMessage("Unknown fatal error occured");
		}
	}

	if (state == ApplicationState::ERROR)
	{
		uih.writeMessage("A fatal error occured that prevented the application from running anymore");
	}
}


void Application::executeCommand(Vector<String>& tokens)
{
	if (tokens.getLen() == 0)
		throw std::logic_error("Invalid command!");

	if (tokens[0] == "ls") lsCommand(tokens);
	else if (tokens[0] == "exit") exitCommand(tokens);
	else if (tokens[0] == "generatePlayer") generatePlayerCommand(tokens);
	else if (tokens[0] == "generateLevel") generateLevelCommand(tokens);
	else if (tokens[0] == "dnd") dndCommand(tokens);
	else if (tokens[0] == "recover") recoverCommand(tokens);
	else if (tokens[0] == "changeBackupFile") changeBackupFileCommand(tokens);
	else throw std::logic_error("Invalid command!");
}

void Application::lsCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 > 1) throw std::logic_error("Invalid command! Too many arguments given!");

	String path = ".";
	if (tokens.getLen() - 1 == 1) path = tokens[1];

	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path.getData()))
		std::cout << entry.path() << std::endl;
}

void Application::exitCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 != 0)
		throw std::logic_error("Invalid command!");

	state = ApplicationState::QUIT;
}

void Application::generateLevelCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 != 1)
		throw std::logic_error("Invalid command!");

	std::ofstream f(tokens[1].getData());
	if (f.is_open() == false)
		throw std::logic_error("Cannot open the file!");

	int number = uih.requestInt("Please enter the level number (positive integer)", "(level number)");
	while (!(1<=number && number<=10))
		number = uih.requestInt("Please enter the level number (positive integer)", "(level number)");

	int seed = uih.requestInt("Please enter level seed", "(seed)");

	Level l(number, seed);
	l.serialize(f);

	f.close();
	if (f.is_open() == true) throw std::exception("Could not close the file!");
	if (f.bad() == true) throw std::exception("Could not close the file!");
}

void Application::generatePlayerCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 != 1)
		throw std::logic_error("Invalid command!");

	std::ofstream f(tokens[1].getData());
	if (f.is_open() == false)
		throw std::logic_error("Could not open the file!");

	String playerName;
	uih.requestTextLine("Please enter the name of your player", "(player name)", playerName);

	Vector<char> raceOptions;
	raceOptions.pushBack('w');
	raceOptions.pushBack('h');
	raceOptions.pushBack('m');

	uih.writeMessage("Enter your player type(Warrior(w)/Human(h)/Mage(m))");
	char race = uih.requestCharChoice(raceOptions);

	Player* pPtr = nullptr;
	if (race == 'w') pPtr = new WarriorPlayer(playerName, 0, 0, UIFightController(uih), UIItemManagerController(uih), OnlyDownMoveController(), UIPointsDistributionController(uih),
		                                   ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
	else if(race=='h') pPtr = new HumanPlayer(playerName, 0, 0, UIFightController(uih), UIItemManagerController(uih), OnlyDownMoveController(), UIPointsDistributionController(uih),
										   ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
	else if (race == 'm') pPtr = new MagePlayer(playerName, 0, 0, UIFightController(uih), UIItemManagerController(uih), OnlyDownMoveController(), UIPointsDistributionController(uih),
											 ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());
	SharedPtr<Player> p(pPtr);

	p->setWeapon(SharedPtr<Weapon>(new Weapon("Ordinary sword", 1, 0.2f)));
	p->setSpell(SharedPtr<Spell>(new Spell("Fire ball", 1, 0.2f)));

	p->serialize(f);
	f.close();
}

void Application::dndCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 != 2)
		throw std::logic_error("Invalid command");

	std::fstream fPlayer(tokens[1].getData(), std::ios::in);
	std::fstream fLevel(tokens[2].getData(), std::ios::in);

	if (fPlayer.is_open() == false || fLevel.is_open() == false)
		throw std::logic_error("Could not open the file!");

	Level* level = GameLogicFileManager::deserializeLevel(fLevel);
	Player* player = GameLogicFileManager::deserializePlayer(fPlayer, UIFightController(uih), UIItemManagerController(uih), UIMoveController(uih, level->getMap()), UIPointsDistributionController(uih),
														     ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

	LevelOutcome outcome = level->play(*player, &backupFile);
	
	if (outcome == LevelOutcome::PLAYER_DIED) uih.writeMessage("Player died");
	else uih.writeMessage("Level successfully completed");

	fPlayer.close();
	fLevel.close();
	if (fLevel.bad() == true || fPlayer.bad() == true)
		throw std::logic_error("Error while closing files!");

	fPlayer.open(tokens[1].getData(), std::ios::out | std::ios::trunc);
	if (player->isAlive() == true)
	{
		player->setPosition(0, 0);
		player->serialize(fPlayer);
	}

	delete level;
	delete player;
}

void Application::changeBackupFileCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 != 1)
		throw std::logic_error("Invalid command!");

	backupFile = tokens[1];
}

void Application::recoverCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 != 3)
		throw std::logic_error("Invalid command!");

	String& backup = tokens[1];
	String& playerFile = tokens[2], & levelFile = tokens[3];

	std::fstream f(backup.getData(), std::ios::in);
	if (f.is_open() == false)
		throw std::logic_error("Could not open the backup file");

	Level *level = GameLogicFileManager::deserializeLevel(f);
	Player* p = GameLogicFileManager::deserializePlayer(f, UIFightController(uih), UIItemManagerController(uih), UIMoveController(uih, level->getMap()), UIPointsDistributionController(uih),
														ItemExchangeMaster::getGlobalInstance(), FightMaster::getGlobalInstance());

	std::ofstream fPlayer(playerFile.getData());
	if(fPlayer.is_open()==false)
		throw std::logic_error("Could not open the new player file");
	p->serialize(fPlayer);

	std::ofstream fLevel(levelFile.getData());
	if (fLevel.is_open() == false)
		throw std::logic_error("Could not open the new level file");
	level->serialize(fLevel);

	f.close();
	fLevel.close();
	fPlayer.close();
	if (f.bad() == true || fLevel.bad() == true || fPlayer.bad() == true)
		throw std::exception("Error while closing files!");

	delete p;
	delete level;
}
