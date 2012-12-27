/*
noise.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef NOISE_HPP_INCLUDED
#define NOISE_HPP_INCLUDED

namespace engine
{
    double noise2d(int x, int y, int seed);

    double noise2dGradient(double x, double y, int seed);

    double noise2dPerlin(
        double x, double y, int seed,
        int octaves, double persistence, double period);

	double noise3d(int x, int y, int z, int seed);

    double noise3dGradient(double x, double y, double z, int seed);

    double noise3dPerlin(
        double x, double y, double z, int seed,
        int octaves, double persistence, double period);

} // namespace engine


#endif // NOISE_HPP_INCLUDED
