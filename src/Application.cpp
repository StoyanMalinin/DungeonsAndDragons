#include "Application.h"

#include <filesystem>
#include <fstream>

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

Application::Application() : Application(std::cin, std::cout)
{}

Application::Application(std::istream& is, std::ostream& os) : uih(is, os), state(ApplicationState::OK)
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

void Application::generatePlayerCommand(Vector<String>& tokens)
{
	if (tokens.getLen() - 1 != 0)
		throw std::logic_error("Invalid command!");

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

	String filename;
	uih.requestTextLine("Please enter the name of the file, where you want to save your player", "(filename)", filename);

	std::ofstream f(filename.getData());
	if (f.is_open() == false)
		throw std::logic_error("Could not open the file!");

	p->serialize(f);
	f.close();
}
