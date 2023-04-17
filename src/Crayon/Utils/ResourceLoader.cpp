#include "ResourceLoader.h"

#include "Crayon/Core/Logger.h"

namespace Crayon
{
    std::string ResourceLoader::LoadFileAsString(const std::string &fileName, bool trace)
    {
        std::ifstream file(fileName);
        std::string fileContent((std::istreambuf_iterator<char>(file)),
                                (std::istreambuf_iterator<char>()));
        file.close();

        if (trace) CRAYON_CORE_TRACE("LOADED FILE FROM {}:\n{}", fileName, fileContent);
        return fileContent;
    }
}