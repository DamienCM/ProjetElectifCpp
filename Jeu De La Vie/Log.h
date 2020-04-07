#pragma once
#include <fstream>
#include <chrono>

class Log {
public:
	int LogLevelError = 0;
	int LogLevelWarning = 1;
	int LogLevelInfo = 2;

private:
	int m_LogLevel = 2;
	std::ofstream mystream;



public:
	Log(const char* str) {
		mystream.open(str);
		mystream << "Debut du programme : " << std::endl;

	}
	void setLevel(int level) {
		m_LogLevel = level;
	}
	void Error(const char* str) {
		if (m_LogLevel >= LogLevelError) {
			time_t result = time(NULL);
			char date[26];
			ctime_s(date, sizeof date, &result);

			mystream << "[Error] : " << str << " at time " << date;
		}
	}
	void Warning(const char* str) {
		if (m_LogLevel >= LogLevelWarning) {
			time_t result = time(NULL);
			char date[26];
			ctime_s(date, sizeof date, &result);
			mystream << "[Warning] : " << str << " at time " << date;
		}
	}
	void Info(const char* str) {
		if (m_LogLevel >= LogLevelInfo) {
			time_t result = time(NULL);
			char date[26];
			ctime_s(date, sizeof date, &result);
			mystream << "[Info] : " << str << " at time " << date;
		}
	}

};
