#pragma once
#include "Constants.hpp"
#include "Background.hpp"
#include "Obstacles.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    Background background;
    Obstacles obstacles;

    void init();
    void togglePause();
    void update();
    void handleInput();

    void render();

    bool paused;
    float gameSpeed;
    float pauseTargetSpeed;
};