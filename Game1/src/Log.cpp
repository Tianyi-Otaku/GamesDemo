#include "Log.h"

//Log logs;

Log logs;

	Log::Log(){
		
		bool flag = _mkdir(dirPath.c_str());
		time_t nowtime;
		time(&nowtime);
#pragma warning(suppress : 4996)
		tm* p = gmtime(&nowtime);
		char times[45];
		sprintf_s(times, "%04d年%02d月%02d日%02d时%02d分%02d秒 ", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
		LogPath = dirPath +"//" + times + LogPath;
	}
	std::string Log::currentTime(){
		time_t nowtime;
		time(&nowtime);
#pragma warning(suppress : 4996)
		tm* p = gmtime(&nowtime);
		char times[20];
		sprintf_s(times, "%04d_%02d_%02d %02d_%02d_%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
		return times;
	}
	void Log::info(std::string data) {
		if (LOG_DEBUG)
			if (LOG_LEVEL <= 0)
				if (LOG_FILE) {
					std::ofstream fout(LogPath, std::ios::app);
					if (!fout) std::cout << "Error 日志文件写入失败！" << std::endl;
					else fout << "[" << currentTime() << "]" << "[INFO] " << data << std::endl;
				}
				std::cout << blue << "[" << currentTime() << "]" << green << "[INFO] " << data << none << std::endl;

	}
	void Log::warn(std::string data) {
		if (LOG_DEBUG)
			if (LOG_LEVEL <= 1)
				if (LOG_FILE) {
					std::ofstream fout(LogPath, std::ios::app);
					if (!fout) std::cout << "Error 日志文件写入失败！" << std::endl;
					else fout << "[" << currentTime() << "]" << "[WARN] " << data << std::endl;
				}
				std::cout << blue << "[" << currentTime() << "]" << yellow << "[WARN] " << data << none << std::endl;

	}
	void Log::error(std::string data) {
		if (LOG_DEBUG)
			if (LOG_LEVEL <= 2)
				if (LOG_FILE) {
					std::ofstream fout(LogPath, std::ios::app);
					if (!fout) std::cout << "Error 日志文件写入失败！" << std::endl;
					else fout << "[" << currentTime() << "]" << "[ERROR] " << data << std::endl;
				}
				std::cout << blue << "[" << currentTime() << "]" << red << "[ERROR] " << data << none << std::endl;

	}
