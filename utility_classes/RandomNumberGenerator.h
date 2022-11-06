//
// Created by ilyazavalov on 29/10/22.
//

#ifndef DATA_STRUCTURES_RANDOMNUMBERGENERATOR_H
#define DATA_STRUCTURES_RANDOMNUMBERGENERATOR_H

#include <random>
#include <chrono>

class RandomNumberGenerator {
private:
    std::mt19937 rng;
public:
    RandomNumberGenerator();
    int operator()();
};


#endif //DATA_STRUCTURES_RANDOMNUMBERGENERATOR_H
