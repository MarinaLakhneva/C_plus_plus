#include "Brick.h"

bool NArkanoid::TBrick::IsDestroyed() {
	return destroyed;
}

bool NArkanoid::TBrick::IsDestructible() {
	return true;
}

void NArkanoid::TBrick::Update(){

}

void NArkanoid::TBrick::Draw() {
	game.GetWindow().draw(shape);
}

void NArkanoid::TBrick::Move() {

}

void NArkanoid::TBrick::Disappear() {
	game.IncScore();
	destroyed = true;
}

bool NArkanoid::TIndestructibleBrick::IsDestructible() {
	return false;
}

void NArkanoid::TIndestructibleBrick::Disappear() {

}

void NArkanoid::TBonusBrick::Disappear() {
	game.SpawnPill(shape.getPosition());
	TBrick::Disappear();
}

void NArkanoid::THelpBrick::Disappear() {
	if (--hp == 0) {
		destroyed = true;
		game.DestroyHelpBrick();
	}
}

void NArkanoid::THelpBrick::Move() {
	shape.move(speed);
}

void NArkanoid::THelpBrick::Update() {
	// Обработка столкновений с границами окна
	if ( (Left() < 0) || ( (float)game.GetWindow().getSize().x < Right()) ) {
		RotateX();
	}
	Move();
}

void NArkanoid::TAccelerationBrick::Disappear() {
	game.Speedup();
	TBrick::Disappear();
}
