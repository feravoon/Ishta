#include "Plane.h"

Plane::Plane(float a, float b, float c, float d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

Plane::Plane()
{
    this->a = 0.0f;
    this->b = 0.0f;
    this->c = 1.0f;
    this->d = 0.0f;
}

glm::vec3 Plane::getNormalVector()
{
    return glm::normalize(glm::vec3(a, b, c));
}
