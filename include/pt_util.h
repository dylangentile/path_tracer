#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <cstdint>

const double pt_infinity = std::numeric_limits<double>::infinity();

void seed_random();
double random_double();
double random_double(double min, double max);
double clamp(double x, double min, double max);
double deg_to_rad(double x);

#define OUTPUT_FORMAT_STBI_RGB 3

constexpr size_t COLOR_SIZE = 3;