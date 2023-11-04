#include "Ray.h"
#include "Plane.h"
#include "Sphere.h"
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"
#include "RayTracer.h"
#include <vector>
#include <memory>

int main()
{
    // Camera with a resolution of 640x480 and fov of 32 degrees by 24 degrees
    Camera cam;
    cam.position = glm::vec3(0.0f, -300.0f, 0.0f);
    cam.angles = glm::vec3(DEG2RAD(90.0f), DEG2RAD(0.0f), DEG2RAD(0.0f));
    cam.resolution = glm::vec2(2*640,2*480);
    cam.fov = glm::vec2(DEG2RAD(64),DEG2RAD(48));
    cam.exposure = 1.0f;

    std::vector<Light> lightSet(2);
    lightSet[0].intensity = 0000;
    lightSet[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
    lightSet[0].position = glm::vec3(0.0f, -300.0f, -50.0f);

    lightSet[1].intensity = 10000;
    lightSet[1].color = glm::vec3(1.0f, 1.0f, 1.0f);
    lightSet[1].position = glm::vec3(50.0f, -100.0f, 50.0f);

    std::vector<std::shared_ptr<SceneObject>> sceneObjectSet(8);
    //std::vector<SceneObject*> sceneObjectSet(7);
    //std::vector<SceneObject> sceneObjectSet(7);

    sceneObjectSet[0] = std::make_shared<Plane>( 0,  0,  1, 100);
    sceneObjectSet[1] = std::make_shared<Plane>( 0,  0, -1, 100);
    sceneObjectSet[2] = std::make_shared<Plane>( 1,  0,  0, 100);
    sceneObjectSet[3] = std::make_shared<Plane>(-1,  0,  0, 100);
    sceneObjectSet[4] = std::make_shared<Plane>( 0, -1,  0, 100);

    sceneObjectSet[5] = std::make_shared<Sphere>(0.0f, 0.0f, -50.0f, 50.0f);
    sceneObjectSet[6] = std::make_shared<Sphere>(-34.0f, -70.0f, -76.0f, 24.0f);
    sceneObjectSet[7] = std::make_shared<Sphere>(50.0f, -70.0f, -82.0f, 18.0f);


    uint8_t image[cam.resolution.x*cam.resolution.y*3];

    Ray pixelRay;
    Ray secondRay;
    RaySample rs;    

    glm::vec3 rawPixelVal;
    //int ang = 0;
    //float angRad = 0;

    float renderScale = 0.5f;
    
    Renderer renderer(renderScale, cam.resolution.x, cam.resolution.y);

    SDL_Event event;
    while (true) {
        // Events management
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                break;
            }
        }
        //angRad = DEG2RAD(ang);

        //cam.angles.z = DEG2RAD(0.0f + 3*cosf(angRad));
        //cam.angles.x = DEG2RAD(90.0f + 3*sinf(angRad));

        /*
        ang+=10;
        if(ang>=360)
            ang = 0;

        lightSet[0].position.x = 30*cosf(angRad);
        lightSet[0].position.y = 30*cosf(angRad);
        lightSet[0].position.z = 30*sinf(angRad);
        */
        for(int j=0; j<cam.resolution.y; j++)
        {
            for(int i=0; i<cam.resolution.x; i++)
            {
                pixelRay = cam.getRayAtPixel(i, j); // Shoot a ray from the pixel
                rs = RayTracer::sampleRay(pixelRay, sceneObjectSet, lightSet); // Get color sample from the scene

                rawPixelVal = 255.0f * cam.exposure * rs.colorIntensity; // Scale the color intensity for an image with 8-bit per channel

                // Clamp the color values
                rawPixelVal.r = glm::clamp(rawPixelVal.r,0.0f,255.0f);
                rawPixelVal.g = glm::clamp(rawPixelVal.g,0.0f,255.0f);
                rawPixelVal.b = glm::clamp(rawPixelVal.b,0.0f,255.0f);

                // Write colors to image matrix
                image[j*cam.resolution.x*3 + i*3]     = (uint8_t)(rawPixelVal.r);
                image[j*cam.resolution.x*3 + i*3 + 1] = (uint8_t)(rawPixelVal.g);
                image[j*cam.resolution.x*3 + i*3 + 2] = (uint8_t)(rawPixelVal.b);
            }
        }   
        renderer.render(image, cam.resolution.x, cam.resolution.y); // Show image on the screen
    }

    // destroy texture
    SDL_DestroyTexture(renderer.tex);
 
    // destroy renderer
    SDL_DestroyRenderer(renderer.rend);
 
    // destroy window
    SDL_DestroyWindow(renderer.win);

    // close SDL
    SDL_Quit();
    return 0;
}