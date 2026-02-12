#include "Game.hpp"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "Draw!");
    SetWindowMinSize(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT);
    SetTargetFPS(FRAMERATE);
    SetExitKey(KEY_NULL);

    Game game;
    game.run();

    CloseWindow();
    return 0;
}
