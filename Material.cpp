#include "Material.h"

Material::Material()
{
    this->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
}

Material::Material(float r, float g, float b)
{
    this->diffuse = glm::vec3(r, g, b);
}