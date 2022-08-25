#pragma once

#include <list>

#include <SFML/Graphics.hpp>

namespace NArkanoid {

    class TPlatform;
    class TBall;
    class TBrick;
    class TPill;

    class IGame { 
    public:
        virtual void IncScore() = 0; // метод увеличения очков на единицу

        virtual TPlatform& GetPlatform() = 0;
        virtual std::list<std::shared_ptr<TBall>>& GetBalls() = 0;
        virtual std::list<std::shared_ptr<TBrick>>& GetBricks() = 0;
        virtual sf::RenderWindow& GetWindow() = 0;
        virtual void SpawnBall() = 0;
        virtual void SpawnPill(const sf::Vector2f& position) = 0;


        virtual void SpawnHelpBrick() = 0; // блок, который двигается и живет до трех ударов
        virtual void DestroyHelpBrick() = 0;

        virtual void Speedup() = 0;
    };

}