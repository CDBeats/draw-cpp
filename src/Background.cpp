#include "Background.hpp"
#include <raylib.h>
#include <algorithm>

Background::Background()
{
    tile = {INITIAL_WINDOW_WIDTH / (NUM_RECTS * 0.5f), INITIAL_WINDOW_HEIGHT * 0.5f};
    // Initialize rectangles to fill the screen in a 2x2 grid
    for (int i = 0; i < NUM_RECTS; i++)
    {
        rects[i] = {(i * tile.x), (i % 2 == 0 ? 0 : tile.y), tile.x, tile.y};
    }
}

Background::~Background() {}

void Background::update(float displacement)
{
    // Update tile dimensions if window is resized
    if (IsWindowResized())
    {
        tile = {GetScreenWidth() / (NUM_RECTS * 0.5f), GetScreenHeight() * 0.5f};
    }

    // Move the leftmost rectangle
    rects[0].x -= displacement;

    // Update widths, heights, and positions dynamically
    for (int i = 0; i < NUM_RECTS; i++)
    {
        rects[i].width = tile.x;
        rects[i].height = tile.y;

        if (i > 0)
        {
            rects[i].x = rects[i - 1].x + rects[i - 1].width;
            rects[i].y = rects[i - 1].y > 0 ? 0 : tile.y; // Base new y on the previous rectangle's y (stagger)
        }
        else
        {
            rects[i].y = rects[1].y > 0 ? 0 : tile.y; // Base first rectangle's y on the second rectangle's y to maintain stagger
        }
    }

    // Wrap the leftmost rectangle if it goes offscreen
    if (rects[0].x + rects[0].width < 0)
    {
        rects[0].x = rects[NUM_RECTS - 1].x + rects[NUM_RECTS - 1].width;
        rects[0].y = 0;
        std::rotate(rects, rects + 1, rects + NUM_RECTS);
    }
}

// Draw method
void Background::draw()
{
    for (int i = 0; i < NUM_RECTS; i++)
    {
        DrawRectangleRec(rects[i], LIGHTGRAY);
    }
}