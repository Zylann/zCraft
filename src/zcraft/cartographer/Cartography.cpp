#include <SFML/System.hpp>
#include "zcraft/cartographer/Cartography.hpp"
#include "zcraft/Block.hpp"
#include "engine/opengl/opengl.hpp"

using namespace zn;

namespace zcraft
{
	Cartography::Cartography()
	{
	}

	Cartography::~Cartography()
	{
		clear();
	}

	void Cartography::clear()
	{
		m_pics.clear();
	}

	void Cartography::setPictureFromImage(const Vector2i pos, const sf::Image & pic)
	{
		if(pic.getSize().x != Block::SIZE || pic.getSize().y != Block::SIZE)
		{
			std::cout << "WARNING: Cartography::setPictureFromImage: "
				<< "given picture doesn't match Block::SIZE. " << pos << std::endl;
			return;
		}

		sf::Texture tex;
		tex.loadFromImage(pic);
		m_pics[pos] = tex;
	}

	void Cartography::erasePicture(const Vector2i pos)
	{
		m_pics.erase(pos);
	}

	const sf::Texture * Cartography::getPicture(const Vector2i pos) const
	{
		auto it = m_pics.find(pos);
		if(it != m_pics.end())
			return &it->second;
		return 0;
	}

	void Cartography::saveAsBigImage(const std::string fpath)
	{
		if(m_pics.empty())
		{
			std::cout << "INFO: Cartography::saveAsBigImage: nothing to save." << std::endl;
			return;
		}

		sf::Clock time;

		std::cout << "Cartography: fetching total size... ";

		Vector2i min;
		Vector2i max;

		for(auto & p : m_pics)
		{
			if(p.first.x < min.x)
				min.x = p.first.x;
			if(p.first.y < min.y)
				min.y = p.first.y;

			if(p.first.x > max.x)
				max.x = p.first.x;
			if(p.first.y > max.y)
				max.y = p.first.y;
		}

		std::cout << "done." << std::endl;
		std::cout << "Cartography: creating big image... " << std::endl;

		Vector2i size = (max - min + Vector2i(1,1)) * Block::SIZE;
		sf::Image bigImage;
		bigImage.create(size.x, size.y);

		std::cout << "| " << "min=" << min << ", max=" << max << " : size=" << size << std::endl;
		std::cout << "| done." << std::endl;
		std::cout << "Cartography: patching pictures... " << std::endl;

		u32 n = 0;
		for(auto & p : m_pics)
		{
			//std::cout << "| " << n + 1 << " of " << m_pics.size() << std::endl;

			Vector2i pos = (p.first - min) * Block::SIZE;
			sf::Image pic = p.second.copyToImage();

			for(u32 y = 0; y < pic.getSize().y; y++)
			for(u32 x = 0; x < pic.getSize().x; x++)
			{
				const u32 gx = pos.x + x;
				const u32 gy = pos.y + y;
				bigImage.setPixel(gx, gy, pic.getPixel(x, y));
			}

			n++;
		}

		std::cout << "| done." << std::endl;
		std::cout << "Cartography: saving big image as \"" << fpath << "\"...";

		bigImage.saveToFile(fpath);

		std::cout << "done (" << time.getElapsedTime().asSeconds() << "s)." << std::endl;
	}

	void Cartography::render(float scale, bool grid)
	{
	#if defined ZN_OPENGL2 //{

		glPushMatrix();

		glEnable(GL_TEXTURE_2D);
		glColor3f(1,1,1);

		glScalef(scale, scale, scale);

		for(auto & p : m_pics)
		{
			p.second.bind();

			glPushMatrix();
			glTranslatef(p.first.x, p.first.y, 0);

			glBegin(GL_QUADS);

			glTexCoord2f(0, 0);		glVertex2f(0, 0);
			glTexCoord2f(1, 0);		glVertex2f(1, 0);
			glTexCoord2f(1, 1);		glVertex2f(1, 1);
			glTexCoord2f(0, 1);		glVertex2f(0, 1);

			glEnd();

			glPopMatrix();
		}

		if(grid)
		{
			glDisable(GL_TEXTURE_2D);
			glColor4f(0.5f, 0.5f, 0.5f, 1.f);
			for(auto & p : m_pics)
				gl::drawRect(p.first.x, p.first.y, 1, 1);
		}

		glPopMatrix();

	//} OpenGL2
	#elif defined ZN_OPENGL3
		#warning "zcraft::Cartography doesn't supports OpenGL3"
	#endif
	}

} // namespace zcraft



