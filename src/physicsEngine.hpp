#pragma once

#include <iostream>
#include <vector>

#include "confetto.hpp"
#include "math.hpp"
#include "time.hpp"

#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272

#define AIR_RESISTANCE 0.97f // 3% sap
#define GRAVITY 1.10f // 10% pull

struct physicsManager
{
    physicsManager() : explosion(0)
    {
        this->colors.push_back(COLOR_BLANCHED_ALMOND);
        this->colors.push_back(COLOR_LIGHT_YELLOW);
        this->colors.push_back(COLOR_LIGHT_GREEN);
        this->colors.push_back(COLOR_LIGHT_BLUE);
        this->colors.push_back(COLOR_LIME_GREEN);
        this->colors.push_back(COLOR_MAGENTA);
        this->colors.push_back(COLOR_YELLOW);
        this->colors.push_back(COLOR_ORANGE);
        this->colors.push_back(COLOR_TOMATO);
        this->colors.push_back(COLOR_WHITE);
        this->colors.push_back(COLOR_PINK);
        this->colors.push_back(COLOR_LIME);
        this->colors.push_back(COLOR_AQUA);
    }

    void explosionInit()
    {
        int explosionSize = 2000;
        for (int i = 0; i < explosionSize; ++i)
        {
            this->confetti.emplace_back(Confetto(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3,
                this->colors[Math::Random(0, this->colors.size())], {Math::Random(-20, 20), Math::Random(-60, 10)},
                Shapes(Math::Random(0, Shapes::shapesLength) - 1)
                ));
        }
    }

    void updateExplosion(Time::Timer& time)
    {
        static int millisFromLastFrame{};
        millisFromLastFrame += time.ElapsedMillis();

        time.Reset();

        if (millisFromLastFrame <= 20)
            return;
        
        millisFromLastFrame -= 20;

        pros::screen::erase();
        if (confetti.size() == 0)
        {
            this->clearExplosion();
            this->explosion = 0;
            return;
        }
        
        for (int i = 0; i < confetti.size(); ++i)
        {
            confetti[i].render();
            confetti[i].velocity *= AIR_RESISTANCE;
            confetti[i].velocity.y += GRAVITY;
            confetti[i].updateCoords();

            if (confetti[i].rect.y > SCREEN_HEIGHT)
                confetti.erase(confetti.begin() + i);
        }
    }

    void clearExplosion()
    {
        this->confetti.clear();
    }

    std::vector<Confetto> confetti;
    std::vector<uint32_t> colors;

    bool explosion;
};