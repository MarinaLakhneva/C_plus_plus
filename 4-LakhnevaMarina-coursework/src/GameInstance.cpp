#include "GameInstance.h"

namespace NArkanoid {

    TGameInstance::TGameInstance(const sf::Vector2f& platform_pos)
        : mWindow({ Global::kWindowWidth, Global::kWindowHeight }, "Arkanoid GUI"),
        mPlatform(*this, platform_pos) {
        // FPS
        mWindow.setFramerateLimit(60);
    }

    void TGameInstance::IncScore() {
        score++;
    }

    void TGameInstance::Start() {
        // Случайность
        std::srand((unsigned int)std::time(NULL));

        // Шарик
        SpawnBall();

        // Блоки
        SpawnBricks();

        Run();

        std::cout << "Your score: " << score << " \n";
        mWindow.close();
    }

    void TGameInstance::Run() {
        while (true) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                return;
            }

            for (int i = 0; i < fps; ++i) {
                mPlatform.Update();
                for (auto brick : bricks) {
                    brick->Update();
                }
                for (auto ball : balls) {
                    ball->Update();
                }
                for (auto pill : pills) {
                    pill->Update();
                }

                // Удаляем упавшие шарики
                auto ballsIter = balls.begin();
                while (ballsIter != balls.end()) {
                    if ((*ballsIter)->IsAlive()) {
                        ballsIter++;
                        continue;
                    }
                    ballsIter = balls.erase(ballsIter);
                }

                // Удаляем активированные и упавшие бонусы
                auto pillsIter = pills.begin();
                while (pillsIter != pills.end()) {
                    if ((*pillsIter)->IsDestroyed()) {
                        pillsIter = pills.erase(pillsIter);
                        continue;
                    }
                    pillsIter++;
                }

                // Если шариков нет, проигрыш
                if (balls.empty()) {
                    std::cout << "\n\n[[[[ You lose! ]]]]\n\n";
                    return;
                }

                // Удаляем блоки
                bool win = true;
                auto it = bricks.begin();

                while (it != bricks.end()) {
                    if ((*it)->IsDestroyed()) {
                        it = bricks.erase(it);
                        continue;
                    }

                    if (win && (*it)->IsDestructible()) {
                        win = false;
                    }
                    it++;
                }

                if (win) {
                    std::cout << "\n\n[[[[ You win! ]]]]\n\n";
                    return;
                }
            }

            mWindow.clear(sf::Color::Black);
            mPlatform.Draw();

            for (auto& ball : balls) {
                ball->Draw();
            }

            for (auto brick : bricks) {
                brick->Draw();
            }

            for (auto pill : pills) {
                pill->Draw();
            }
            mWindow.display();
        }
    }

    void TGameInstance::Speedup() {
        fps += Global::kBallAcceleration;
    }

    TPlatform& TGameInstance::GetPlatform() {
        return mPlatform;
    }

    std::list<std::shared_ptr<TBall>>& TGameInstance::GetBalls() {
        return balls;
    }

    std::list<std::shared_ptr<TBrick>>& TGameInstance::GetBricks() {
        return bricks;
    }

    sf::RenderWindow& TGameInstance::GetWindow() {
        return mWindow;
    }

    void TGameInstance::SpawnBall() {
        balls.emplace_back(std::make_shared<TBall>(*this, sf::Vector2f{ Global::kWindowWidth / 2.f, Global::kWindowHeight * 2.f / 3.f }));
    }

    void TGameInstance::SpawnPill(const sf::Vector2f& position) {
        auto randInt = rand();
        if (randInt % 2) {
            pills.emplace_back(std::make_shared<NArkanoid::TExtraBallPill>(*this, position));
            return;
        }
        pills.emplace_back(std::make_shared<NArkanoid::THelpBrickPill>(*this, position));
    }

    void TGameInstance::SpawnBricks() {
        int id = 0;
        for (int i = 0; i < Global::kBricksCountY; ++i) {
            for (int j = 0; j < Global::kBricksCountX; ++j, ++id) {
                sf::Vector2f pos{
                        Global::kBricksGap + (float)j * (Global::kBrickWidth + Global::kBricksGap),
                        Global::kBricksGap + (float)i * (Global::kBrickHeight + Global::kBricksGap)
                };

                if (id % 7 == 0) {
                    bricks.emplace_front(std::make_shared<TIndestructibleBrick>(*this, pos));
                    continue;
                }
                if (id % 17 == 0) {
                    bricks.emplace_front(std::make_shared<TAccelerationBrick>(*this, pos));
                    continue;
                }
                if (id % 8 == 0) {
                    bricks.emplace_front(std::make_shared<TBonusBrick>(*this, pos));
                    continue;
                }
                bricks.emplace_front(std::make_shared<TDefaultBrick>(*this, pos));
            }
        }

    }

    void TGameInstance::SpawnHelpBrick() {
        if (!hasHelpBrick) {
            bricks.emplace_front(std::make_shared<THelpBrick>(*this));
            hasHelpBrick = true;
        }
    }

    void TGameInstance::DestroyHelpBrick() {
        hasHelpBrick = false;
    }

}

void ArkanoidGame::Run() {
    NArkanoid::TGameInstance game({ NArkanoid::Global::kWindowWidth / 2.f, NArkanoid::Global::kWindowHeight - 40.f });
    game.Start();
}