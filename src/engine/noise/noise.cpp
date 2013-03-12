/*
noise.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <cmath>
#include <iostream>

#include "engine/noise/noise.hpp"
#include "engine/interpolation.hpp"

// set at random
#define RAND_SEQ_X 72699
#define RAND_SEQ_Y 31976
#define RAND_SEQ_Z 16863
#define RAND_SEQ_SEED 561
#define RAND_SEQ1 11126
#define RAND_SEQ2 98756
#define RAND_SEQ3 423005601
// constant
#define MAX_INT7 0x7fffffff

namespace zn
{
    /*
        These functions generate noise from a seed and coordinates.
        Using the same seed and coordinates will generate the same noise.
    */

    // [0,1]
    float noise2d(int x, int y, int seed)
    {
         // "hazard" from known random sequences, seed and coordinates
        int n = RAND_SEQ_X*x + RAND_SEQ_Y*y + RAND_SEQ_SEED*seed;
        n &= 0x7fffffff; // clear last sign bit
        n = (n >> 13) ^ n;
        n = n * (n * n * RAND_SEQ1 + RAND_SEQ2) + RAND_SEQ3;
        n &= 0x7fffffff;
        // returning [0,1] float
        return (float)n / MAX_INT7;
    }

    float noise2dGradient(float x, float y, int seed)
    {
        // Calculate the integer coordinates
        int x0 = (x > 0.0 ? (int)x : (int)x - 1);
        int y0 = (y > 0.0 ? (int)y : (int)y - 1);
        // Calculate the remaining part of the coordinates
        float xl = x - (float)x0;
        float yl = y - (float)y0;
        // Get values for corners of square
        float v00 = noise2d(x0, y0, seed);
        float v10 = noise2d(x0+1, y0, seed);
        float v01 = noise2d(x0, y0+1, seed);
        float v11 = noise2d(x0+1, y0+1, seed);
        // Interpolate
        return biLinearInterpolation(v00,v10,v01,v11,xl,yl);
    }

    float noise2dPerlin(
			float x, float y, int seed,
			int octaves, float persistence, float period)
    {
        if(octaves < 1)
            return 0;

        x /= period;
        y /= period;

        float noise = 0; // noise
        float f = 1.0;
        float amp = 1.0; // amplitude of an octave
        float ampMax = 0; // total amplitude

        for(int i = 0; i < octaves; i++)
        {
            noise += amp * noise2dGradient(x*f, y*f, seed+i);
            ampMax += amp;
            f *= 2.0;
            amp *= persistence; // reduce next amplitude
        }

        return noise / ampMax;
    }

    // [0,1]
    float noise3d(int x, int y, int z, int seed)
    {
         // "hazard" from known random sequences, seed and coordinates
        int n = RAND_SEQ_X*x + RAND_SEQ_Y*y + RAND_SEQ_Z*z + RAND_SEQ_SEED*seed;
        n &= 0x7fffffff; // clear last sign bit
        n = (n >> 13) ^ n;
        n = n * (n * n * RAND_SEQ1 + RAND_SEQ2) + RAND_SEQ3;
        n &= 0x7fffffff;
        // returning [0,1] float
        return (float)n / MAX_INT7;
    }

	float noise3dGradient(float x, float y, float z, int seed)
    {
        // Calculate the integer coordinates
        int x0 = (x > 0.0 ? (int)x : (int)x - 1);
        int y0 = (y > 0.0 ? (int)y : (int)y - 1);
        int z0 = (z > 0.0 ? (int)z : (int)z - 1);
        // Calculate the remaining part of the coordinates
        float xl = x - (float)x0;
        float yl = y - (float)y0;
        float zl = z - (float)z0;
        // Get values for corners of cube
        float v000 = noise3d(x0, y0, z0, seed);
        float v100 = noise3d(x0+1, y0, z0, seed);
        float v010 = noise3d(x0, y0+1, z0, seed);
        float v110 = noise3d(x0+1, y0+1, z0, seed);
        float v001 = noise3d(x0, y0, z0+1, seed);
        float v101 = noise3d(x0+1, y0, z0+1, seed);
        float v011 = noise3d(x0, y0+1, z0+1, seed);
        float v111 = noise3d(x0+1, y0+1, z0+1, seed);
        // Interpolate
        return triLinearInterpolation(v000,v100,v010,v110,v001,v101,v011,v111,xl,yl,zl);
    }

    float noise3dPerlin(
			float x, float y, float z, int seed,
			int octaves, float persistence, float period)
    {
        if(octaves < 1)
            return 0;

        x /= period;
        y /= period;
        z /= period;

        float noise = 0;
        float f = 1.0;
        float amp = 1.0;
        float ampMax = 0;

        for(int i=0; i<octaves; i++)
        {
            noise += amp * noise3dGradient(x*f, y*f, z*f, seed+i);
            ampMax += amp;
            f *= 2.0;
            amp *= persistence;
        }
        return noise / ampMax;
    }

} // namespace zn

