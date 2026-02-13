#include "Game.hpp"
#include "Constants.hpp"
#include <raylib.h>

Game::Game()
{
    togglePause();
}

Game::~Game() {}

void Game::run()
{
    while (!WindowShouldClose())
    {
        update();
        render();
    }
}

void Game::togglePause()
{
    if ((!paused && gameSpeed < pauseTargetSpeed) || (paused && gameSpeed > 0.f))
        return; // Ignore toggle while decelerating / rebounding

    paused = !paused;

    if (paused)
    {
        pauseTargetSpeed = gameSpeed; // store the speed at the moment of pause
    }
}

void Game::update()
{
    handleInput();

    // Get time elapsed since last frame seconds (capped to avoid large jumps on window resize)
    float deltaTime = std::min(GetFrameTime(), 1.0f / FRAMERATE);
    float gameAcceleration = 0.f;
    float gameDisplacement = 0.f;

    if (paused)
    {
        if (gameSpeed > 0.f)
        {
            gameAcceleration = G_PAUSE_DECELLERATION;
        }
        else
        {
            gameSpeed = 0.f;
        }
        // Update pause screen
    }
    else
    {
        if (gameSpeed < pauseTargetSpeed)
        {
            gameAcceleration = -G_PAUSE_DECELLERATION;
        }
        else
        {
            gameAcceleration = G_CONSTANT_ACCELERATION;
        }
    }

    gameSpeed += gameAcceleration * deltaTime;
    // Calculate displacement this frame in pixels
    gameDisplacement = gameSpeed * deltaTime;
    // Update game objects by moving them left by displacement
    background.update(gameDisplacement * 0.9f); // Move background slightly slower for parallax effect
    obstacles.update(gameDisplacement);
    player.update(deltaTime);
}

void Game::handleInput()
{
    // Quit the game when ESC is pressed
    if (IsKeyPressed(KEY_ESCAPE)) // Detect once per press
    {
        togglePause();
    }

    // W,Space,↑ | A,← | D,→
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        player.jump();
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        player.moveLeft();
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        player.moveRight();
    }
}

void Game::render()
{
    BeginDrawing();
    ClearBackground(Color{255, 255, 255, 255});

    // Draw background
    background.draw();
    obstacles.draw();
    player.draw();

    DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, BLACK);
    DrawText(TextFormat("Game Speed: %.2f", gameSpeed), 10, 30, 20, BLACK);

    EndDrawing();
}