#pragma once
#include <raylib.h>

// Window settings
static constexpr int FRAMERATE = 0;
static constexpr int INITIAL_WINDOW = 400; // px
static constexpr int BACKGROUND_TILES = 4;

static constexpr Vector2 PIPE_HEAD_DIMS = {0.1f, 0.05f};

// Game physics
static constexpr float G_INITIAL_SPEED = 0.25f;
static constexpr float G_CONSTANT_ACCELERATION = 0.05f;
static constexpr float G_PAUSE_DECELLERATION = -G_CONSTANT_ACCELERATION * 25.f;

// Player settings
static constexpr float P_SIZE = 0.025f; // px

static constexpr float P_AX = 2.5f;      // px/s^2
static constexpr float P_VX_MAX = 0.75f; // px/s

static constexpr float P_VJUMP = -0.75f;
static constexpr float P_GRAVITY = 1.75f;
static constexpr float P_VY_MAX = 1.f;
