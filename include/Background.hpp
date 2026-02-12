#pragma once
#include <raylib.h>
#include "Constants.hpp"

class Background
{
public:
    Background();
    ~Background();

    void update(float displacement);
    void draw();

private:
    constexpr static int NUM_RECTS = BACKGROUND_TILES;
    Rectangle rects[NUM_RECTS];

    // Initial tile dimensions
    Vector2 tile;
};