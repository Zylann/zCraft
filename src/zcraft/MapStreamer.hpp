/*
MapStreamer.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef MAPSTREAMER_HPP_INCLUDED
#define MAPSTREAMER_HPP_INCLUDED

#include "zcraft/BlockMap.hpp"
#include "zcraft/mapgen/MapGenerator.hpp"
#include "zcraft/MapStreamThread.hpp"

namespace zcraft
{
	/**
		The MapStreamer ensures that blocks are loaded or saved
		efficiently around players while they move.
		This version currently only supports 1 player.
	**/
	// TODO MapStreamer: make non-copyable
	class MapStreamer
	{
	public :

		static const u32 UPDATE_PERIOD = 500; // milliseconds

	private :

		u32 m_radius;
		Vector3i m_center;
		Vector3i m_lastCenter;
		BlockMap * r_map;
		MapStreamThread m_streamThread;
		std::set<Vector3i> m_requestedBlocksPositions;
		bool m_save;

		// TODO MapStreamer: add a cache

	public :

		MapStreamer(BlockMap & map, u32 radiusBlocks = 4);

		~MapStreamer();

		void update(const Vector3i center, bool forceUpdate = false);

		inline MapStreamThread::RunningInfo getThreadInfo()
		{ return m_streamThread.getRunningInfo(); }

		// Enables or disables map saving.
		inline void setSave(bool enable) { m_save = enable; }

	private :

		void doUpdate();

	};

} // namespace zcraft


#endif // MAPSTREAMER_HPP_INCLUDED
