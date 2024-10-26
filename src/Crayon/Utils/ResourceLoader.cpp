#include "ResourceLoader.h"

#include "Crayon/Core/Logger.h"

namespace Crayon
{
    std::string ResourceLoader::LoadFileAsString(const std::string &fileName)
    {
        CRAYON_CORE_TRACE("Loading file from {}", fileName);

        std::ifstream file(fileName);
        std::string fileContent((std::istreambuf_iterator<char>(file)),
                                (std::istreambuf_iterator<char>()));
        file.close();

        auto extension = fileName.substr(fileName.find('.') + 1, fileName.length() - 1);

        if (extension == "png" || extension == "jpg")
        {
            CRAYON_CORE_TRACE("Loaded {} image from {}", extension, fileName);
        }
        else
        {
            CRAYON_CORE_TRACE("Loaded content from {}:\n{}", fileName, fileContent);
        }

        return fileContent;
    }
}