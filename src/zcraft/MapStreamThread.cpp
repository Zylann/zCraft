/*
MapStreamThread.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include <sstream> // for debug stuff
#include "zcraft/MapStreamThread.hpp"

using namespace engine;

namespace zcraft
{
	MapStreamThread::MapStreamThread(std::string worldDir, u32 genSeed)
	: 	AThread("MapStreamThread"),
		m_loader(worldDir),
		m_generator(genSeed)
	{}

	MapStreamThread::~MapStreamThread()
	{
		clear();
	}

	void MapStreamThread::clear()
	{
		m_requestsMutex.lock();
		for(auto & req : m_immergeRequests)
		{
			if(req.drop)
			{
				// We must free memory here, even if the request hasn't been processed,
				// because the drop flag also means that the data is only
				// referenced in this request
				if(req.block != nullptr)
					delete req.block;
				else
					std::cout << "WARNING: MapStreamThread::clear: "
						<< "tried to delete immerge request block, "
						<< "but it was null" << std::endl;
			}
		}
		m_immergeRequests.clear();
		m_emergeRequests.clear();
		m_requestsMutex.unlock();

		m_repliesMutex.lock();
		for(auto it = m_replies.begin(); it != m_replies.end(); it++)
		{
			Block * block = *it;
			if(block != 0)
				delete block;
		}
		m_replies.clear();
		m_repliesMutex.unlock();
	}

	void MapStreamThread::sendRequests(
			std::list<EmergeRequest> & emergeRequests,
			std::list<ImmergeRequest> & immergeRequests)
	{
		m_requestsMutex.lock();

		m_immergeRequests.splice(m_immergeRequests.begin(), immergeRequests);

		m_emergeRequests.clear();
		m_emergeRequests.splice(m_emergeRequests.begin(), emergeRequests);

		m_requestsMutex.unlock();
	}

	void MapStreamThread::popReplies(std::list<Block*> & replies)
	{
		if(!m_repliesMutex.isLocked())
		{
			m_repliesMutex.lock();
			replies.splice(replies.begin(), m_replies);
			m_repliesMutex.unlock();
		}
	}

	void MapStreamThread::run()
	{
		while(m_runFlag)
		{
			loop();
		}
		clear();
	}

	void MapStreamThread::loop()
	{
		m_runningInfo = RunningInfo();

		// Retrieve requests

		const u32 pickLimit = 64;

		std::list<EmergeRequest> emergeRequests;
		std::list<ImmergeRequest> immergeRequests;

		if(!m_requestsMutex.isLocked())
		{
			m_requestsMutex.lock();

			u32 n = 0;
			// Note : all immerge requests must be processed first.
			for(; n < pickLimit && !m_immergeRequests.empty(); n++)
			{
				// TODO MapStreamThread: detect same immerge positions and choose the latest
				immergeRequests.push_front(m_immergeRequests.back());
				m_immergeRequests.pop_back();
			}
			for(; n < pickLimit && !m_emergeRequests.empty(); n++)
			{
				emergeRequests.push_front(m_emergeRequests.back());
				m_emergeRequests.pop_back();
			}

			m_runningInfo.remainingRequests =
				m_emergeRequests.size() + m_immergeRequests.size();

			m_requestsMutex.unlock();
		}

		// Process requests

		if(!immergeRequests.empty())
		{
			// Save [and drop]
			for(auto & req : immergeRequests)
			{
				m_loader.saveBlock(req.block);
				++m_runningInfo.savedCount;
				req.block->dirty = false;

				if(req.drop)
				{
					delete req.block;
					++m_runningInfo.droppedCount;
				}
			}
		}

		if(!emergeRequests.empty())
		{
			// Load or generate
			for(auto & req : emergeRequests)
			{
				Block * block = nullptr;
				if(m_loader.isBlockOnHardDrive(req.pos))
				{
					block = m_loader.loadBlock(req.pos);
					++m_runningInfo.loadedCount;
				}
				else
				{
					block = m_generator.makeBlock(req.pos);
					++m_runningInfo.generatedCount;
				}
				if(block != 0)
				{
					m_repliesMutex.lock();
					m_replies.push_back(block);
					m_repliesMutex.unlock();
				}
			}
		}

		// Debug
		/*
		std::stringstream ss;
		ss << "MapStreamThread: "
			<< "rem: " << m_runningInfo.remainingRequests
			<< ", G:" << m_runningInfo.generatedCount
			<< ", L:" << m_runningInfo.loadedCount
			<< ", S:" << m_runningInfo.savedCount
			<< ", D:" << m_runningInfo.droppedCount
			<< ", C:" << m_runningInfo.cancelledCount << std::endl;
		std::cout << ss.str();
		*/

		// Sleep a little to save CPU usage
		engine::sleep(50);
	}

} // namespace zcraft





