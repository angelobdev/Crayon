#pragma once

#ifdef _WIN32
#define CRAYON_PLATFORM_WINDOWS

#elifdef __APPLE__
#define CRAYON_PLATFORM_APPLE

#else
#error Crayon is only supported on Windows!

#endif
