#pragma once

#include "Base.h"
#include <spdlog/spdlog.h>

namespace Crayon::Core
{
    class Logger
    {
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

        Logger() = default;

        ~Logger() = default;

    public:
        static void Initialize();

        static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }

        static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    };
}

// Core Log Macros
#define CRAYON_CORE_FATAL(...)    ::Crayon::Core::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define CRAYON_CORE_ERROR(...)    ::Crayon::Core::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CRAYON_CORE_WARN(...)     ::Crayon::Core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CRAYON_CORE_INFO(...)     ::Crayon::Core::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CRAYON_CORE_TRACE(...)    ::Crayon::Core::Logger::GetCoreLogger()->trace(__VA_ARGS__)

// Core Log Macros
#define CRAYON_FATAL(...)        ::Crayon::Core::Logger::GetClientLogger()->critical(__VA_ARGS__)
#define CRAYON_ERROR(...)        ::Crayon::Core::Logger::GetClientLogger()->error(__VA_ARGS__)
#define CRAYON_WARN(...)         ::Crayon::Core::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define CRAYON_INFO(...)         ::Crayon::Core::Logger::GetClientLogger()->info(__VA_ARGS__)
#define CRAYON_TRACE(...)        ::Crayon::Core::Logger::GetClientLogger()->trace(__VA_ARGS__)