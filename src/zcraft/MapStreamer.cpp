#include "engine/math.hpp"
#include "zcraft/MapStreamer.hpp"

#define for_xyz(__pos, __min, __max) \
	for(__pos.z = __min.z; __pos.z <= __max.z; __pos.z++) \
	for(__pos.y = __min.y; __pos.y <= __max.y; __pos.y++) \
	for(__pos.x = __min.x; __pos.x <= __max.x; __pos.x++)

using namespace engine;

namespace zcraft
{
	MapStreamer::MapStreamer(BlockMap & map, u32 radiusBlocks)
	: m_streamThread("default", 131183)
	{
		r_map = &map;
		m_radius = radiusBlocks;
		m_save = true;
	}

	MapStreamer::~MapStreamer()
	{
		m_streamThread.stop();
		m_streamThread.wait();
	}

	void MapStreamer::update(const Vector3i center, bool forceUpdate)
	{
		// Update requests
		if(center != m_center || forceUpdate)
		{
			m_center = center;
			m_requestedBlocksPositions.clear();
			doUpdate();
		}

		// Retrieve replies
		std::list<Block*> replies;
		m_streamThread.popReplies(replies);

		// Insert blocks
		for(auto it = replies.begin(); it != replies.end(); it++)
		{
			Block * b = (*it);
			r_map->setBlock(b);
			m_requestedBlocksPositions.erase(b->getPosition());
		}
	}

	void MapStreamer::doUpdate()
	{
		// Debug
		u32 fetchCount = 0;
		sf::Clock clock;

		if(!m_streamThread.isRunning())
			m_streamThread.start();

		std::list<ImmergeRequest> immergeRequests;
		std::list<EmergeRequest> emergeRequests;
		const Vector3i newMin = m_center - Vector3i(1,1,1) * m_radius;
		const Vector3i newMax = m_center + Vector3i(1,1,1) * m_radius;
		Vector3i pos;

		// Immerge useless blocks

		std::list<Block*> uselessBlocks;
		r_map->removeBlocksNotInArea(uselessBlocks, m_center, m_radius);
		//std::cout << uselessBlocks.size() << std::endl;

		for(auto it = uselessBlocks.begin(); it != uselessBlocks.end(); it++)
		{
			if((*it) != nullptr)
			{
				Block * block = (*it);
				if(block->dirty && m_save) // Is the block needs to be saved?
				{
					// Save and drop (true)
					immergeRequests.push_front(ImmergeRequest(block, true));
				}
				else
					delete block; // No need to save, just erase it from memory
			}
		}

		// Emerge required blocks

		std::multimap<f32,Vector3i> orderedEmergePositions;

		// For each block position around the current pos
		for(pos.z = newMin.z; pos.z <= newMax.z; pos.z++)
		for(pos.y = newMin.y; pos.y <= newMax.y; pos.y++)
		for(pos.x = newMin.x; pos.x <= newMax.x; pos.x++)
		{
			fetchCount++;
			// If the block is not loaded and has not been requested yet
			if(!r_map->isBlock(pos) &&
				m_requestedBlocksPositions.find(pos) == m_requestedBlocksPositions.end())
			{
				orderedEmergePositions.insert(
					std::pair<f32,Vector3i>(
						pos.getDistanceFromSQ(m_center), pos));
			}
		}

		for(auto it = orderedEmergePositions.begin();
				it != orderedEmergePositions.end(); it++)
		{
			// Request for block loading
			emergeRequests.push_front(EmergeRequest(it->second));
			m_requestedBlocksPositions.insert(it->second);
		}

		// Send requests
		m_streamThread.sendRequests(emergeRequests, immergeRequests);

		// Debug
		std::cout << "INFO: MapStreamer updated at " << m_center
			<< ", fetchCount=" << fetchCount
			<< ", time=" << clock.getElapsedTime().asSeconds() << "s"
			<< std::endl;
	}

} // namespace zcraft



