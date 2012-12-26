/*
Grid
noise.cpp

Copyright (c) 2011 by Marc Gilleron, <marc.gilleron@free.fr>

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cmath>
#include <iostream>

#include "engine/noise.hpp"
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

namespace engine
{
    /*
        These functions generate noise from a seed and coordinates.
        Using the same seed and coordinates will generate the same noise.
    */

    // [0,1]
    double noise2d(int x, int y, int seed)
    {
         // "hazard" from known random sequences, seed and coordinates
        int n = RAND_SEQ_X*x + RAND_SEQ_Y*y + RAND_SEQ_SEED*seed;
        n &= 0x7fffffff; // clear last sign bit
        // shifting, adding and noising stuff
        n = (n >> 13) ^ n;
        n = n * (n * n * RAND_SEQ1 + RAND_SEQ2) + RAND_SEQ3;
        n &= 0x7fffffff;
        // returning [0,1] float
        return (double)n / MAX_INT7;
    }

    double noise2dGradient(double x, double y, int seed)
    {
        // Calculate the integer coordinates
        int x0 = (x > 0.0 ? (int)x : (int)x - 1);
        int y0 = (y > 0.0 ? (int)y : (int)y - 1);
        // Calculate the remaining part of the coordinates
        double xl = x - (double)x0;
        double yl = y - (double)y0;
        // Get values for corners of square
        double v00 = noise2d(x0, y0, seed);
        double v10 = noise2d(x0+1, y0, seed);
        double v01 = noise2d(x0, y0+1, seed);
        double v11 = noise2d(x0+1, y0+1, seed);
        // Interpolate
        return biLinearInterpolation(v00,v10,v01,v11,xl,yl);
    }

    double noise2dPerlin(
			double x, double y, int seed,
			int octaves, double persistence, double period)
    {
        if(octaves < 1)
            return 0;

        x /= period;
        y /= period;

        double noise = 0; // noise
        double f = 1.0;
        double amp = 1.0; // amplitude of an octave
        double ampMax = 0; // total amplitude

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
    double noise3d(int x, int y, int z, int seed)
    {
         // "hazard" from known random sequences, seed and coordinates
        int n = RAND_SEQ_X*x + RAND_SEQ_Y*y + RAND_SEQ_Z*z + RAND_SEQ_SEED*seed;
        n &= 0x7fffffff; // clear last sign bit
        // shifting, adding and noising stuff
        n = (n >> 13) ^ n;
        n = n * (n * n * RAND_SEQ1 + RAND_SEQ2) + RAND_SEQ3;
        n &= 0x7fffffff;
        // returning [0,1] float
        return (double)n / MAX_INT7;
    }

	double noise3dGradient(double x, double y, double z, int seed)
    {
        // Calculate the integer coordinates
        int x0 = (x > 0.0 ? (int)x : (int)x - 1);
        int y0 = (y > 0.0 ? (int)y : (int)y - 1);
        int z0 = (z > 0.0 ? (int)z : (int)z - 1);
        // Calculate the remaining part of the coordinates
        double xl = x - (double)x0;
        double yl = y - (double)y0;
        double zl = z - (double)z0;
        // Get values for corners of cube
        double v000 = noise3d(x0, y0, z0, seed);
        double v100 = noise3d(x0+1, y0, z0, seed);
        double v010 = noise3d(x0, y0+1, z0, seed);
        double v110 = noise3d(x0+1, y0+1, z0, seed);
        double v001 = noise3d(x0, y0, z0+1, seed);
        double v101 = noise3d(x0+1, y0, z0+1, seed);
        double v011 = noise3d(x0, y0+1, z0+1, seed);
        double v111 = noise3d(x0+1, y0+1, z0+1, seed);
        // Interpolate
        return triLinearInterpolation(v000,v100,v010,v110,v001,v101,v011,v111,xl,yl,zl);
    }

    double noise3dPerlin(
			double x, double y, double z, int seed,
			int octaves, double persistence, double period)
    {
        if(octaves < 1)
            return 0;

        x /= period;
        y /= period;
        z /= period;

        double noise = 0;
        double f = 1.0;
        double amp = 1.0;
        double ampMax = 0;

        for(int i=0; i<octaves; i++)
        {
            noise += amp * noise3dGradient(x*f, y*f, z*f, seed+i);
            ampMax += amp;
            f *= 2.0;
            amp *= persistence;
        }
        return noise / ampMax;
    }

} // namespace engine

