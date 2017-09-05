#pragma once

#include <SDL2/SDL.h>

#define MaxSpeed 16
#define MaxGrowSpeed 16

#define S_Game 0
#define S_GameOver 1
#define S_Menu 2

struct GameState {
	Uint32 score;
	Uint8 state,speed,GrowSpeed;
};

extern struct GameState state;


void SetSpeed(int newspeed);
void SetGrowSpeed(int nGSpeed);

void SetScore(int newScore);
char* GetScoreS();
