#pragma once
#include "glm/vec3.hpp"
#include "glm/geometric.hpp"

class Plane {
    public:
        float a, b, c, d;
        Plane(float a, float b, float c, float d);
        Plane();
        glm::vec3 getNormalVector();
        Plane(glm::vec3 x0,glm::vec3 x1,glm::vec3 x2);
};