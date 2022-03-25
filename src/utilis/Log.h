#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include "Timer.h"

class Log
{
public:
	enum LogFlags { INFO, WARNING, CRITICAL, FATAL, CONSOLE };
	explicit Log(const std::string& message, LogFlags flag = INFO, bool includeTime = true);
	~Log() = default;

	void writeLog(const std::string& text);
private:
	//bool imGuiLog;	-> write in imGuiDebug window
	//bool fileLog;		-> write in file window
};


