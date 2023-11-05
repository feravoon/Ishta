#include "Sphere.h"

glm::vec3 Sphere::intersectWithRay(Ray &ray)
{
    glm::vec3 L = this->center - ray.initPoint;
    float tca = glm::dot(L, ray.unitVector);
    // if (tca < 0) return false;
    float d2 = glm::dot(L, L) - tca * tca;
    if (d2 >  this->radiusSquared) return glm::vec3(INFINITY);
    float thc = sqrt(this->radiusSquared - d2);
    float t0 = tca - thc;
    float t1 = tca + thc;

    float t = t0;

    if (t0 > t1) t = t1;

    if (t < 0) {
        return glm::vec3(INFINITY);
    }

    return ray.getPosAtRange(t);
}

float Sphere::angleBetweenSurfaceNormalAndRay(Ray &ray, glm::vec3 posOnSurface)
{
    glm::vec3 normalOnSurfacePos =  glm::normalize(posOnSurface - this->center);
    return acosf(glm::dot(ray.unitVector, normalOnSurfacePos));
}

Sphere::Sphere()
{
    this->center = glm::vec3(0.0f, 0.0f, 0.0f);
    this->radius = 25;
    this->radiusSquared = this->radius * this->radius;
}

Sphere::Sphere(float centerx, float centery, float centerz, float radius)
{
    this->center = glm::vec3(centerx, centery, centerz);
    this->radius = radius;
    this->radiusSquared = radius * radius;
}

Ray Sphere::getReflectedRay(Ray &incidentRay, glm::vec3 posOnSurface)
{
    glm::vec3 normalOnSurfacePos =  glm::normalize(posOnSurface - this->center);
    glm::vec3 reflectedUnitVector = incidentRay.unitVector - 2*glm::dot(incidentRay.unitVector, normalOnSurfacePos) * normalOnSurfacePos;

    return Ray(posOnSurface+0.001f*reflectedUnitVector, reflectedUnitVector);
}