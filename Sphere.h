#pragma once
#include "SceneObject.h"

class Sphere : public SceneObject{
    public:
        glm::vec3 center;
        float radius, radiusSquared;
        glm::vec3 intersectWithRay(Ray &ray);
        float angleBetweenSurfaceNormalAndRay(Ray &ray, glm::vec3 posOnSurface);
        Sphere();
        Sphere(float centerx, float centery, float centerz, float radius);
        Ray getReflectedRay(Ray &incidentRay, glm::vec3 posOnSurface);
};