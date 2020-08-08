#include "map.h"
#include<stdio.h>
unsigned char map[MapH][MapW];

void FillMapArea(Uint32 x1,Uint32 y1,Uint32 x2 , Uint32 y2,Uint8 value) {
	if(x1>=MapW) x1 = MapW-1;
	if(x2>=MapW) x2 = MapW-1;
	if(y1>=MapH) y1 = MapH-1;
	if(y2>=MapH) y2 = MapH-1;

	for(int i= y1;i<=y2;i++) for (int e = x1;e<=x2;e++) map[i][e] = value;
}

void InitMap () {
	int i,e;
	for(i = 0;i<MapH;i++) {
		for(e = 0; e<MapW;e++) {
			if(e<MenuW) map[i][e] = T_MENU;
			
			if(
			(i==0&&e==MenuW)||
			(i==0&&e==MapW-1)||
			(i==MapH-1 && e==MenuW)||
			(i==MapH-1 && e==MapW-1)
			) map[i][e] = T_FRAME_CORNER;

			if(e>MenuW && e<MapW-1 && (i==0||i==MapH-1)) map[i][e] = T_FRAME_H;
			if(i>0 && i<MapH-1 &&(e==MenuW||e==MapW-1)) map[i][e] = T_FRAME_V;

			if(e>MenuW && e<MapW-1 && i>0 && i<MapH-1) map[i][e] = T_TAB_BACK;
		}
	}
	FillMapArea(1,1,6,2,T_BLACK);
	FillMapArea(1,4,6,5,T_BLACK);
}
