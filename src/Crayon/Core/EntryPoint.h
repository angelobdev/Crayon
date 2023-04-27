#pragma once

#include "Base.h"
#include "Logger.h"

int main(int argc, char **argv)
{
    Crayon::Logger::Initialize();
    auto *app = Crayon::CreateApplication();
    app->Run();
    return EXIT_SUCCESS;
}