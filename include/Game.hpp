#pragma once
#include "Constants.hpp"
#include "Background.hpp"
#include "Obstacles.hpp"
#include "Player.hpp"

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    Background background;
    Obstacles obstacles;
    Player player;

    void togglePause();
    void update();
    void handleInput();

    void render();

    bool paused = false;
    float gameSpeed;
    float pauseTargetSpeed;
};