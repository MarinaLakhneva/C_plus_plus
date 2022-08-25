#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "global.h"
#include "Collider.h"
#include "GameObject.h"
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include "Pill.h"

namespace NArkanoid {

    class TGameInstance : public IGame {
    public:
        TGameInstance(const sf::Vector2f& platform_pos);

        virtual void IncScore() override;

        virtual TPlatform& GetPlatform() override;
        virtual std::list<std::shared_ptr<TBall>>& GetBalls() override;
        virtual std::list<std::shared_ptr<TBrick>>& GetBricks() override;
        virtual sf::RenderWindow& GetWindow() override;
        virtual void SpawnBall() override;
        virtual void SpawnPill(const sf::Vector2f& position) override;

        virtual void SpawnHelpBrick() override;
        virtual void DestroyHelpBrick() override;

        void Start();
        void Run();

        virtual void Speedup() override;

    private:
        // Создаёт блоки
        void SpawnBricks();

    private:
        sf::RenderWindow mWindow;

        TPlatform mPlatform;

        std::list<std::shared_ptr<TBrick>> bricks;
        std::list<std::shared_ptr<TPill>> pills;
        std::list<std::shared_ptr<TBall>> balls;

        unsigned long score{ 0 };

        bool hasHelpBrick{ false };

        int fps{ Global::kIterationsPerFrame };
    };

}

class ArkanoidGame {
public:
    static void Run();
};
