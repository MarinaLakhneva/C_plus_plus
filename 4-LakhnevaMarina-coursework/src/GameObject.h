#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"

namespace NArkanoid {

	class TGameInstance;

	class TGameObject {
	public:
		virtual void Update() = 0;
		virtual void Draw() = 0;

	protected:
		TGameObject(IGame& game) : game(game) {}

	protected:
		IGame& game;
	};
}