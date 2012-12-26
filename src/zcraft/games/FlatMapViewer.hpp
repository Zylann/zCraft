#ifndef FLATMAPVIEWER_HPP_INCLUDED
#define FLATMAPVIEWER_HPP_INCLUDED

#include "engine/BasicGame.hpp"
#include "engine/bmfont/Font.hpp"
#include "engine/opengl/Camera2D.hpp"
#include "zcraft/zcraft.hpp"
#include "zcraft/cartographer/Cartography.hpp"
#include "zcraft/MapStreamer.hpp"
#include "zcraft/IMapListener.hpp"

namespace zcraft
{
	class FlatMapViewer : public engine::ABasicGame, public IMapListener
	{
	private :

		MapStreamer * m_mapStreamer;
		BlockMap m_map;
		Cartography m_cartography;
		engine::Camera2D m_camera;
		engine::bmfont::Font m_font;

	public :

		FlatMapViewer(u32 width, u32 height);

		~FlatMapViewer();

		void blockAdded(const Vector3i pos) override;

		void blockChanged(const Vector3i pos) override;

		void blockRemoved(const Vector3i pos) override;

	protected :

		bool init() override;

		void update(const engine::Time & delta) override;

		void render(const engine::Time & delta) override;

		void dispose() override;

		void resized(const Vector2i & newSize) override;

		void processEvent(const sf::Event & event) override;

	};

} // namespace zcraft

#endif // FLATMAPVIEWER_HPP_INCLUDED
