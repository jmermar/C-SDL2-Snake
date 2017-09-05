#include"graphic.h"
#include"map.h"
#include"state.h"

void Print(const unsigned char* text,int x,int y);
SDL_Texture* tileset=0;
SDL_Renderer* render=0;
SDL_Window* win=0;
SDL_Texture* font = 0;

void InitGraphics(int w, int h) {
	SDL_Init(SDL_INIT_EVERYTHING);

	win = SDL_CreateWindow("Snake Deluxe",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
		w*2,h*2,SDL_WINDOW_SHOWN);

	render = SDL_CreateRenderer(win,-1,0);
	SDL_RenderSetLogicalSize(render,w,h);

	SDL_Surface* stileset = SDL_LoadBMP("graphic/tiles.bmp");
	tileset = SDL_CreateTextureFromSurface(render,stileset);
	SDL_FreeSurface(stileset);

	SDL_Surface *sfont = SDL_LoadBMP("graphic/font.bmp");
	font = SDL_CreateTextureFromSurface(render,sfont);
	SDL_FreeSurface(sfont);
}
void QuitGraphics(){
	SDL_DestroyTexture(tileset);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
}

void Render(){
	SDL_SetRenderDrawColor(render,0,0,0,0);
	SDL_RenderClear(render);
	SDL_Rect tile = {0,0,16,16};
	SDL_Rect frame = {0,0,16,16};

	for(int i = 0;i<MapH;i++) {
		tile.y = i*16;
		for(int e = 0; e<MapW;e++) {
			tile.x = e*16;

			frame.x = 16*(map[i][e]%TileW);
			frame.y = 16*(map[i][e]/TileW);
			SDL_RenderCopy(render,tileset,&frame,&tile);
		}
	}

	if(state.state==S_Menu) DrawMenu();
	
	Print("score",1,1);
	Print(GetScoreS(),1,2);

	if(state.state==S_GameOver) {
		Print("press",1,4);
		Print("space",1,5);
	}
	

	SDL_RenderPresent(render);
}


void Print(const unsigned char* text,int x,int y) {
	SDL_Rect word = {x*16+FontOX,y*16+FontOY,FontSW,FontSH};
	word.x -= 16;
	SDL_Rect frame = {0,0,FontSW,FontSH};
	for(text;*text!=0;text++) {
		unsigned char tile = 0;
		if(*text>='a'&&*text<='z') tile = *text - 'a' + FontStartLetter; 
		if(*text>='A'&&*text<='Z') tile = *text - 'A' + FontStartLetter;

		if(*text>='0'&&*text<='9') tile = *text - '0' + FontStartNumber;

		word.x +=16;
		frame.x = (tile%FontW)*FontSW;
		frame.y = (tile/FontW)*FontSH;

		SDL_RenderCopy(render,font,&frame,&word);
	}
}
