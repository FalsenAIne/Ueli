#pragma once

#ifdef UELI_PLATFORM_WINDOWS
	#ifdef UELI_BUILD_DLL
		#define UELI_API __declspec(dllexport)
	#else
		#define UELI_API __declspec(dllimport)
	#endif
#else
	#error Building only supports Windows!
#endif

#define UELI_TRACE(...)         ::Utils::Logger::GetLogger()->trace(__VA_ARGS__)
#define UELI_INFO(...)          ::Utils::Logger::GetLogger()->info(__VA_ARGS__)
#define UELI_WARN(...)          ::Utils::Logger::GetLogger()->warn(__VA_ARGS__)
#define UELI_ERROR(...)         ::Utils::Logger::GetLogger()->error(__VA_ARGS__)
#define UELI_FATAL(...)		    ::Utils::Logger::GetLogger()->critical(__VA_ARGS__)

#define UELI_ASSERT(x, ...) { if(!(x)) { UELI_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }