#ifndef FLATMAPVIEWER_HPP_INCLUDED
#define FLATMAPVIEWER_HPP_INCLUDED

#include "engine/BasicGame.hpp"
#include "engine/bmfont/Font.hpp"
#include "engine/opengl/Camera2D.hpp"
#include "zcraft/zcraft.hpp"
#include "zcraft/cartographer/Cartography.hpp"
#include "zcraft/MapStreamer.hpp"

namespace zcraft
{
	class FlatMapViewer : public zn::ABasicGame, public IMapListener
	{
	private :

		MapStreamer * m_mapStreamer;
		BlockMap m_map;
		Cartography m_cartography;
		zn::Camera2D m_camera;
		zn::bmfont::Font m_font;

	public :

		FlatMapViewer(u32 width, u32 height);

		~FlatMapViewer();

		void blockAdded(const Vector3i pos, BlockMap & map) override;

		void blockChanged(const Vector3i pos, BlockMap & map) override;

		void blockRemoved(const Vector3i pos, BlockMap & map) override;

	protected :

		bool init() override;

		void update(const zn::Time & delta) override;

		void renderScene(const zn::Time & delta) override;

		void renderGUI(const zn::Time & delta) override;

		void dispose() override;

		void resized(const Vector2i & newSize) override;

		void processEvent(const sf::Event & event) override;

	};

} // namespace zcraft

#endif // FLATMAPVIEWER_HPP_INCLUDED
