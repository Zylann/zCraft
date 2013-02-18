#include <array>
#include <iostream>

#include "TweenTest.hpp"
#include "engine/noise.hpp"

using namespace zn;

namespace experimental
{
	struct Ball
	{
		Vector2f pos;
		Vector2f vel;
		float r = 4;
	};

	std::array<Ball, 5000> balls;

	float brake(float x, float linear, float quadratic, float dt)
	{
		if(x > 0)
		{
			x -= x * x * quadratic * dt;
			x -= linear * dt;
			if(x < 0)
				x = 0;
		}
		if(x < 0)
		{
			x += x * x * quadratic * dt;
			x += linear * dt;
			if(x > 0)
				x = 0;
		}
		return x;
	}

	float rand(float min, float max)
	{
		static int n = 0;
		n++;
		return (max - min) * noise2d(n, n+1, 131183) + min;
	}

	bool TweenTest::init()
	{
		sf::Vector2u winSize = m_window.getSize();
		float w = winSize.x;
		float h = winSize.y;

		balls[0].pos.x = w / 2.f;
		balls[0].pos.y = h / 2.f;
		balls[0].r = 10;

		for(unsigned int i = 1; i < balls.size(); i++)
		{
			Ball & b = balls[i];
//			b.pos.x = rand(100, w-100);
//			b.pos.y = rand(100, h-100);
//			b.pos.x = w / 2.f;
//			b.pos.y = h / 2.f;

			float t = rand(0, 2.f * 3.1415f);
			float r = rand(200, 250);

			b.pos.x = w / 2.f + r * cos(t);
			b.pos.y = h / 2.f + r * sin(t);

			b.vel.x = 200.f * cos(t+3.1415/2.f);
			b.vel.y = 200.f * sin(t+3.1415/2.f);
		}

		return true;
	}

	void TweenTest::update(const Time & delta)
	{
		const float g = 9.81f * 20.f;
		const float dt = delta.s();

		sf::Vector2u winSize = m_window.getSize();
		float w = winSize.x;
		float h = winSize.y;

		sf::Vector2i imouse = sf::Mouse::getPosition(m_window);
		Vector2f mouse(imouse.x, imouse.y);
		mouse.x = imouse.x;
		mouse.y = winSize.y - imouse.y;

		Vector2f u;
		float k, d, t;

		for(unsigned int i = 0; i < balls.size(); i++)
		{
			Ball & b = balls[i];
			// Gravity
//			b.vel.y -= g * dt;

			// Attraction
			if(i != 0)
			{
				u = balls[0].pos - b.pos;
				d = u.length();
				u.normalize();
				k = dt * 5000000.f / (d * d + 400.f);
				b.vel += u * k;
			}

			// Friction
			b.vel.x = brake(b.vel.x, 0, 0.0001f, dt);
			b.vel.y = brake(b.vel.y, 0, 0.0001f, dt);

			// Application
			b.pos += b.vel * dt;

			// Border collisions
//			if(b.pos.y < 0)
//			{
//				b.pos.y = -b.pos.y;
//				b.vel.y = -b.vel.y;
//			}
//			if(b.pos.y > h)
//			{
//				b.pos.y = 2.f * h - b.pos.y;
//				b.vel.y = -b.vel.y;
//			}
//			if(b.pos.x < 0)
//			{
//				b.pos.x = -b.pos.x;
//				b.vel.x = -b.vel.x;
//			}
//			if(b.pos.x > w)
//			{
//				b.pos.x = 2.f * w - b.pos.x;
//				b.vel.x = -b.vel.x;
//			}
		}
	}

	void TweenTest::renderScene(const Time & delta)
	{
		// Pixel-match view
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, m_window.getSize().x, 0, m_window.getSize().y);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3ub(64,64,64);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//		glPointSize(4);
		//glBegin(GL_POINTS);

		for(auto & b : balls)
		{
			//glVertex2f(b.pos.x, b.pos.y);
			gl::fillCircle(b.pos.x, b.pos.y, b.r);
		}

		//glEnd();
	}

	void TweenTest::renderGUI(const Time & delta)
	{

	}

	void TweenTest::processEvent(const sf::Event & event)
	{

	}

	void TweenTest::dispose()
	{

	}

} // namespace experimental



