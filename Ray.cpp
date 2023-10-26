#include "Ray.h"

glm::vec3 Ray::getPosAtRange(float range)
{ 
    return initPoint + range * unitVector;
}

glm::vec3 Ray::intersectWithPlane(Plane &plane)
{
    float t = (-plane.d - plane.a*initPoint.x - plane.b*initPoint.y - plane.c*initPoint.z) / (plane.a*unitVector.x + plane.b*unitVector.y + plane.c*unitVector.z);

    if(t<=0)
        t = MAXFLOAT;

    return getPosAtRange(t);
}

float Ray::angleToNormalOfPlane(Plane &plane)
{
    glm::vec3 normalVectorOfPlane = plane.getNormalVector();
    return acosf(glm::dot(this->unitVector, normalVectorOfPlane));
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
