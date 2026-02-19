#include "Game.hpp"
#include "Constants.hpp"
#include <raylib.h>

Game::Game()
{
    pause();
    gameSpeed = G_INITIAL_SPEED * INITIAL_WINDOW;
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

void Game::pause()
{
    if (gameSpeed < pauseTargetSpeed)
        return;
    pauseTargetSpeed = gameSpeed;
    paused = true;
}

void Game::unpause()
{
    if (gameSpeed > 0.f)
        return;

    paused = false;
}

void Game::handleResize()
{
    if (IsWindowResized())
    {
        pause();
        int w = GetScreenWidth();
        int h = GetScreenHeight();

        if (previousWidth != w)
            SetWindowSize(w, w);
        if (previousHeight != h || IsWindowMaximized())
            SetWindowSize(h, h);
        pauseTargetSpeed /= previousHeight;
        pauseTargetSpeed *= GetScreenHeight();

        previousWidth = GetScreenWidth();
        previousHeight = GetScreenHeight();
    }
}

void Game::update()
{
    handleInput();
    handleResize();

    // Get time elapsed since last frame seconds (capped to avoid large jumps on window resize)
    float deltaTime = GetFrameTime();
    float gameAcceleration = 0.f;
    float gameDisplacement = 0.f;

    if (paused)
    {
        if (gameSpeed > 0.f)
        {
            gameAcceleration = G_PAUSE_DECELLERATION * GetScreenHeight(); // decelerate
        }
        else
        {
            gameSpeed = 0.f;
        }
    }
    else // running
    {
        if (gameSpeed < pauseTargetSpeed)
        {
            gameAcceleration = -G_PAUSE_DECELLERATION * GetScreenHeight(); // recover to pause speed
        }
        else
        {
            gameAcceleration = G_CONSTANT_ACCELERATION * GetScreenHeight();
        }
    }

    gameSpeed /= previousHeight;
    gameSpeed *= GetScreenHeight();
    gameSpeed += gameAcceleration * deltaTime;
    // Calculate displacement this frame in pixels
    gameDisplacement = gameSpeed * deltaTime;
    // Update game objects by moving them left by displacement
    background.update(gameDisplacement * 0.9f); // Move background slightly slower for parallax effect
    obstacles.update(gameDisplacement);
    player.update(deltaTime, gameSpeed);
}

void Game::handleInput()
{
    // Quit the game when ESC is pressed
    if (IsKeyPressed(KEY_ESCAPE)) // Detect once per press
    {
        if (!paused)
            pause();
        else
            unpause();
    }

    // W,Space,↑ | A,← | D,→
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP))
    {
        player.jump();
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        player.move(left);
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        player.move(right);
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