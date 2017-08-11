#pragma once

#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <cmath>

#include "common/Rng.h"

namespace unnamed::map::generator {

class SimplexNoise{


    rng::Rng                rng;
    std::vector<uint8_t>    permutation;

    double              Fade(double t);
    double              Lerp(double t, double a, double b);
    double              Gradient(int hash, double x, double y, double z);

public:
                    SimplexNoise();
    explicit        SimplexNoise(unsigned int seed);

    unsigned int    GetSeed() const;
    double          GetNoise(double x, double y);
    double          GetOctavedNoise(int x, int y, int octaves, double roughness, double scale);
};

}
