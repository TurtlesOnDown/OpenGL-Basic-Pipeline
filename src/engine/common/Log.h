#pragma once

#include <spdlog/spdlog.h>

class Log {
public:
	static void init();

	template<typename... Args>
	static void trace(const char *fmt, const Args &... args) {
		if (initialized) {
			Log::GetLogger()->trace(fmt, args...);
		}
		else {
			std::cout << "ERROR::Initialize Logger";
		}
	}

	template<typename... Args>
	static void info(const char *fmt, const Args &... args) {
		if (initialized) {
			Log::GetLogger()->info(fmt, args...);
		}
		else {
			std::cout << "ERROR::Initialize Logger";
		}
	}

	template<typename... Args>
	static void warn(const char *fmt, const Args &... args) {
		if (initialized) {
			Log::GetLogger()->warn(fmt, args...);
		}
		else {
			std::cout << "ERROR::Initialize Logger";
		}
	}

	template<typename... Args>
	static void error(const char *fmt, const Args &... args) {
		if (initialized) {
			Log::GetLogger()->error(fmt, args...);
		}
		else {
			std::cout << "ERROR::Initialize Logger";
		}
	}

	template<typename... Args>
	static void critical(const char *fmt, const Args &... args) {
		if (initialized) {
			Log::GetLogger()->critical(fmt, args...);
		}
		else {
			std::cout << "ERROR::Initialize Logger";
		}
	}

	inline static std::shared_ptr<spdlog::logger> &GetLogger() { return logger; }
private:
	static bool initialized;
	static std::shared_ptr<spdlog::logger> logger;
};

#define LOG_TRACE(...) Log::trace(__VA_ARGS__)
#define LOG_INFO(...) Log::info(__VA_ARGS__)
#define LOG_WARN(...) Log::warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::error(__VA_ARGS__)
#define LOG_CRITICAL(...) Log::critical(__VA_ARGS__)