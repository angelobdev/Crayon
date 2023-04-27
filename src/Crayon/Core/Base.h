#pragma once

// DEFINITIONS

#if defined(_WIN32)
	#define CRAYON_PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define CRAYON_PLATFORM_APPLE
#else
	#error Crayon is only supported on Windows and macOS!
#endif