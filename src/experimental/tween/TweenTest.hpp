#ifndef TWEENTEST_HPP_INCLUDED
#define TWEENTEST_HPP_INCLUDED

#include "engine/game/BasicGame.hpp"

namespace experimental
{
	class TweenTest : public zn::ABasicGame
	{
	public :

		TweenTest() : ABasicGame(1600, 1000, "Tween test")
		{}

		virtual ~TweenTest()
		{}

	protected :

		bool init() override;

		void update(const zn::Time & delta) override;

		void renderScene(const zn::Time & delta) override;

		void renderGUI(const zn::Time & delta) override;

		void processEvent(const sf::Event & event) override;

		void dispose() override;

	};

} // namespace experimental

#endif // TWEENTEST_HPP_INCLUDED
