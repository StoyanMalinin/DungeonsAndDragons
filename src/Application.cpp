#include "Application.h"

#include <filesystem>

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
