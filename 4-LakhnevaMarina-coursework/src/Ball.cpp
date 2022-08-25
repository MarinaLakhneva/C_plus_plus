#include "Ball.h"

void NArkanoid::TBall::Update() {
    // Обработка столкновений с границами окна
    if ( (Left() < 0) || ((float)game.GetWindow().getSize().x < Right()) ) {
        RotateX();
    }

    if (Top() < 0) {
        RotateY();
    }

    if ( (float)game.GetWindow().getSize().y < Bottom() ) {
        alive = false;
        return;
    }

    // Обработка столкновения с платформой
    if (Collide(this, &game.GetPlatform()) < 0 && (Bottom() < game.GetPlatform().Bottom() ) ) {
        RotateY();
    }

    bool handleX = true;
    bool handleY = true;

    // Обработка столкновений с блоками
    for (auto& brick : game.GetBricks()) {
        if (brick->IsDestroyed()) {
            continue;
        }

        if (int orient = Collide(this, brick.get())) {
            brick->Disappear();
            if (handleX && orient > 0) {
                RotateX();
                handleX = false;
            }
            if (handleY && orient < 0) {
                RotateY();
                handleY = false;
            }
        }
    }

    // Обработка столкновений с другими мячиками
    for (auto& other : game.GetBalls()) {
        if (other.get() == this) {
            continue;
        }
        if (int orient = Collide(this, other.get())) {
            if (handleX && orient > 0) {
                RotateX();
                handleX = false;
            }
            if (handleY && orient < 0) {
                RotateY();
                handleY = false;
            }
        }
    }
	Move();
}

bool NArkanoid::TBall::IsAlive() {
    return alive;
}

void NArkanoid::TBall::Move() {
    shape.move(speed);
}

void NArkanoid::TBall::Draw() {
    game.GetWindow().draw(shape);
}
