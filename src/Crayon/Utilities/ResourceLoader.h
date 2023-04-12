#pragma once

#include "crypch.h"

namespace Crayon
{
    class ResourceLoader
    {
    public:
        static std::string LoadFileAsString(const std::string& fileName);
    };
}

