#include "Player.hpp"
#include "Constants.hpp"
#include <raylib.h>
#include <raymath.h>

Player::Player() : x(200.f), y(200.f), vx(0.f), vy(0.f) {}
Player::~Player() {}

void Player::jump()
{
    vy = P_V_JUMP;
    // Placeholder for jump logic (e.g., apply upward velocity)
}

void Player::moveLeft()
{
    vx -= P_AX * DT;
}

void Player::moveRight()
{
    vx += P_AX * DT;
}

void Player::update(float dt)
{
    vx = Clamp(vx, -P_VX_MAX, P_VX_MAX);
    vy += P_GRAVITY * dt;
    vy = Clamp(vy, -P_VY_MAX, P_VY_MAX);
    DT = dt;
    x += vx * dt;
    y += vy * dt;
}

void Player::draw()
{
    DrawRectangleRounded({x - P_SIZE * .5f, y - P_SIZE * 2.f, P_SIZE, P_SIZE * 2.f}, P_SIZE * 0.5, 4, BLACK);
    DrawText(TextFormat("vx: %.2f", vx), 10, 50, 20, BLACK);
    DrawText(TextFormat("vy: %.2f", vy), 10, 70, 20, BLACK);

    // Placeholder for drawing the player (e.g., DrawCircle or DrawTexture)
}