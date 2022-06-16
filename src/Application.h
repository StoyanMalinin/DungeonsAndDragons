#ifndef __APPLICATION_H
#define __APPLICATION_H

#include <iostream>

#include "UI/UIHandler.h"

enum class ApplicationState
{
	QUIT,
	OK,
	ERROR,
};

class Application
{
private:
	UIHandler uih;
	ApplicationState state;

public:
	Application();
	Application(std::istream &is, std::ostream& os);
	Application(const Application& other) = delete;
	Application& operator =(const Application& other) = delete;

public:
	void run();

private:
	void executeCommand(Vector<String>& tokens);
	void lsCommand(Vector<String>& tokens);
	void exitCommand(Vector<String>& tokens);
};

#endif // !__APPLICATION_H
