#include "Game.hpp"

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(INITIAL_WINDOW, INITIAL_WINDOW, "Draw!");
    SetWindowMinSize(INITIAL_WINDOW, INITIAL_WINDOW);
    SetTargetFPS(FRAMERATE);
    SetExitKey(KEY_NULL);

    Game game;
    game.run();

    CloseWindow();
    return 0;
}
