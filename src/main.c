#include "state.h"
#include "map.h"
#include "graphic.h"
#include "game.h"
#include "menu.h"
#define SDL_SCANCODE_ENTER 28
struct GameState state;

#define bool char
#define true 1
#define false 0

Uint32 S_previous = 0;

int main(int argc,char**argv) {
	SetGrowSpeed(1);
	SetSpeed(8);
	SetScore(0);
	
	state.state = S_Game;
	InitMap();
	InitGraphics(MapW*16,MapH*16);
	StartGame(&state);
	state.state = S_GameOver;
	Uint32 Time = 0;
	Uint8 FPS = 30;
	
	bool running = true;
	SDL_Event event;
	while(running) {
		Time = SDL_GetTicks();
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
				running = false;
				case SDL_KEYDOWN:
				
				if(!event.key.repeat) {
					Uint32 scancode = event.key.keysym.scancode;
					if(state.state!=S_Menu)GameKeyDown(scancode);
					if(state.state==S_Menu)MenuKeyDown(scancode);
					if(scancode==SDL_SCANCODE_ESCAPE) {
						if(state.state!=S_Menu) OpenMenu();
						else if(state.state==S_Menu) CloseMenu();
					}
				}
				break;
			}
		}
		Render();
		
		Time = SDL_GetTicks();
		
		if(state.state == S_Game)SnakeStep();	
		
		if(SDL_GetTicks()-Time < 1000/FPS) SDL_Delay(1000/FPS-(SDL_GetTicks()-Time));
	}

	QuitGraphics();	
}
