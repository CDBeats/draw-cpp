#include "Game.hpp"
#include "Constants.hpp"
#include <raylib.h>

Game::Game() { pause(); }

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
    if (timeScale > 1.f)
        return;
    paused = true;
}

void Game::unpause()
{
    timeScale = 10.f;
    if (timeScale < 2.f)
        return;

    paused = false;
}

void Game::handlePause()
{
    // Pause logic manipulates deltaTime
    if (paused)
    {
        if (timeScale < 10.f)
            timeScale += 0.005f;
        else
            timeScale = 100000.f;
    }
    else
    {
        if (timeScale > 1.f)
            timeScale -= 0.005f;
        else
            timeScale = 1.f;
    }
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

        previousWidth = GetScreenWidth();
        previousHeight = GetScreenHeight();
    }
}

void Game::update()
{
    handleInput();
    handleResize();
    handlePause();

    deltaTime = GetFrameTime();
    gameSpeed += gameAcceleration * deltaTime / timeScale;
    gameDisplacement = gameSpeed * deltaTime / timeScale;

    // Update game objects
    background.update(gameDisplacement * 0.8f);
    obstacles.update(gameDisplacement);
    player.update(deltaTime / timeScale, gameSpeed);
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