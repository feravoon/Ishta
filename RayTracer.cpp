#include "RayTracer.h"

RaySample RayTracer::sampleRay(Ray &ray, std::vector<std::shared_ptr<SceneObject>> &sceneObjectSet, std::vector<Light> &lightSet)
{
    glm::vec3 incomingLightVec;
    float distanceToLight;

    // Check intersection with every object in the scene
    IntersectionData intersectionResult;
    intersectionResult = getClosestIntersection(ray, sceneObjectSet);

    RaySample rs;
    rs.colorIntensity = glm::vec3(0.0f);
    rs.depth = intersectionResult.minDepth;
    rs.intersection = intersectionResult.closestIntersection;
    rs.closestObjectIndex = intersectionResult.minDepthIndex;

    if(rs.closestObjectIndex == -1)
        return rs;

    IntersectionData lightIntersectionResult;
    for(int i = 0; i < lightSet.size(); i++)
    {
        incomingLightVec = intersectionResult.closestIntersection - lightSet[i].position;
        distanceToLight = glm::length(incomingLightVec);
        incomingLightVec = incomingLightVec/distanceToLight;

        Ray lightRay(lightSet[i].position, incomingLightVec);
        lightIntersectionResult = getClosestIntersection(lightRay, sceneObjectSet);

        if(glm::length(intersectionResult.closestIntersection - lightIntersectionResult.closestIntersection)>0.1f)
            continue;
        

        float angleBetweenSurfaceNormalAndRay = sceneObjectSet[intersectionResult.minDepthIndex]->angleBetweenSurfaceNormalAndRay(lightRay, intersectionResult.closestIntersection) + M_PI;
        float reflectionCoeff = cosf(angleBetweenSurfaceNormalAndRay);

        rs.colorIntensity += lightSet[i].color * lightSet[i].intensity * reflectionCoeff / (distanceToLight*distanceToLight);
    }

    return rs;
}

IntersectionData RayTracer::getClosestIntersection(Ray &ray, std::vector<std::shared_ptr<SceneObject>> &sceneObjectSet)
{
    IntersectionData result;
    result.minDepth = MAXFLOAT;
    result.minDepthIndex = -1;
    glm::vec3 intersection;
    float curDepth;

    for(int p = 0; p < sceneObjectSet.size(); p++)
    {
        intersection = sceneObjectSet[p]->intersectWithRay(ray);
        curDepth = glm::length(intersection - ray.initPoint);
        if(curDepth < result.minDepth)
        {
            result.minDepth = curDepth;
            result.minDepthIndex = p;
            result.closestIntersection = intersection;
        }
    }

    return result;
}
