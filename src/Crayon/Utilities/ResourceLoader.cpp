#include "ResourceLoader.h"

#include "Crayon/Core/Logger.h"

namespace Crayon
{
    std::string ResourceLoader::LoadFileAsString(const std::string &fileName)
    {
        CRAYON_CORE_TRACE("LOADING FILE FROM {}", fileName);
        std::ifstream file(fileName);
        std::string fileContent((std::istreambuf_iterator<char>(file)),
                                (std::istreambuf_iterator<char>()));
        file.close();
        return fileContent;
    }
}