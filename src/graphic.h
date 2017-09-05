#pragma once

#include <SDL2/SDL.h>
#include "map.h"
#define TileW  4

#define FontW 16
#define FontSW 14
#define FontSH 16
#define FontOX ((16-FontSW)/2)
#define FontOY ((16-FontSH)/2)

#define FontStartLetter 33
#define FontStartNumber 16
extern SDL_Texture* tileset;
extern SDL_Texture* font;
extern SDL_Renderer* render;
extern SDL_Window* win;



void FillMapArea(Uint32 x1,Uint32 y1,Uint32 x2 , Uint32 y2,Uint8 value);
void InitGraphics(int w,int h);
void QuitGraphics();
void Render();
void Print(const unsigned char*txt,int x,int y);
