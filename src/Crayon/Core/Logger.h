#pragma once

#include "Base.h"
#include <spdlog/spdlog.h>

namespace Crayon
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
#define CRAYON_CORE_FATAL(...)    ::Crayon::Logger::GetCoreLogger()->critical(__VA_ARGS__)
#define CRAYON_CORE_ERROR(...)    ::Crayon::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CRAYON_CORE_WARN(...)     ::Crayon::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CRAYON_CORE_INFO(...)     ::Crayon::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CRAYON_CORE_TRACE(...)    ::Crayon::Logger::GetCoreLogger()->trace(__VA_ARGS__)

// Core Log Macros
#define CRAYON_FATAL(...)        ::Crayon::Logger::GetClientLogger()->critical(__VA_ARGS__)
#define CRAYON_ERROR(...)        ::Crayon::Logger::GetClientLogger()->error(__VA_ARGS__)
#define CRAYON_WARN(...)         ::Crayon::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define CRAYON_INFO(...)         ::Crayon::Logger::GetClientLogger()->info(__VA_ARGS__)
#define CRAYON_TRACE(...)        ::Crayon::Logger::GetClientLogger()->trace(__VA_ARGS__)