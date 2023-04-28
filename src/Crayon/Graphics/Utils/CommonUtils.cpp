#include "CommonUtils.h"
#include "Crayon/Core/Logger.h"

namespace Crayon
{
    unsigned int CommonUtils::GetSizeOfType(GLenum type)
    {
        switch (type)
        {
            case GL_FLOAT:
                return sizeof(float);
            case GL_UNSIGNED_INT:
                return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE:
                return sizeof(unsigned char);
            default:
                CRAYON_CORE_ERROR("Invalid type!");
                return -1;
        }
    }
}