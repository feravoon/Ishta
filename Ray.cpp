#include "Ray.h"

glm::vec3 Ray::getPosAtRange(float range)
{ 
    return initPoint + range * unitVector;
}


Ray::Ray(glm::vec3 initPoint, glm::vec2 angles)
{
    this->initPoint = initPoint;
    this->unitVector = glm::normalize(glm::vec3(cos(angles[0]),sin(angles[0]),tan(angles[1])));
}

Ray::Ray(glm::vec3 initPoint, glm::vec3 unitVector)
{
    this->initPoint = initPoint;
    this->unitVector = unitVector;
}

Ray::Ray()
{
    initPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    unitVector = glm::vec3(0.0f, 0.0f, 1.0f);
}
