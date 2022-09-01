#pragma once

#include <list>

#include "global.h"
#include "Gem.h"
#include "Selector.h"
#include "DSU.h"
#include "Bonus.h"

namespace NGems {

	class TGame {
	public:
		TGame() : mWindow({Global::kWindowWidth, Global::kWindowHeight}, "GEMS") {
			mWindow.setFramerateLimit(60);
		}
		void Start();
	private:
		void spawnGems();
		void run();
		void redraw();

		bool updateField();
	private:
		sf::RenderWindow mWindow;
		std::vector<std::vector<TGem>> field;
		TSelector swapper;
		size_t score{ 0 };
	};
}

struct GemsGame {
	static void Run();
};