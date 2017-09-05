#include "game.h"
#include "stdio.h"

#define MaxScore 999999
char _initializedScore = 0;
char ScoreS[7];

void SetScore(int newScore) {
	if(!_initializedScore) {
		for(char*c=ScoreS;c-ScoreS<=7;c++) *c = 0;
		_initializedScore = 1;
	}

	state.score = newScore;
	if(state.score>MaxScore) state.score = MaxScore;
	sprintf(ScoreS,"%d\n",state.score);
}

char* GetScoreS() {
	return ScoreS;
}

struct Snake {
	int x,y,dir,size,pdir;
}snake;

int Timer = 0;

int tab[Tabrows*Tabcolls];

void GameKeyDown(Uint32 key) {
	switch(key) {
		case SDL_SCANCODE_UP:
		if(snake.pdir!=D_DOWN||snake.size==1)snake.dir = D_UP;
		break;
		case SDL_SCANCODE_DOWN:
		if(snake.pdir!=D_UP||snake.size==1)snake.dir = D_DOWN;
		break;

		case SDL_SCANCODE_LEFT:
		if(snake.pdir!=D_RIGHT||snake.size==1)snake.dir = D_LEFT;
		break;

		case SDL_SCANCODE_RIGHT:
		if(snake.pdir!=D_LEFT||snake.size==1)snake.dir = D_RIGHT;
		break;
		case SDL_SCANCODE_SPACE:
		if(state.state == S_GameOver) StartGame();
		break;
	}
}

void PutFood() {
	if(snake.size >= Tabcolls*Tabrows-1) {
		return;
	}
	int *i=tab + (rand()%(Tabcolls*Tabrows));
	for(i ;1; i++) {
		if(i-tab >= Tabcolls*Tabrows) i = tab;
		if((*i)<1) {
			*i = -1;
			break;
		}
	}
}

void StartGame(struct GameState *st) {
	state.state = S_Game;
	Timer = 0;
	SetScore(0);
	snake.x = Tabcolls/2;
	snake.y = Tabrows/2;
	snake.dir = D_LEFT;
	snake.pdir = snake.dir;
	snake.size = 1;
	for(int *i = tab;i-tab<Tabcolls*Tabrows;i++) *i=0;
	
	PutFood();
}

void SnakeGrown() {
	for(int *i=tab;i-tab<Tabcolls*Tabrows;i++) if(*i>0) *i += state.GrowSpeed;
}

void UpdateTab() {
	char win = 1;
	for(int *t = tab;t-tab<Tabcolls*Tabrows;t++) {
		int i = (t-tab)/Tabcolls;
		int e = (t-tab)%Tabcolls;
		
		int m_e = e +MenuW+1;
		int m_i = i+1;
		if(*t>0) {
			(*t)--;
			map[m_i][m_e] = T_SNAKE;
		}else if(*t==0) {
			win = 0;
			map[m_i][m_e] = T_TAB_BACK;
		}else if (*t==-1) {
			win = 0;
			map[m_i][m_e] = T_FOOD;
		}
	}
	if(win) state.state = S_GameOver;
}

void SnakeStep() {
	if(++Timer < MaxSpeed-state.speed) return;
	Timer = 0;
	
	switch(snake.dir) {
		case D_LEFT:
		snake.x--;
		break;
		case D_UP:
		snake.y--;
		break;
		case D_DOWN:
		snake.y++;
		break;
		case D_RIGHT:
		snake.x++;
		break;
	}
	if (snake.x < 0 || snake.y < 0 || snake.x >= Tabcolls || snake.y >= Tabrows) {
		state.state = S_GameOver;
		return;
	}
	
	if(tab[snake.y*Tabcolls+snake.x]>0) {
		state.state = S_GameOver;
		return;
	}else if(tab[snake.y*Tabcolls+snake.x]==-1) {
		snake.size += state.GrowSpeed;
		SetScore(state.score+state.GrowSpeed);
		SnakeGrown();
		tab[snake.y*Tabcolls+snake.x] = snake.size;
		UpdateTab();
		PutFood();
	}else if(tab[snake.y*Tabcolls+snake.x]==0) {
		tab[snake.y*Tabcolls+snake.x] = snake.size;
		UpdateTab();
	}
	
	snake.pdir = snake.dir;
}
