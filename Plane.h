#pragma once
#include "SceneObject.h"

class Plane : public SceneObject {
    public:
        float a, b, c, d;
        Plane(float a, float b, float c, float d);
        Plane();
        glm::vec3 getNormalVector();
        glm::vec3 intersectWithRay(Ray &ray);
        float angleBetweenSurfaceNormalAndRay(Ray &ray, glm::vec3 posOnSurface);
        Ray getReflectedRay(Ray &incidentRay, glm::vec3 posOnSurface);
        Plane(glm::vec3 x0, glm::vec3 x1, glm::vec3 x2);
};