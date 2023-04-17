#pragma once

#include <Users/angelo/Dev/CXX/Crayon/vendor/glad/include/glad/glad.h>

namespace Crayon
{
    class CommonUtils
    {
    public:
        static unsigned int GetSizeOfType(GLenum type);
    };
} // Crayon
