#include "empch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Ember
{
	std::shared_ptr<spdlog::logger> Log::EmberLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%d/%m/%Y][%T] %n: %v%$");
		EmberLogger = spdlog::stdout_color_mt("EMBER");
		EmberLogger->set_level(spdlog::level::trace);
	}
}