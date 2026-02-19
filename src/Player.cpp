#include "Player.hpp"
#include "Constants.hpp"
#include <raylib.h>
#include <raymath.h>

// Add this member to your Player class (in Player.hpp):
// float prevScreenHeight = 0.0f;

Player::Player()
    : x(200.f), y(200.f),
      vx(0.f), vy(0.f),
      prevScreenHeight(0.0f)
{
    // size will be set on first update (safe even if draw happens before)
}

Player::~Player() {}

void Player::jump()
{
    vy = P_VJUMP;
}

void Player::move(int dir)
{
    if (dir == 0) // left
        vx -= (P_AX + G_CONSTANT_ACCELERATION) * DT;
    else if (dir == 1) // right
        vx += P_AX * DT;
}

void Player::update(float dt, float gameSpeed)
{
    GameSpeed = gameSpeed;
    // === NEW: Handle resize + initial setup (positions now scale correctly) ===
    float currentHeight = GetScreenHeight();

    if (IsWindowResized() || prevScreenHeight == 0.0f)
    {
        if (prevScreenHeight != 0.0f)
        {
            // Scale both x and y by the height ratio so the player stays
            // in the exact same relative position on screen after resize.
            // This matches how you already scale movement (vx/vy * height).
            float ratio = currentHeight / prevScreenHeight;
            x *= ratio;
            y *= ratio;
        }
        prevScreenHeight = currentHeight;
    }

    // Always keep size in sync with current height (better than only-on-resize)
    size = P_SIZE * currentHeight;

    // === Original physics (unchanged) ===
    vx = Clamp(vx, -gameSpeed - P_VX_MAX, P_VX_MAX);
    vy += P_GRAVITY * dt;
    vy = Clamp(vy, -P_VY_MAX, P_VY_MAX);

    DT = dt;

    // Use currentHeight for movement (consistent with the new scaling logic)
    x += vx * dt * currentHeight;
    y += vy * dt * currentHeight;
}

void Player::draw()
{
    DrawRectangleRounded({x - size * .5f, y - size * 2.f, size, size * 2.f},
                         size * 0.5, 4, BLACK);
    DrawText(TextFormat("x: %.2f", x), 10, 50, 20, BLACK);
    DrawText(TextFormat("y: %.2f", y), 10, 70, 20, BLACK);
}