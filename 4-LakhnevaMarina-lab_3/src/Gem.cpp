#include "Gem.h"

namespace NGems {
	bool TGem::IsEmpty() {
		return mColor == GemColor::EMPTY;
	}

	GemColor TGem::GetColor() {
		return mColor;
	}

	void TGem::SetColor(GemColor color) {
		mColor = color;
		fillColor = getColor(color);
		shape.setFillColor(fillColor);
	}

	void TGem::Select() {
		shape.setFillColor(sf::Color::White);
		selected = true;
	}

	void TGem::Unselect() {
		shape.setFillColor(fillColor);
		selected = false;
	}

	void TGem::Draw() {
		window.draw(shape);
	}

	void TGem::Swap(TGem* other) {
		if (other == this) {
			return;
		}
		std::swap(fillColor, other->fillColor);
		std::swap(mColor, other->mColor);

		other->shape.setFillColor(other->fillColor);
		shape.setFillColor(fillColor);
	}

	bool TGem::Match(TGem& other) {
		return mColor == other.mColor;
	}

	bool TGem::IsNeighbor(const TGem& other) const {
		return (i == other.i && std::abs(j - other.j) == 1) ||
			(j == other.j && std::abs(i - other.i) == 1);
	}

	bool TGem::Contains(const sf::Vector2i& pos) const {
		return
			pos.x > shape.getPosition().x &&
			pos.y > shape.getPosition().y &&
			pos.x < shape.getPosition().x + shape.getSize().x &&
			pos.y < shape.getPosition().y + shape.getSize().y;
	}

	void TGem::FallTo(const sf::Vector2f& position) {
		shape.setPosition(position);
	}

	sf::Color TGem::getColor(GemColor colorID) {
		switch (colorID) {
		case RED:
			return sf::Color::Red;
		case BLUE:
			return sf::Color::Blue;
		case GREEN:
			return sf::Color::Green;
		case PURPLE:
			return sf::Color{ 128, 0, 128, 255 };
		case YELLOW:
			return sf::Color::Yellow;
		}
		return sf::Color::Black;
	}
}
