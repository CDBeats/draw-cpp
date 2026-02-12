#pragma once
#include <raylib.h>

// Window settings
static constexpr int FRAMERATE = 2000;

static constexpr int INITIAL_WINDOW_WIDTH = 400;
static constexpr int INITIAL_WINDOW_HEIGHT = 400;

static constexpr int BACKGROUND_TILES = 4;

static constexpr Vector2 PIPE_HEAD_DIMS = {40.f, 20.f};

// Game physics
static constexpr float INITIAL_GAME_SPEED = 100.f;
static constexpr float GAME_CONSTANT_ACCELERATION = 20.0f;
static constexpr float PAUSE_DECELLERATION = -GAME_CONSTANT_ACCELERATION * 25.f;
