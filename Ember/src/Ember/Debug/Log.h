#pragma once
#include "spdlog/spdlog.h"
#include "Ember/Core/Core.h"

namespace Ember
{
	class EMBER_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> EmberLogger;
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetEmberLogger() { return EmberLogger; }
	};
}

//Ember-Log Macros
#ifdef EM_DEBUG

#define EM_LOG_TRACE(...) ::Ember::Log::GetEmberLogger()->trace(__VA_ARGS__)
#define EM_LOG_DEBUG(...) ::Ember::Log::GetEmberLogger()->debug(__VA_ARGS__)
#define EM_LOG_INFO(...)  ::Ember::Log::GetEmberLogger()->info(__VA_ARGS__)
#define EM_LOG_WARN(...)  ::Ember::Log::GetEmberLogger()->warn(__VA_ARGS__)
#define EM_LOG_ERROR(...) ::Ember::Log::GetEmberLogger()->error(__VA_ARGS__)
#define EM_LOG_FATAL(...) ::Ember::Log::GetEmberLogger()->critical(__VA_ARGS__)

#endif // EM_DEBUG

#ifdef EM_RELEASE

#define EM_LOG_TRACE(...) 
#define EM_LOG_DEBUG(...) 
#define EM_LOG_INFO(...) 
#define EM_LOG_WARN(...)  ::Ember::Log::GetEmberLogger()->warn(__VA_ARGS__)
#define EM_LOG_ERROR(...) ::Ember::Log::GetEmberLogger()->error(__VA_ARGS__)
#define EM_LOG_FATAL(...) ::Ember::Log::GetEmberLogger()->critical(__VA_ARGS__)

#endif // EM_RELEASE

#ifdef EM_DIST

#define EM_LOG_TRACE(...) 
#define EM_LOG_DEBUG(...) 
#define EM_LOG_INFO(...) 
#define EM_LOG_WARN(...) 
#define EM_LOG_ERROR(...) 
#define EM_LOG_FATAL(...) 

#endif // EM_DIST