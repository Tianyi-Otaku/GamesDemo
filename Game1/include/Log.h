#pragma once
#include<iostream>
#include <fstream>
#include<ctime>
#include <direct.h>

class Log {
#ifdef _DEBUG
#define LOG_DEBUG true
#else
#define LOG_DEBUG false
#endif
#define LOG_LEVEL 0
	// 0 INFO
	// 1 WARN
	// 2 ERROR
#define LOG_FILE true
	std::string dirPath = "Log";
	std::string LogPath = "日志信息.txt";
	//shell 定义
	const std::string none = "\033[0m";
	const std::string red = "\033[31m";
	const std::string green = "\033[32m";
	const std::string yellow = "\033[33m";
	const std::string blue = "\033[34m";
public:
	Log();
	std::string currentTime();
	void info(std::string data);
	void warn(std::string data);
	void error(std::string data);
};
extern Log logs;