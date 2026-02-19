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

    // Initial stencil + first pipe
    positionRects(INITIAL_WINDOW, INITIAL_WINDOW);
    obstacles.push_back(stencil); // <-- now explicit (was hidden inside positionRects)

    prevScreenWidth = INITIAL_WINDOW;
    prevScreenHeight = INITIAL_WINDOW;
}

Obstacles::~Obstacles()
{
    UnloadTexture(pipeHead);
    UnloadTexture(pipeShaft);
}

// Now ONLY configures the stencil template + spawn parameters.
// Does NOT push anything to obstacles (cleaner + fixes old double-spawn bug).
void Obstacles::positionRects(float right, float bottom)
{
    startX = right;

    // Randomize the next pipe's vertical position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.3f * right, 0.6f * bottom);
    centerY = dist(gen);

    gapX = right * 0.5f;
    gapY = bottom * 0.125f;

    // x / width (same for all parts)
    for (int i = 0; i < Pipes::COUNT; i++)
    {
        stencil.rects[i].x = startX;
        stencil.rects[i].width = dims.x;
    }

    // y positions
    stencil.rects[Pipes::TOP_HEAD].y = centerY - gapY - dims.y;
    stencil.rects[Pipes::BOTTOM_HEAD].y = centerY + gapY;
    stencil.rects[Pipes::TOP_SHAFT].y = 0.f;
    stencil.rects[Pipes::BOTTOM_SHAFT].y = centerY + gapY + dims.y - 1.0f;

    // heights
    stencil.rects[Pipes::TOP_HEAD].height = dims.y;
    stencil.rects[Pipes::BOTTOM_HEAD].height = dims.y;
    stencil.rects[Pipes::TOP_SHAFT].height = centerY - gapY - dims.y + 1.0f;
    stencil.rects[Pipes::BOTTOM_SHAFT].height = bottom - (centerY + gapY + dims.y - 1.0f);
}

void Obstacles::update(float displacement)
{
    float currW = static_cast<float>(GetScreenWidth());
    float currH = static_cast<float>(GetScreenHeight());

    // Always keep pipe width/height scaled to current screen height (same as Player)
    dims = {PIPE_HEAD_DIMS.x * currH, PIPE_HEAD_DIMS.y * currH};

    bool resized = IsWindowResized() || prevScreenHeight == 0.0f;

    if (resized)
    {
        if (prevScreenHeight != 0.0f) // not the very first frame
        {
            float ratioW = currW / prevScreenWidth;
            float ratioH = currH / prevScreenHeight;

            // Scale EVERY existing pipe so it stays in the exact same relative spot
            for (auto &obstacle : obstacles)
            {
                for (int i = 0; i < Pipes::COUNT; i++)
                {
                    obstacle.rects[i].x *= ratioW;
                    obstacle.rects[i].width *= ratioW;
                    obstacle.rects[i].y *= ratioH;
                    obstacle.rects[i].height *= ratioH;
                }
            }

            // Keep spawn logic consistent
            startX *= ratioW;
        }

        // Update stencil + spawn parameters for the new resolution (new random centerY)
        positionRects(currW, currH);
    }

    prevScreenWidth = currW;
    prevScreenHeight = currH;

    // Move pipes
    for (auto &obstacle : obstacles)
    {
        for (int i = 0; i < Pipes::COUNT; i++)
        {
            obstacle.rects[i].x -= displacement;
        }
    }

    // Spawn new pipe when the last one has scrolled far enough
    if (!obstacles.empty() && obstacles.back().rects[Pipes::TOP_HEAD].x < startX - gapX)
    {
        if (!resized) // avoid re-randomising on the resize frame
        {
            positionRects(currW, currH);
        }
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
    Texture2D textures[Pipes::COUNT] = {pipeHead, pipeHead, pipeShaft, pipeShaft};
    bool flip[Pipes::COUNT] = {true, false, false, false};

    for (auto &pipeGroup : obstacles)
    {
        for (int i = 0; i < Pipes::COUNT; i++)
        {
            DrawTexturePro(textures[i],
                           {0.f, 0.f,
                            (float)textures[i].width,
                            flip[i] ? -(float)textures[i].height : (float)textures[i].height},
                           pipeGroup.rects[i],
                           {0.f, 0.f}, 0.f, WHITE);
        }
    }
}