/*
IMapListener.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef IMAPLISTENER_HPP_INCLUDED
#define IMAPLISTENER_HPP_INCLUDED

namespace zcraft
{
	class IMapListener
	{
	public :

		virtual ~IMapListener() {}

		virtual void blockAdded(const Vector3i pos) = 0;

		virtual void blockChanged(const Vector3i pos) = 0;

		virtual void blockRemoved(const Vector3i pos) = 0;

	};

} // namespace zcraft

#endif // IMAPLISTENER_HPP_INCLUDED

