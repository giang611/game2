#pragma once
#include<Windows.h>
#include<SDL_image.h>
#include<string>
#include<SDL.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<iostream>
#include<vector>

using namespace std;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

//Screen
const int fps = 40;
const int Screen_WIDTH = 1280;
const int Screen_HEIGHT = 640;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define TILE_SIZE 64
#define MAX_MAP_X 350
#define MAX_MAP_Y 10
#define STATE_MONNEY 4

typedef struct input{
	int left;
	int right;
	int down;
	int up;
	int jump;

};

typedef struct Map {
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	
	string file_name;
	

 };


namespace SDLCommonfunc
{
	bool CheckCollision(const SDL_Rect object1, const SDL_Rect object2);
	bool checkmouse(const int& x, const int& y, const SDL_Rect& rect);

	
}
