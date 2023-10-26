#include "RayTracer.h"

RaySample RayTracer::sampleRay(Ray &ray, std::vector<Plane> &planeSet, std::vector<Light> &lightSet)
{
    glm::vec3 intersection, incomingLightVec;
    float curDepth;
    int minDepthIndex;
    float minDepth = MAXFLOAT;
    float distanceToLight;

    for(int p=0; p<5; p++)
    {
        intersection = ray.intersectWithPlane(planeSet[p]);
        curDepth = glm::length(intersection - ray.initPoint);
        if(curDepth<minDepth)
        {
            minDepth = curDepth;
            minDepthIndex = p;
        }
    }
    
    intersection = ray.intersectWithPlane(planeSet[minDepthIndex]);
    
    RaySample rs;
    rs.colorIntensity = glm::vec3(0.0f);
    rs.depth = minDepth;
    rs.intersection = intersection;

    for(int i = 0; i < lightSet.size(); i++)
    {
        incomingLightVec = intersection - lightSet[i].position;
        distanceToLight = glm::length(incomingLightVec);
        incomingLightVec = incomingLightVec/distanceToLight;

        Ray lightRay(lightSet[i].position, incomingLightVec);

        rs.colorIntensity += lightSet[i].color * lightSet[i].intensity * -(cosf(lightRay.angleToNormalOfPlane(planeSet[minDepthIndex]))) / (distanceToLight*distanceToLight);
    }
    

    return rs;
}