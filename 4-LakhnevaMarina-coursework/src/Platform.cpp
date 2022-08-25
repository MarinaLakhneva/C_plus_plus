#include "Platform.h"

void NArkanoid::TPlatform::Update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && Left() > 0) {
        SetSpeed({ -Global::kPlatformSpeed, 0 });
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && Right() < game.GetWindow().getSize().x) {
        SetSpeed({ Global::kPlatformSpeed, 0 });
    }
    else {
        SetSpeed({ 0, 0 });
    }
    Move();
}

void NArkanoid::TPlatform::Move() {
    shape.move(speed);
}

void NArkanoid::TPlatform::Draw() {
    game.GetWindow().draw(shape);
}
