#include "Pill.h"

void NArkanoid::TPill::Update() {
	if (Collide(&game.GetPlatform(), this)) {
		Destroy();
		Activate();
		return;
	}
	if (((float)game.GetWindow().getSize().y < Bottom())) {
		Destroy();
	}
	Move();
}

void NArkanoid::TPill::Draw() {
	game.GetWindow().draw(shape);
}

void NArkanoid::TPill::Destroy() {
	destroyed = true;
}

bool NArkanoid::TPill::IsDestroyed() {
	return destroyed;
}

void NArkanoid::TPill::Move() {
	shape.move(speed);
}

void NArkanoid::TExtraBallPill::Activate() {
	game.SpawnBall();
}

void NArkanoid::THelpBrickPill::Activate() {
	game.SpawnHelpBrick();
}
