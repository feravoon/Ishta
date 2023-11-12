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

glm::vec3 Plane::intersectWithRay(Ray &ray)
{
    float t = (-this->d - this->a*ray.initPoint.x - this->b*ray.initPoint.y - this->c*ray.initPoint.z) / (this->a*ray.unitVector.x + this->b*ray.unitVector.y + this->c*ray.unitVector.z);

    if(t<=0)
        t = MAXFLOAT;

    return ray.getPosAtRange(t);
}

float Plane::angleBetweenSurfaceNormalAndRay(Ray &ray, glm::vec3 posOnSurface)
{
    glm::vec3 normalVectorOfPlane = getNormalVector();
    return acosf(glm::dot(ray.unitVector, normalVectorOfPlane));
}

Ray Plane::getReflectedRay(Ray &incidentRay, glm::vec3 posOnSurface)
{
    glm::vec3 normalOnSurfacePos = this->getNormalVector();
    glm::vec3 reflectedUnitVector = incidentRay.unitVector - 2.0f*glm::dot(incidentRay.unitVector, normalOnSurfacePos) * normalOnSurfacePos;

    return Ray(posOnSurface+0.01f*reflectedUnitVector, reflectedUnitVector);
}
