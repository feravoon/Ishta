#include <random>
class RandomGenerator{

    public:
        std::default_random_engine generator;
        std::normal_distribution<float> distribution;
        float generate();
        RandomGenerator();
        RandomGenerator(float mean, float sigma);
};