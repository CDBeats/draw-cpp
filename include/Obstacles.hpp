#pragma once
#include "raylib.h"
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
        // Array of rectangles for the pipe parts
        Rectangle rects[COUNT];
    };

    // Vector of all obstacles, each containing its own set of rects for the pipe parts
    std::vector<Pipes> obstacles;

private:
    void positionRects(float right, float bottom);

    float startX;
    float gapX;
    float centerY;
    float gapY;

    Texture2D pipeHead;
    Texture2D pipeShaft;
    Pipes stencil;
    Rectangle initialDrawRect;
};
