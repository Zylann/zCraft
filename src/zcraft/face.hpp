#ifndef FACE_HPP_INCLUDED
#define FACE_HPP_INCLUDED

#include "zcraft/common.hpp"

namespace zcraft
{
	namespace face
	{
		// The 3D space uses Z+ as altitude coordinate.

		/* Named by looking to y+ */
        enum Face
        {
            WEST = 0,
            EAST,
            SOUTH,
            NORTH,
            BOTTOM,
            TOP,

            COUNT // keep last
        };

        inline u8 opposite(u8 dir)
        {
            if(dir == WEST)    return EAST;
            if(dir == EAST)    return WEST;
            if(dir == SOUTH)   return NORTH;
            if(dir == NORTH)   return SOUTH;
            if(dir == BOTTOM)  return TOP;
            return BOTTOM; // if(dir == TOP)
        }

        inline Vector3i toVec3i(u8 dir)
        {
            if(dir == WEST)    return Vector3i(-1, 0, 0);
            if(dir == EAST)    return Vector3i(1, 0, 0);
            if(dir == SOUTH)   return Vector3i(0, -1, 0);
            if(dir == NORTH)   return Vector3i(0, 1, 0);
            if(dir == BOTTOM)  return Vector3i(0, 0, -1);
            return Vector3i(0, 0, 1); // if(dir == TOP)
        }

	}

} // namespace zcraft

#endif // FACE_HPP_INCLUDED
