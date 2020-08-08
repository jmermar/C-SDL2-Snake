#pragma once
#include <SDL2/SDL.h>
#define Tabrows 24
#define Tabcolls 24
#define MenuW 8


#define MapW (Tabcolls+2+MenuW)
#define MapH (Tabrows+2)

#define T_BLACK 3
#define T_MENU 5
#define T_FRAME_CORNER 0
#define T_FRAME_H 1
#define T_FRAME_V 2
#define T_TAB_BACK 4
#define T_SNAKE 6
#define T_FOOD 7
#define T_ARROW 8

extern unsigned char map[MapH][MapW];


void InitMap();
