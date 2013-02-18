/*
serialization.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef SERIALIZATION_HPP_INCLUDED
#define SERIALIZATION_HPP_INCLUDED

/* header-only */

#include <iostream>

// TODO serialization: switch to common types (defined in types.hpp)
typedef unsigned char uint8;
typedef short unsigned int uint16;
typedef unsigned int uint32;

typedef char int8;
typedef short int int16;
typedef int int32;

namespace engine
{
	/*
		Unsigned integers
	*/

    inline void serialize(std::ostream& os, uint8 d)
    {
        os.put(d);
    }

    inline void serialize(std::ostream& os, uint16 d)
    {
        os.put((uint8)(d >> 8));
        os.put((uint8)d);
    }

    inline void serialize(std::ostream& os, uint32 d)
    {
        os.put((uint8)(d >> 24));
        os.put((uint8)(d >> 16));
        os.put((uint8)(d >> 8));
        os.put((uint8)d);
    }

    inline void unserialize(std::istream& is, uint8& d)
    {
        d = is.get();
    }

    inline void unserialize(std::istream& is, uint16& d)
    {
        d = ((uint8)is.get() << 8) | (uint8)is.get();
    }

    inline void unserialize(std::istream& is, uint32& d)
    {
        d = ((uint8)is.get() << 24) |
            ((uint8)is.get() << 16) |
            ((uint8)is.get() << 8) |
            (uint8)is.get();
    }

	/*
		Signed integers
	*/

    inline void serialize(std::ostream& os, int8 d)
    {
        serialize(os,(uint8)d);
    }

    inline void serialize(std::ostream& os, int16 d)
    {
        serialize(os, (uint16)d);
    }

    inline void serialize(std::ostream& os, int32 d)
    {
        serialize(os, (uint32)d);
    }

    inline void unserialize(std::istream& is, int8& d)
    {
        uint8 d1;
        unserialize(is, d1);
        d = (int8)d1;
    }

    inline void unserialize(std::istream& is, int16& d)
    {
        uint16 d1;
        unserialize(is, d1);
        d = (int16)d1;
    }

    inline void unserialize(std::istream& is, int32& d)
    {
        uint32 d1;
        unserialize(is, d1);
        d = (int32)d1;
    }

	/*
		Floating numbers
	*/

    inline void serialize(std::ostream& os, double d)
    {
        char* buf = (char*)(&d);
        os.write(buf, sizeof(double));
    }

    inline void unserialize(std::istream& is, double& d)
    {
        char buf[sizeof(double)] = {0};
        is.read(buf, sizeof(double));
        double* dp = (double*)buf;
        d = *dp;
    }

    inline void serialize(std::ostream& os, float d)
    {
        char* buf = (char*)(&d);
        os.write(buf, sizeof(float));
    }

    inline void unserialize(std::istream& is, float& d)
    {
        char buf[sizeof(float)] = {0};
        is.read(buf, sizeof(float));
        float* dp = (float*)buf;
        d = *dp;
    }

    inline void serializeAsText(std::ostream& os, float d)
    {
        os << d << ' '; // space delimiter (for binary streams)
    }

    inline void unserializeFromText(std::istream& is, float& d)
    {
        is >> d;
        is.get(); // skip space delimiter
    }

    inline void serializeAsText(std::ostream& os, double d)
    {
        os << d << ' '; // space delimiter (for binary streams)
    }

    inline void unserializeFromText(std::istream& is, double& d)
    {
        is >> d;
        is.get(); // skip end space
    }

	/*
		Strings
	*/

    inline void serialize(std::ostream& os, std::string s)
    {
        // size first
        serialize(os, s.size());
        // then characters
        for(unsigned int i=0; i<s.size(); i++)
        {
            os << (uint8)s[i];
        }
    }

    inline void unserialize(std::istream& is, std::string& s)
    {
        s.clear();
        uint32 size;
        // getting size
        unserialize(is, size);
        s.resize(size);
        // getting characters
        for(unsigned int i=0; i<s.size(); i++)
        {
            s[i] = is.get();
        }
    }

#ifdef ZN_SFML

	//////////////////////////////////////////////
	// SFML-dependant part
	//////////////////////////////////////////////

	/*
		Vector2i
	*/

	inline void serialize(std::ostream & os, const sf::Vector2i & vec)
	{
		serialize(os, vec.x);
		serialize(os, vec.y);
	}

	inline void unserialize(std::istream & is, sf::Vector2i & vec)
	{
		unserialize(is, vec.x);
		unserialize(is, vec.y);
	}

	/*
		Vector2f
	*/

	inline void serialize(std::ostream & os, const sf::Vector2f & vec)
	{
		serialize(os, vec.x);
		serialize(os, vec.y);
	}

	inline void unserialize(std::istream & is, sf::Vector2f & vec)
	{
		unserialize(is, vec.x);
		unserialize(is, vec.y);
	}

#endif // ZN_SFML

} // namespace engine


#endif // SERIALIZATION_HPP_INCLUDED

