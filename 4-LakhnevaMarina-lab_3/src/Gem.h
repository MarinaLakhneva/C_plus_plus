#pragma once

#include "global.h"

namespace NGems {

	class TGem {
	public:
		TGem(sf::RenderWindow& window, const sf::Vector2f& position, GemColor color, int i, int j) : window(window), i(i), j(j) {
			shape.setPosition(position);
			shape.setSize({ Global::kGemSize, Global::kGemSize });
			fillColor = getColor(color);
			shape.setFillColor(fillColor);
			mColor = color;
		}
		bool IsEmpty();

		GemColor GetColor();

		void SetColor(GemColor color);
		void Select();
		void Unselect();
		void Draw();
		void Swap(TGem* other);

		bool Match(TGem& other);
		bool IsNeighbor(const TGem& other) const;
		bool Contains(const sf::Vector2i& pos) const;

		void FallTo(const sf::Vector2f& position);

		int I() { return i; }
		int J() { return j; }
	private:
		static sf::Color getColor(GemColor colorID);
	private:
		sf::RenderWindow& window;
		sf::RectangleShape shape;
		sf::Color fillColor;
		GemColor mColor;
		int i, j;
		bool selected{ false };
	};
}