/*
Rect.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_RECT_HPP_INCLUDED
#define ZN_RECT_HPP_INCLUDED

#include <iostream> // For textual representation
#include "Vector2.hpp"

namespace zn
{
	/*
		A 2D rectangle defined by two points.
	*/
	template <typename T>
	class Rect
	{
	public :

		Vector2<T> min;
		Vector2<T> max;

		Rect() {}

		Rect(const T width, const T height)
			: min(0, 0), max(width-1, height-1)
		{}

		Rect(const T minX, const T minY, const T maxX, const T maxY)
		: min(minX, minY), max(maxX, maxY)
		{}

		Rect(const Rect & other)
		{
			min = other.min;
			max = other.max;
		}

		Rect(const Vector2<T> & min0, const Vector2<T> & max0)
		{
			min = min0;
			max = max0;
		}

		// Initializes the rectangle from new edges
		inline void set(const T minX, const T minY, const T maxX, const T maxY)
		{
			min.x = minX;
			min.y = minY;
			max.x = maxX;
			max.y = maxY;
		}

		// Initializes the rectangle from another
		inline void set(const Rect & other)
		{
			min = other.min;
			max = other.max;
		}

		// Initializes the rectangle from new edges
		inline void set(const Vector2<T> & min0, const Vector2<T> & max0)
		{
			min = min0;
			max = max0;
		}

		// Returns the positive width of the rectangle
		inline T width() const
		{
			const T w = max.x - min.x;
			return w > 0 ? w : -w;
		}

		// Returns the positive height of the rectangle
		inline T height() const
		{
			const T h = max.y - min.y;
			return h > 0 ? h : -h;
		}

		// Returns the positive area of the rectangle
		inline T area() const
		{
			return width() * height();
		}

		// Tests if the given point (x,y) is contained into the rectangle.
		// Edges are included.
		inline bool contains(const T x, const T y) const
		{
			return x >= min.x && x <= max.x && y >= min.y && y <= max.y;
		}

		// Tests if the given point is contained into the rectangle.
		// Edges are included.
		inline bool contains(const Vector2<T> & p) const
		{
			return contains(p.x, p.y);
		}

		// Tests if the given rectangle is included in the current one.
		// Edges are included.
		inline bool contains(const Rect<T> & other) const
		{
			return min.x <= other.min.x && max.x >= other.max.x &&
					min.y <= other.min.y && max.y >= other.max.y ;
		}

		// Tests if the given rectangle intersects the current one.
		// Edges are included.
		inline bool intersects(const Rect<T> & other) const
		{
			return max.y >= other.min.y &&
					min.y <= other.max.y &&
					max.x >= other.min.x &&
					max.x <= other.max.x ;
		}

		// TODO Rect: intersection

		// Swaps min and max coordinates in order to keep them ordered
		// (min.x <= max.x and min.y <= max.y)
		inline void repair()
		{
			if(max.x < min.x)
				std::swap(min.x, max.x);
			if(max.y < min.y)
				std::swap(min.y, max.y);
		}

		// Offsets borders of the rectangle :
		// negative value means contracting,
		// positive value means expanding.
		inline Rect<T> & pad(const T p)
		{
			min.x -= p;
			min.y -= p;
			max.x += p;
			max.y += p;
			return *this;
		}

		// Offsets borders of the rectangle :
		// negative values means contracting,
		// positive values means expanding.
		inline Rect<T> & pad(const T x, const T y)
		{
			min.x -= x;
			min.y -= y;
			max.x += x;
			max.y += y;
			return *this;
		}

		// Offsets borders of the rectangle :
		// negative values means contracting,
		// positive values means expanding.
		inline Rect<T> & pad(const T minx, const T miny, const T maxx, const T maxy)
		{
			min.x -= minx;
			min.y -= miny;
			max.x += maxx;
			max.y += maxy;
			return *this;
		}

		// Moves the rectangle by a vector
		inline Rect<T> & offset(const T x, const T y)
		{
			min.x += x;
			min.y += y;
			max.x += x;
			max.y += y;
			return *this;
		}

		// Moves the rectangle by a vector, returns reference for chaining
		inline Rect<T> & offset(const Vector2<T> & off)
		{
			min += off;
			max += off;
			return *this;
		}

		// Expands the rect from 1 side only per dimension.
		// Example : if x < 0, the rectangle will be expanded from the left
		// without modify the opposite side.
		// Returns self for chaining.
		inline Rect<T> & expand(const T x, const T y)
		{
			if(x < 0)
				min.x += x;
			else if(x > 0)
				max.x += x;
			if(y < 0)
				min.y += y;
			else if(y > 0)
				max.y += y;
			return *this;
		}

		// Contracts the rect from 1 side only per dimension.
		// Example : if x < 0, the rectangle will be reduced from the right
		// without modify the opposite side.
		// Returns self for chaining.
		inline Rect<T> & contract(const T x, const T y)
		{
			if(x < 0)
				max.x += x;
			else if(x > 0)
				min.x += x;
			if(y < 0)
				max.y += y;
			else if(y > 0)
				min.y += y;
			return *this;
		}

		// Computes the center of the rectangle.
		inline Vector2<T> getCenter() const
		{
			return Vector2<T>((min.x + max.y) / 2, (min.y + max.y) / 2);
		}

		// Moves the rectangle to have its origin at the given position
		inline void setPositionFromOrigin(const T x, const T y)
		{
			offset(x - min.x, y - min.y);
		}

		// Moves the rectangle to have its origin at the given position.
		// The origin is the min point.
		inline void setPositionFromOrigin(const Vector2<T> & p)
		{
			offset(p - min);
		}

		// Clips the rectangle to another.
		// If they don't intersect, it will result in a rectangle with area = 0
		inline void clipTo(const Rect<T> & other)
		{
			if(max.x > other.max.x)
				max.x = other.max.x;
			if(max.y > other.max.y)
				max.y = other.max.y;

			if(min.x > other.min.x)
				min.x = other.min.x;
			if(min.y > other.min.y)
				min.y = other.min.y;

			// correct possible invalid rect resulting from clipping
			if(min.y > max.y)
				min.y = max.y;
			if(min.x > max.x)
				min.x = max.x;
		}

	};

	// Textual representation
	template <typename T>
	std::ostream & operator<<(std::ostream & os, const Rect<T> & r)
	{
		os << "(" << r.min.x << ", " << r.min.y << ", "
				  << r.max.x << ", " << r.max.y << ")";
		return os;
	}

	typedef Rect<int> IntRect;
	typedef Rect<float> FloatRect;

} // namespace zn

#endif // ZN_RECT_HPP_INCLUDED


