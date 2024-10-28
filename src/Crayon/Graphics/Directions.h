#pragma once

#include <glm/glm.hpp>

namespace Crayon::Graphics
{
    struct Directions
    {
        static const glm::vec3 UP;
        static const glm::vec3 DOWN;
        static const glm::vec3 LEFT;
        static const glm::vec3 RIGHT;
        static const glm::vec3 FORWARD;
        static const glm::vec3 BACK;
    };
}