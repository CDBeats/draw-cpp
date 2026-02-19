#pragma once
#include "Constants.hpp"
#include <raylib.h>

class Player
{
public:
    Player();
    ~Player();

    void update(float dt, float gameSpeed);
    void jump();
    void move(int dir);
    void draw();

private:
    float GameSpeed;
    float size = P_SIZE * INITIAL_WINDOW;
    float prevScreenHeight;
    float DT;
    float x;
    float y;
    float vx;
    float vy;
};