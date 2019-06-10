#pragma once

constexpr auto NUM_BULLETS = 3;
constexpr auto NUM_ENEMY_BULLETS_BIG_SHIP = 1;
constexpr auto NUM_ENEMY_BULLETS_SMALL_SHIP = 3;

constexpr auto PLAYER_BULLET_SPEED = 10.0;
constexpr auto ENEMY_BULLET_SPEED = 4.0;

constexpr auto ENEMY_FIRE_DELAY = 200;
constexpr auto BULLET_POS_OFF_SCREEN = -200;

constexpr auto BULLET_RANGE = 300;
constexpr auto BULLET_HEIGHT = 4;
constexpr auto BULLET_WIDTH = 4;
constexpr pointd BULLET_OFF_POSITION = { -100, -100 };