/*
Exception.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef EXCEPTION_HPP_INCLUDED
#define EXCEPTION_HPP_INCLUDED

#include <exception>
#include <sstream>

/*
    This file is header-only
*/

namespace engine
{
    class Exception : public std::exception
    {
    private:

        std::string m_msg;

    public:

        enum ExceptionLevel
        {
            EX_INFO = 0,
            EX_WARNING,
            EX_ERROR,
            EX_FATAL,
            EX_UNKNOWN
        };

        Exception(const std::string & msg, int level = EX_UNKNOWN) throw()
        {
            switch(level)
            {
                case EX_INFO        : m_msg = "INFO: "; break;
                case EX_WARNING     : m_msg = "WARNING: "; break;
                case EX_ERROR       : m_msg = "ERROR: "; break;
                case EX_FATAL       : m_msg = "FATAL ERROR: "; break;
                default : m_msg = "EXCEPTION: "; break;
            }
            m_msg += msg;
        }

        virtual ~Exception() throw()
        {}

        virtual const char * what() const throw() override
        {
            return m_msg.c_str();
        }
    };

} // namespace engine


#endif // EXCEPTION_HPP_INCLUDED
