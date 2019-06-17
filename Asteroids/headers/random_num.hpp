#pragma once

#include <random>

constexpr auto PI = 3.14159265359;

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
std::uniform_real_distribution<> PIx2_RAND(0.0, 2.0*PI);
std::uniform_real_distribution<> window_Y_RAND(50.0, window_Y-50.0);
std::uniform_real_distribution<> RAND_0_to_1(0, 1.0);