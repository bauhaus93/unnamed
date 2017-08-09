#include "Rng.h"

Rng::Rng():
    generator {},
    distribution100 { 0, 99 },
    distributionStd {}{
    std::random_device rd;
    Seed(rd());
}

Rng::Rng(unsigned int seed):
    Rng() {
    Seed(seed);
}

void Rng::Seed(unsigned int newSeed) {
    generator.seed(newSeed);
    seed = newSeed;
}

unsigned int Rng::GetSeed() const {
    return seed;
}

std::mt19937 Rng::GetGenerator() {
    return generator;
}

unsigned int Rng::Random100() {
    return static_cast<unsigned int>(distribution100(generator));
}

int Rng::Random(int min, int max){
    if (min >= max) {
        throw GameException("Rng::Random", StringFormat("Min must be smaller than max, but was %d/%d", min, max));
    }
	return min + (distributionStd(generator) % (max - min + 1));
}

unsigned int Rng::Random() {
    return static_cast<unsigned int>(distributionStd(generator));
}
