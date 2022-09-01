#pragma once

#include <SFML/Graphics.hpp>


namespace NGems {
	
	namespace Global {

		static constexpr int kWindowWidth = 455;
		static constexpr int kWindowHeight = 680;

		static constexpr int kGemsCountX = 10;
		static constexpr int kGemsCountY = 15;

		static constexpr float kGemSize = 40.f;

		static constexpr float kGemsGap = 5.f;

	}

	enum GemColor {
		RED = 0, GREEN = 1, BLUE = 2, PURPLE = 3, YELLOW = 4, EMPTY = 5
	};
}
