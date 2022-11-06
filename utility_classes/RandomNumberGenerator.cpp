//
// Created by ilyazavalov on 29/10/22.
//

#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator() : rng(std::chrono::steady_clock::now().time_since_epoch().count()){ }

int RandomNumberGenerator::operator()() {
    return int(rng());
}