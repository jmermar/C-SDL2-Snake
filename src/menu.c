#include "menu.h"
#include<stdio.h>

#define OptionsL 2

char sSpeed[3];
char sGSpeed[3];

Uint8 menuIndex = 0;

int renderX = 0;
int renderY = 0;
int StartRenderY = 0;
int currentRenderY=0;

void SetSpeed(int newSpeed)
{
	state.speed = newSpeed;
	state.speed %= MaxSpeed;
	sprintf(sSpeed, "%d", state.speed);
}

void SetGrowSpeed(int nGSPeed) {
	state.GrowSpeed = nGSPeed;
	if(state.GrowSpeed < 1) state.GrowSpeed = MaxGrowSpeed;
	if(state.GrowSpeed > MaxGrowSpeed) state.GrowSpeed = 1;
	sprintf(sGSpeed, "%d", state.GrowSpeed);
}

void SetIndex(int newindex) {
	map[StartRenderY + 1 + menuIndex * 2][renderX] = T_BLACK;
	menuIndex = newindex%OptionsL;
	map[StartRenderY + 1 + menuIndex * 2][renderX] = T_ARROW;
}

/**
 *-Speed Option functions
 */
void OSpeedDraw() {
	Print("speed", renderX + 1, currentRenderY);
	Print(sSpeed, renderX + 1, currentRenderY + 1);
}

void OSpeedKeyDown(Uint32 key) {
	if(key == SDL_SCANCODE_RIGHT) SetSpeed(++state.speed);
	if(key == SDL_SCANCODE_LEFT) SetSpeed(--state.speed);
}

/**
 *-Grow Option functions
 */
void OGrowDraw() {
	Print("grow", renderX + 1 , currentRenderY);
	Print(sGSpeed, renderX + 1, currentRenderY+1);
}
void OGrowKeyDown(Uint32 key) {
	if(key==SDL_SCANCODE_RIGHT) SetGrowSpeed(++state.GrowSpeed);
	if(key==SDL_SCANCODE_LEFT) SetGrowSpeed(--state.GrowSpeed);
}


enum options {
	O_Speed = 0,O_WS
};

typedef struct sOption {
	void (*draw)();
	void (*keydown)(Uint32);
} sOption;

sOption options[OptionsL];

Uint32 PreviousState = 0;
Uint8 Cursor = 0;
/**
 *-Basic Menu function
 */
void OpenMenu() {
	if(state.state == S_Menu) return;
	PreviousState = state.state;
	state.state = S_Menu;

	renderX = 1;
	renderY = 13;
	StartRenderY = renderY - OptionsL*2;
	FillMapArea(renderX, StartRenderY, 6, 14, T_BLACK);
	SetIndex(0);

	//Create options
	
	

	sOption ospeed;
	ospeed.draw = OSpeedDraw;
	ospeed.keydown = OSpeedKeyDown;

	options[0] = ospeed;

	sOption ogrowsize;
	ogrowsize.draw = OGrowDraw;
	ogrowsize.keydown = OGrowKeyDown;
	options[1] = ogrowsize;
}

void CloseMenu() {
	FillMapArea(renderX,StartRenderY,6,14,T_MENU);
	state.state = PreviousState;
}

void DrawMenu() {
	Print("Config",renderX,StartRenderY);

	for(int i=0;i<OptionsL;i++) {
		currentRenderY = StartRenderY +1 +i*2;
		if(options[i].draw)options[i].draw();
	}
}

void MenuKeyDown(Uint32 key) {
	if(key==SDL_SCANCODE_DOWN) {
		SetIndex(menuIndex+1);
		return;
	}if(key==SDL_SCANCODE_UP) {
		SetIndex(menuIndex+1);
		return;
	}

	if(options[menuIndex].keydown) options[menuIndex].keydown(key);
}
