#pragma once

namespace NArkanoid {
    namespace Global {

        static constexpr unsigned int kWindowHeight = 720;
        static constexpr unsigned int kWindowWidth = 480;

        static constexpr int kIterationsPerFrame = 16;

        static constexpr float kPlatformSpeed = .4f;
        static constexpr float kPlatformWidth = 60.f;
        static constexpr float kPlatformHeight = 12.f;

        static constexpr float kBallRadius = 6.f;
        static constexpr int kBallAcceleration = 4;
        static constexpr float kBallSpeedX = .1f;
        static constexpr float kBallSpeedY = .2f;

        static constexpr int kBricksCountX = 5;
        static constexpr int kBricksCountY = 8;
        static constexpr int kBricksGap = 5;

        static constexpr int kBrickWidth = (kWindowWidth - kBricksGap) / kBricksCountX - kBricksGap;
        static constexpr int kBrickHeight = (kWindowHeight - kBricksGap) / kBricksCountY / 2 - kBricksGap;

        static constexpr float kPillWidth = kBrickWidth / 2.f;
        static constexpr float kPillHeight = kBrickHeight / 2.f;
        static constexpr float kPillFallingSpeed = .15f;
    }
}
