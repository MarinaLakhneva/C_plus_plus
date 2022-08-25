#pragma once

#include "global.h"
#include "Collider.h"
#include "GameObject.h"
#include "MovingObject.h"
#include "Platform.h"

namespace NArkanoid {

	class TPill : public TBoxCollider {
	public:
		TPill(IGame& game, const sf::Vector2f& position, sf::Color color) : TBoxCollider(game, shape) {
			shape.setSize({ Global::kPillWidth, Global::kPillHeight });
			shape.setPosition(position);
			shape.setFillColor(color);
			SetSpeed({ 0, Global::kPillFallingSpeed });
		}

		virtual void Activate() = 0;

		void Update() override;
		void Move() override;
		void Draw() override;

		void Destroy();
		bool IsDestroyed();


	private:
		sf::RectangleShape shape;
		bool destroyed{ false };
	};

	class TExtraBallPill : public TPill {
	public:
		TExtraBallPill(IGame& game, const sf::Vector2f& position) : TPill(game, position, sf::Color::Cyan) {}

		virtual void Activate() override;
	};

	class THelpBrickPill : public TPill {
	public:
		THelpBrickPill(IGame& game, const sf::Vector2f& position) : TPill(game, position, sf::Color::Green) {}

		virtual void Activate() override;
	};
}