#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Ember
{
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* CurrentSession;
		std::ofstream OutputStream;
		int32_t ProfileCount;
	public:
		Instrumentor()
			: CurrentSession(nullptr), ProfileCount(0)
		{

		}

		void BeginSession(const std::string& name, const std::string& filepath = "results.json")
		{
			OutputStream.open(filepath);
			WriteHeader();
			CurrentSession = new InstrumentationSession{ name };
		}

		void EndSession()
		{
			WriteFooter();
			OutputStream.close();
			delete CurrentSession;
			CurrentSession = nullptr;
			ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result)
		{
			if (ProfileCount++ > 0)
				OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			OutputStream << "{";
			OutputStream << "\"cat\":\"function\",";
			OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			OutputStream << "\"name\":\"" << name << "\",";
			OutputStream << "\"ph\":\"X\",";
			OutputStream << "\"pid\":0,";
			OutputStream << "\"tid\":" << result.ThreadID << ",";
			OutputStream << "\"ts\":" << result.Start;
			OutputStream << "}";

			OutputStream.flush();
		}

		void WriteHeader()
		{
			OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			OutputStream.flush();
		}

		void WriteFooter()
		{
			OutputStream << "]}";
			OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	private:
		const char* Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> StartTimepoint;
		bool Stopped;
	public:
		InstrumentationTimer(const char* name)
			: Name(name), Stopped(false)
		{
			StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ Name, start, end, threadID });

			Stopped = true;
		}
	};
}

#define EM_PROFILE 0
#if EM_PROFILE
#define EM_PROFILE_BEGIN_SESSION(name, filepath) ::Ember::Instrumentor::Get().BeginSession(name, filepath)
#define EM_PROFILE_END_SESSION() ::Ember::Instrumentor::Get().EndSession()
#define EM_PROFILE_SCOPE(name) ::Ember::InstrumentationTimer timer##__LINE__(name);
#define EM_PROFILE_FUNCTION() EM_PROFILE_SCOPE(__FUNCSIG__)
#else
#define EM_PROFILE_BEGIN_SESSION(name, filepath)
#define EM_PROFILE_END_SESSION()
#define EM_PROFILE_SCOPE(name)
#define EM_PROFILE_FUNCTION()
#endif 