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

    void update();
    void render();

    void pause();
    void unpause();
    void handleInput();
    void handleResize();

    int previousWidth = INITIAL_WINDOW;
    int previousHeight = INITIAL_WINDOW;

    bool paused = false;
    float gameSpeed;
    float pauseTargetSpeed;
    enum Direction
    {
        left,
        right
    };
};