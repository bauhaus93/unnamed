#pragma once

#include <random>
#include "exception/GameException.h"
#include "common/StringFormat.h"

class Rng {

    std::mt19937                        generator;
    std::uniform_int_distribution<>     distribution100;
    std::uniform_int_distribution<>     distributionStd;
    unsigned int                        seed;

public:

                    Rng();
    explicit        Rng(unsigned int seed);

    void            Seed(unsigned int newSeed);
    unsigned int    GetSeed() const;
    std::mt19937    GetGenerator();


    unsigned int    Random100();
    int             Random(int min, int max);
    unsigned int    Random();
};
