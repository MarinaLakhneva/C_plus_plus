#pragma once

#include "Collider.h"
#include "GameObject.h"
#include "Pill.h"

#include <iostream>

namespace NArkanoid {

    class TBrick : public TBoxCollider {
    public:
        virtual void Disappear();
        virtual bool IsDestroyed();
        virtual bool IsDestructible();

        virtual void Update() override;
        virtual void Move() override;
        virtual void Draw() override;

    protected:
        TBrick(IGame& game, const sf::Vector2f& position) : TBoxCollider(game, shape) {
            shape.setSize({ Global::kBrickWidth, Global::kBrickHeight });
            shape.setPosition(position);
        }
    protected:
        sf::RectangleShape shape;
        bool destroyed{false};
    };

    class TDefaultBrick : public TBrick {
    public:
        TDefaultBrick(IGame& game, const sf::Vector2f& position) : TBrick(game, position) {
            shape.setFillColor(fillColor);
        }

    private:
        sf::Color fillColor{ (sf::Uint8)201, (sf::Uint8)91, (sf::Uint8)15, (sf::Uint8)255 };
    };

    class TIndestructibleBrick : public TBrick {
    public:
        TIndestructibleBrick(IGame& game, const sf::Vector2f& position) : TBrick(game, position) {
            shape.setFillColor(fillColor);
        }

        virtual bool IsDestructible() override;
        virtual void Disappear() override;

    private:
        sf::Color fillColor{ (sf::Uint8)100, (sf::Uint8)100, (sf::Uint8)100, (sf::Uint8)255 };
    };

    class TAccelerationBrick : public TBrick {
    public:
        TAccelerationBrick(IGame& game, const sf::Vector2f& position) : TBrick(game, position) {
            shape.setFillColor(fillColor);
        }

        virtual void Disappear() override;

    private:
        sf::Color fillColor{ (sf::Uint8)15, (sf::Uint8)50, (sf::Uint8)100, (sf::Uint8)255 };
    };

    class TBonusBrick : public TBrick {
    public:
        TBonusBrick(IGame& game, const sf::Vector2f& position) : TBrick(game, position) {
            shape.setFillColor(fillColor);
        }

        virtual void Disappear() override;

    private:
        sf::Color fillColor{ (sf::Uint8)133, (sf::Uint8)15, (sf::Uint8)255, (sf::Uint8)255 };
    };

    class THelpBrick : public TBrick {
    public:
        THelpBrick(IGame& game) : TBrick(game, sf::Vector2f{ Global::kWindowWidth / 2.f, Global::kWindowHeight * 0.75f }) {
            shape.setFillColor(fillColor);
            SetSpeed({ Global::kBallSpeedX, 0 });
            hp = 3;
        }

        virtual void Disappear() override;
        virtual void Move() override;
        virtual void Update() override;

    private:
        sf::Color fillColor{ sf::Color::Yellow };
        int hp;
    };
}