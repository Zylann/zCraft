#ifndef CARTOGRAPHY_HPP_INCLUDED
#define CARTOGRAPHY_HPP_INCLUDED

#include <map>
#include <SFML/Graphics.hpp>
//#include "engine/core/Vector2.hpp"
#include "zcraft/common.hpp"

namespace zcraft
{
	/*
		A cartography is a set of tiny pictures (representing blocks/chunks)
		that form a bigger one.
	*/

	class Cartography
	{
	private :

		std::map<Vector2i, sf::Texture> m_pics;

	public :

		Cartography();

		~Cartography();

		void clear();

		/// Sets one of the pictures of the cartography
		void setPictureFromImage(const Vector2i pos, const sf::Image & pic);

		void erasePicture(const Vector2i pos);

		const sf::Texture * getPicture(const Vector2i pos) const;

		void saveAsBigImage(const std::string fpath);

		void render(float scale = 1, bool grid = false);

	};

} // namespace zcraft


#endif // CARTOGRAPHY_HPP_INCLUDED
