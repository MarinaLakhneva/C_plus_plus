#pragma once
#include "GameObject.h"

namespace NArkanoid {

    class TMovingObject : public TGameObject {
    protected:
        TMovingObject(IGame& game) : TGameObject(game) {}

        void SetSpeed(const sf::Vector2f& speed);
        const sf::Vector2f& GetSpeed() const;

        virtual void Move() = 0;
        void RotateX();
        void RotateY();

    protected:
        sf::Vector2f speed;
    };

}