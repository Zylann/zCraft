#ifndef TWEENTEST_HPP_INCLUDED
#define TWEENTEST_HPP_INCLUDED

#include "engine/BasicGame.hpp"

namespace experimental
{
	class TweenTest : public engine::ABasicGame
	{
	public :

		TweenTest() : ABasicGame(1600, 1000, "Tween test")
		{}

		virtual ~TweenTest()
		{}

	protected :

		bool init() override;

		void update(const engine::Time & delta) override;

		void renderScene(const engine::Time & delta) override;

		void renderGUI(const engine::Time & delta) override;

		void processEvent(const sf::Event & event) override;

		void dispose() override;

	};

} // namespace experimental

#endif // TWEENTEST_HPP_INCLUDED
