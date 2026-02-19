#pragma once
#include "raylib.h"
#include "Constants.hpp"
#include <vector>

class Obstacles
{
public:
    Obstacles();
    ~Obstacles();

    void update(float displacement);
    void draw();

    // Enum for pipe parts
    struct Pipes
    {
        enum
        {
            TOP_HEAD = 0,
            BOTTOM_HEAD = 1,
            TOP_SHAFT = 2,
            BOTTOM_SHAFT = 3,
            COUNT = 4
        };
        Rectangle rects[COUNT];
    };

    std::vector<Pipes> obstacles;

private:
    void positionRects(float right, float bottom);

    float startX;
    float gapX;
    float centerY;
    float gapY;
    Vector2 dims = {PIPE_HEAD_DIMS.x * INITIAL_WINDOW, PIPE_HEAD_DIMS.y *INITIAL_WINDOW};
    Texture2D pipeHead;
    Texture2D pipeShaft;
    Pipes stencil;
    Rectangle initialDrawRect;

    // NEW: remember previous resolution so we can scale existing pipes on resize
    float prevScreenWidth = 0.0f;
    float prevScreenHeight = 0.0f;
};