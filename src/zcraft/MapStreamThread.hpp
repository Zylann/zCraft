/*
MapStreamThread.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef MAPSTREAMTHREAD_HPP_INCLUDED
#define MAPSTREAMTHREAD_HPP_INCLUDED

#include <list>
#include "engine/system/Thread.hpp"
#include "engine/system/Mutex.hpp"
#include "zcraft/MapLoader.hpp"
#include "zcraft/mapgen/MapGenerator.hpp"

namespace zcraft
{
	/**
		This thread takes care of generating, loading or saving
		map blocks for one world.
		It does not interact with the map, and it only deals with Blocks :

		Map <--blocks--> MapStreamer <--blocks--> MapStreamThread
		|<---------Main thread------------------>|
												Sync

		This architecture is aimed at minimal concurrent access,
		as every synchronisation points are located between the MapStreamer and
		the MapStreamThread.
	**/

	struct EmergeRequest
	{
		Vector3i pos;
		EmergeRequest(const Vector3i p) : pos(p) {}
	};

	struct ImmergeRequest
	{
		Block * block = nullptr;
		bool drop = true; // if true, the block will be deleted after processing

		ImmergeRequest(Block * b, bool pdrop) : block(b), drop(pdrop) {}
	};

	class MapStreamThread : public zn::AThread
	{
	public /* TYPES */ :

		struct RunningInfo
		{
			u32 savedCount = 0;
			u32 droppedCount = 0;
			u32 loadedCount = 0;
			u32 generatedCount = 0;
			u32 remainingRequests = 0;
		};

	private /* ATTRIBUTES */ :

		MapLoader m_loader;
		AMapGenerator * m_generator;
		RunningInfo m_runningInfo;
		// In
		std::list<ImmergeRequest> m_immergeRequests;
		std::list<EmergeRequest> m_emergeRequests;
		zn::Mutex m_requestsMutex;
		// Out
		std::list<Block*> m_replies;
		zn::Mutex m_repliesMutex;

	public /* METHODS */ :

		// Creates an inactive MapStreamThread binded to the
		// specified world folder and having the given map generation seed.
		MapStreamThread(std::string worldDir, u32 genSeed = 131183);

		~MapStreamThread();

		// Replace old emerge requests by new ones,
		// and adds new immerge requests to the old ones.
		// Given lists may be modified to avoid copies.
		void sendRequests(
			std::list<EmergeRequest> & emergeRequests,
			std::list<ImmergeRequest> & immergeRequests);

		// Retrieve all thread's work results at once.
		void popReplies(std::list<Block*> & replies);

		// Get informations about the state of the thread (read-only)
		inline RunningInfo getRunningInfo() const { return m_runningInfo; }

	protected /* METHODS */ :

		void run() override;

		void loop();

		void clear();

	};

} // namespace zcraft

#endif // MAPSTREAMTHREAD_HPP_INCLUDED



