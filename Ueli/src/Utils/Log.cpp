#include "Utils/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Utils {

	std::shared_ptr<spdlog::logger> Logger::s_Logger;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Ueli.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_Logger = std::make_shared<spdlog::logger>("API", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_Logger);
		s_Logger->set_level(spdlog::level::trace);
		s_Logger->flush_on(spdlog::level::trace);
	}

	void Logger::Shutdown()
	{
		spdlog::drop(s_Logger->name());
		s_Logger.reset();
		s_Logger = nullptr;
	}

}