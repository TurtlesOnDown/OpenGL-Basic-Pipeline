#include "Includes.h"

#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::logger;

void Log::init() {
	spdlog::set_pattern("%^[%T %d-%m-%Y] [%@] %v%$");
	logger = spdlog::stdout_color_mt("console");
	logger->set_level(spdlog::level::trace);
}