#include "Obstacles.hpp"
#include "Constants.hpp"
#include <raylib.h>
#include <vector>
#include <random>

Obstacles::Obstacles()
{
    // Load the pipe textures
    pipeHead = LoadTexture("assets/pipe_head.png");
    SetTextureFilter(pipeHead, TEXTURE_FILTER_BILINEAR);
    pipeShaft = LoadTexture("assets/pipe_shaft.png");
    SetTextureFilter(pipeShaft, TEXTURE_FILTER_BILINEAR);

    // Set up the stencil
    positionRects(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
}

// Unload textures
Obstacles::~Obstacles()
{
    UnloadTexture(pipeHead);
    UnloadTexture(pipeShaft);
}

// Reset obstacles and reposition the stencil rectangles
void Obstacles::positionRects(float right, float bottom)
{
    // Useful when resizing obstacles.clear();

    startX = right;
    // Randomize the stencil's centerY
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.3f * right, 0.6f * bottom);
    centerY = dist(gen);
    gapX = right * 0.5f;
    gapY = bottom * 0.125f;

    // Set x positions and widths (same for all rects)
    for (int i = 0; i < Pipes::COUNT; i++)
    {
        stencil.rects[i].x = startX;               // All start at the same position
        stencil.rects[i].width = PIPE_HEAD_DIMS.x; // All images have the same width
    }

    // Set y positions
    stencil.rects[Pipes::TOP_HEAD].y = centerY - gapY - PIPE_HEAD_DIMS.y;
    stencil.rects[Pipes::BOTTOM_HEAD].y = centerY + gapY;
    stencil.rects[Pipes::TOP_SHAFT].y = 0.f;
    stencil.rects[Pipes::BOTTOM_SHAFT].y = centerY + gapY + PIPE_HEAD_DIMS.y - 1.0f;

    // Set heights
    stencil.rects[Pipes::TOP_HEAD].height = PIPE_HEAD_DIMS.y;
    stencil.rects[Pipes::BOTTOM_HEAD].height = PIPE_HEAD_DIMS.y;
    stencil.rects[Pipes::TOP_SHAFT].height = centerY - gapY - PIPE_HEAD_DIMS.y + 1.0f;
    stencil.rects[Pipes::BOTTOM_SHAFT].height = bottom - (centerY + gapY + PIPE_HEAD_DIMS.y - 1.0f);

    // After repositioning, add the stencil as the first obstacle
    obstacles.push_back(stencil);
}

void Obstacles::update(float displacement)
{
    // Reposition stencil if window resized
    if (IsWindowResized())
    {
        positionRects(static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));
    }

    // Move the pipes by displacement
    for (auto &obstacle : obstacles) // for every obstacle group in the vector of obstacles
    {
        for (int i = 0; i < Pipes::COUNT; i++) // For every rect in each obstacle group
        {
            obstacle.rects[i].x -= displacement;
        }
    }

    // If the most recently added pipe has moved past the startX - gapX threshold, add a new pipe
    if (obstacles.back().rects[Pipes::TOP_HEAD].x < startX - gapX)
    {
        positionRects(static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));

        // Copy the stencil onto the obstacles vector
        obstacles.push_back(stencil);
    }

    // Remove off-screen pipes
    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(), [](const Pipes &pipe)
                       { return pipe.rects[Pipes::TOP_HEAD].x + pipe.rects[Pipes::TOP_HEAD].width < 0.f; }),
        obstacles.end());
}

void Obstacles::draw()
{
    /*// Draw stencil (only for debugging)
    for (int i = 0; i < Pipes::COUNT; i++)
    {
        Texture2D &tex = (i < Pipes::TOP_SHAFT) ? pipeHead : pipeShaft;
        Rectangle src = (i == Pipes::TOP_HEAD) ? Rectangle{0.f, (float)pipeHead.height, (float)pipeHead.width, -(float)pipeHead.height}
                                               : Rectangle{0.f, 0.f, (float)tex.width, (float)tex.height};

        DrawTexturePro(tex, src, stencil.rects[i], {0.f, 0.f}, 0.f, BLACK);
    }*/

    // For each pipe texture used, define if it needs to be flipped
    Texture2D textures[Pipes::COUNT] = {pipeHead, pipeHead, pipeShaft, pipeShaft};
    bool flipTop[Pipes::COUNT] = {true, false, false, false}; // Only top pipe flips

    for (auto &pipeGroup : obstacles)
    {
        for (int i = 0; i < Pipes::COUNT; i++)
        {
            DrawTexturePro(textures[i],
                           {0.f, 0.f, (float)textures[i].width, flipTop[i] ? -(float)textures[i].height : (float)textures[i].height},
                           pipeGroup.rects[i],
                           {0.f, 0.f}, 0.f, WHITE);
        }
    }
}