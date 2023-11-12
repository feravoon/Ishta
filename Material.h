#include "glm/vec3.hpp"

class Material {

    public:
        glm::vec3 diffuse;
        Material();
        Material(float r, float g, float b);
};