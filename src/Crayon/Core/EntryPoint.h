#pragma once

#include "Base.h"
#include "Logger.h"

int main(int argc, char **argv)
{
    Crayon::Core::Logger::Initialize();
    CRAYON_CORE_TRACE("Creating application...");
    CreateApplication()->Run();
    return EXIT_SUCCESS;
}