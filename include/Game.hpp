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
    void handlePause();

    int previousWidth = INITIAL_WINDOW;
    int previousHeight = INITIAL_WINDOW;

    bool paused = false;
    float gameAcceleration = G_CONSTANT_ACCELERATION * INITIAL_WINDOW;
    float gameSpeed = G_INITIAL_SPEED * INITIAL_WINDOW;
    float gameDisplacement;

    float timeScale = 1.f;
    float deltaTime;

    enum Direction
    {
        left,
        right
    };
};