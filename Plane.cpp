#include "Plane.h"

Plane::Plane(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

glm::vec3 Plane::getNormalVector()
{
    return glm::normalize(glm::vec3(a, b, c));
}
