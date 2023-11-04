#include "RayTracer.h"

RaySample RayTracer::sampleRay(Ray &ray, std::vector<std::shared_ptr<SceneObject>> &sceneObjectSet, std::vector<Light> &lightSet)
{
    glm::vec3 intersection, incomingLightVec;
    float curDepth;
    glm::vec3 closestIntersection;
    float minDepth = MAXFLOAT;
    int minDepthIndex;
    float distanceToLight;

    for(int p = 0; p < sceneObjectSet.size(); p++)
    {
        intersection = sceneObjectSet[p]->intersectWithRay(ray);
        curDepth = glm::length(intersection - ray.initPoint);
        if(curDepth < minDepth)
        {
            minDepth = curDepth;
            minDepthIndex = p;
            closestIntersection = intersection;
        }
    }

    RaySample rs;
    rs.colorIntensity = glm::vec3(0.0f);
    rs.depth = minDepth;
    rs.intersection = closestIntersection;

    for(int i = 0; i < lightSet.size(); i++)
    {
        incomingLightVec = closestIntersection - lightSet[i].position;
        distanceToLight = glm::length(incomingLightVec);
        incomingLightVec = incomingLightVec/distanceToLight;

        Ray lightRay(lightSet[i].position, incomingLightVec);

        float angleBetweenSurfaceNormalAndRay = sceneObjectSet[minDepthIndex]->angleBetweenSurfaceNormalAndRay(lightRay, closestIntersection) + M_PI;
        float reflectionCoeff = cosf(angleBetweenSurfaceNormalAndRay);

        rs.colorIntensity += lightSet[i].color * lightSet[i].intensity *  reflectionCoeff / (distanceToLight*distanceToLight);
    }
    

    return rs;
}