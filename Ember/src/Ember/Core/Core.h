#pragma once

#ifdef EM_PLATFORM_WINDOWS

#ifdef EM_BUILD_DLL

#define EMBER_API __declspec(dllexport)
#else
#define EMBER_API __declspec(dllimport)

#endif // EM_BUILD_DLL

#endif // EM_PLATFORM_WINDOWS

#ifdef EM_DEBUG

#define EM_ASSERT(x, ...) if (!(x)) { EM_LOG_ERROR("Error-Level Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); }
#define EM_FATAL_ASSERT(x, ...) if (!(x)) { EM_LOG_FATAL("Fatal-Level Assertion Failed! {0}", __VA_ARGS__); __debugbreak(); }
#else
#define EM_ASSERT(x, ...) 
#define EM_FATAL_ASSERT(x, ...) 

#endif // EM_DEBUG

#define BIT(x) (1 << x)