#pragma once

#include <SFML/Graphics.hpp>

#include "global.h"
#include "Collider.h"
#include "MovingObject.h"

namespace NArkanoid {

    class TPlatform : public TBoxCollider {
    public:
        TPlatform(IGame& game, const sf::Vector2f& position) : TBoxCollider(game, shape) {
            shape.setSize({ Global::kPlatformWidth, Global::kPlatformHeight });
            shape.setPosition(position);
        }

        virtual void Update() override;
        virtual void Move() override;
        virtual void Draw() override;

    private:
        sf::RectangleShape shape;
    };

}