#include "Log.h"

Log::Log(const std::string& message, LogFlags flag, bool includeTime)
{
	std::string logType;
	switch (flag)
	{
	case Log::INFO:    logType = "INFO";	break;
	case Log::WARNING: logType = "WARNING"; break;
	case Log::CRITICAL:logType = "CRITICAL";break;
	case Log::FATAL:   logType = "FATAL";	break;
	}
			
	std::string text = "[(" + logType + ")" + (includeTime ? Timer::getDateAndTime() : "") + "] - " + message + "\n";
	writeLog(text);
}

void Log::writeLog(const std::string& text)
{
	//mkdir if not exist
	if (!std::filesystem::is_directory("resources/logs"))
		std::filesystem::create_directory("resources/logs");
	std::string fileName ("resources/logs/log_MeshViewer.txt");
	std::fstream file;
	//set text append and binary
	file.open(fileName, std::ios::app | std::ios::binary);
	if(file.is_open())
		file << text;
	file.close();
}


