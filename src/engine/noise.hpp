/*
noise.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ENGINE_NOISE_HPP_INCLUDED
#define ENGINE_NOISE_HPP_INCLUDED

namespace engine
{
    float noise2d(int x, int y, int seed);

    float noise2dGradient(float x, float y, int seed);

    float noise2dPerlin(
        float x, float y, int seed,
        int octaves, float persistence, float period);

	float noise3d(int x, int y, int z, int seed);

    float noise3dGradient(float x, float y, float z, int seed);

    float noise3dPerlin(
        float x, float y, float z, int seed,
        int octaves, float persistence, float period);

} // namespace engine


#endif // ENGINE_NOISE_HPP_INCLUDED
