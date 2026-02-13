#pragma once
#include <raylib.h>

// Window settings
static constexpr int FRAMERATE = 2000;

static constexpr int INITIAL_WINDOW_WIDTH = 400;
static constexpr int INITIAL_WINDOW_HEIGHT = 400;

static constexpr int BACKGROUND_TILES = 4;

static constexpr Vector2 PIPE_HEAD_DIMS = {40.f, 20.f};

// Game physics
static constexpr float G_INITIAL_SPEED = 100.f;
static constexpr float G_CONSTANT_ACCELERATION = 20.0f;
static constexpr float G_PAUSE_DECELLERATION = -G_CONSTANT_ACCELERATION * 25.f;

// Player settings
static constexpr int P_SIZE = 10; // px

static constexpr float P_AX = 500.f;     // px/s^2
static constexpr float P_VX_MAX = 300.f; // px/s

static constexpr float P_V_JUMP = -200.f;
static constexpr float P_GRAVITY = 500.f;
static constexpr float P_VY_MAX = 400.f;
