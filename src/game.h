#pragma once
#include "map.h"
#include "state.h"
#include<SDL2/SDL.h>

#define D_UP 0
#define D_LEFT 1
#define D_DOWN 2
#define D_RIGHT 3

void GameKeyDown(Uint32 key);

void StartGame();

void SnakeStep();
