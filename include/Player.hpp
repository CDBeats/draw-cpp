#pragma once
#include <raylib.h>

class Player
{
public:
    Player();
    ~Player();

    void update(float dt);
    void jump();
    void moveLeft();
    void moveRight();
    void draw();

private:
    float DT;
    float x;
    float y;
    float vx;
    float vy;
};