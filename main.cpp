#include "Ray.h"
#include "Plane.h"
#include "Camera.h"
#include "Renderer.h"

int main()
{
    // Camera with a resolution of 640x480 and fov of 32 degrees by 24 degrees
    Camera cam;
    cam.position = glm::vec3(0.0f, -200.0f, 5.0f);
    cam.angles = glm::vec3(DEG2RAD(170.0f), DEG2RAD(-10.0f), DEG2RAD(-10.0f));
    cam.resolution = glm::vec2(640,480);
    cam.fov = glm::vec2(DEG2RAD(32),DEG2RAD(24));

    Plane *planeSet[5];

    planeSet[0] = new Plane(0,0,1,-10);
    planeSet[1] = new Plane(0,0,-1,-10);
    planeSet[2] = new Plane(1,0,0,-10);
    planeSet[3] = new Plane(-1,0,0,-10);
    planeSet[4] = new Plane(0,-1,0,-10);

    uint8_t image[cam.resolution.x*cam.resolution.y*3];

    Ray pixelRay;
    float curDepth; 
    float minDepth = 2500000.0f;
    glm::vec3 intersection;
    for(int i=0; i<cam.resolution.x; i++)
    {
        for(int j=0; j<cam.resolution.y; j++)
        {
            pixelRay = cam.getRayAtPixel(i, j);
            minDepth = 2500000.0f;
            for(int p=0; p<5; p++)
            {
                intersection = pixelRay.intersectWithPlane(*planeSet[p]);
                curDepth = glm::length(intersection-cam.position);
                if(curDepth<minDepth)
                    minDepth = curDepth;
            }
            
            image[i*cam.resolution.y*3 + j*3] = (uint8_t)(minDepth/1);
            image[i*cam.resolution.y*3 + j*3 + 1] = (uint8_t)(minDepth/1);
            image[i*cam.resolution.y*3 + j*3 + 2] = (uint8_t)(minDepth/1);

            //image[i*cam.resolution.y*3 + j*3] = 255*(i*cam.resolution.y*3 + j*3)/(cam.resolution.x*cam.resolution.y*3); 
            //image[i*cam.resolution.y*3 + j*3 + 1] = 255*(i*cam.resolution.y*3 + j*3)/(cam.resolution.x*cam.resolution.y*3);
            //image[i*cam.resolution.y*3 + j*3 + 2] = 255*(i*cam.resolution.y*3 + j*3)/(cam.resolution.x*cam.resolution.y*3);
        }
    }

    Renderer renderer(1, cam.resolution.x, cam.resolution.y);
    int close = 0;
    SDL_Event event;
     while (!close) {
        // Events management
        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                close = true;
                break;
            }
        }
        renderer.render(image, cam.resolution.x, cam.resolution.y);
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