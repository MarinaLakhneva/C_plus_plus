#pragma once

#include "global.h"
#include "Game.h"
#include "MovingObject.h"
#include <SFML/Graphics.hpp>

namespace NArkanoid {

    class ICollider : public TMovingObject {
    protected:
        ICollider(IGame& game) : TMovingObject(game) {}

        virtual float x() = 0;
        virtual float y() = 0;

    public:
        virtual float Left() = 0;
        virtual float Right() = 0;
        virtual float Top() = 0;
        virtual float Bottom() = 0;
    };

    class TBoxCollider : public ICollider {
    public:
        TBoxCollider(IGame& game, sf::RectangleShape& shape) : rect(shape), ICollider(game) {}

    protected:
        virtual float x() override;
        virtual float y() override;

    public:
        virtual float Left() override;
        virtual float Right() override;
        virtual float Top() override;
        virtual float Bottom() override;

    private:
        sf::RectangleShape& rect;
    };

    class TCircleCollider : public ICollider {
    public:
        TCircleCollider(IGame& game, sf::CircleShape& shape) : circle(shape), ICollider(game) {}

    protected:
        virtual float x() override;
        virtual float y() override;

    public:
        virtual float Left() override;
        virtual float Right() override;
        virtual float Top() override;
        virtual float Bottom() override;

    private:
        sf::CircleShape& circle;
    };

    int Collide(ICollider*, ICollider*);
}