#include "RandomGenerator.h"


RandomGenerator::RandomGenerator()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->generator = std::default_random_engine(seed);
    this->distribution = std::normal_distribution<float>(0.0, 1.0);
}

RandomGenerator::RandomGenerator(float mean, float sigma)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    this->generator = std::default_random_engine(seed);
    this->distribution = std::normal_distribution<float>(mean, sigma);
}

float RandomGenerator::generate()
{
    return this->distribution(this->generator);    
}