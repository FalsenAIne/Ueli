#pragma once

#define UELI_TRACE(...)         ::Utils::Logger::GetLogger()->trace(__VA_ARGS__)
#define UELI_INFO(...)          ::Utils::Logger::GetLogger()->info(__VA_ARGS__)
#define UELI_WARN(...)          ::Utils::Logger::GetLogger()->warn(__VA_ARGS__)
#define UELI_ERROR(...)         ::Utils::Logger::GetLogger()->error(__VA_ARGS__)
#define UELI_FATAL(...)		    ::Utils::Logger::GetLogger()->critical(__VA_ARGS__)

#define UELI_ASSERT(x, ...) { if(!(x)) { UELI_FATAL("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }