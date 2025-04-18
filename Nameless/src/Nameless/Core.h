#pragma once

#ifdef NMLS_PLATFORM_WINDOWS
#if NMLS_DYNAMIC_LINK
	#ifdef NMLS_BUILD_DLL
		#define  __declspec(dllexport)
	#else
		#define  __declspec(dllimport)
	#endif
#else
	#define NAMELESS_API
#endif
#else
	#error Nameless only supports Windows
#endif

#ifdef NMLS_ENABLE_ASSERTS
	#define NMLS_ASSERT(x, ...) { if(!(x)) { NMLS_ERROR("Assertion failed: {0}", __VA_ARGS_); __debugbreak(); } }
	#define NMLS_CORE_ASSERT(x, ...) { if(!(x)) { NMLS_CORE_ERROR("Assertion failed: {0}", __VA_ARGS_); __debugbreak(); } }
#else
	#define NMLS_ASSERT(x, ...)
	#define NMLS_CORE_ASSERT(x, ...)
#endif

#define NMLS_BIND_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)