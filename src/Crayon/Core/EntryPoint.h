#pragma once

#include "Base.h"
#include "Logger.h"

int main(int argc, char **argv)
{
    Crayon::Logger::Initialize();
    CRAYON_CORE_TRACE("Creating application...");
    auto *app = Crayon::CreateApplication();
    app->Run();
    return EXIT_SUCCESS;
}