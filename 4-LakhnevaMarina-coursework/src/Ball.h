#pragma once

#include "global.h"
#include "Collider.h"
#include "MovingObject.h"
#include "Platform.h"
#include "Brick.h"

namespace NArkanoid {

    class TBall : public TCircleCollider {
        friend class TGameInstance;

    public:
        TBall(IGame& game, const sf::Vector2f& position) : TCircleCollider(game, shape) {
            SetSpeed({ Global::kBallSpeedX, -Global::kBallSpeedY });
            shape.setRadius(Global::kBallRadius);
            shape.setPosition(position);
        }

        bool IsAlive();

        virtual void Update() override;
        virtual void Move() override;
        virtual void Draw() override;

    private:
        sf::CircleShape shape;
        bool alive{ true };
    };
}