#pragma once
#include"baseObject.h"
class khien :public baseObject
{
public:
	khien();

	int width_frame;
	int height_frame;
	int frame;
	float x_pos;
	float y_pos;
	float map_x_;
	float map_y_;
	int status;
	int heart_tt;
	
	
	SDL_Rect frame_clip[8];
	bool LoadImg(string path, SDL_Renderer* screen,int stt);
	bool LoadImg2(string path, SDL_Renderer* screen,int stt);
	bool LoadImg3(string path, SDL_Renderer* screen, int stt);
	void set_clip();
	void set_clip2();
	void set_clip3();
	void show(SDL_Renderer* des, Map map);
	void show2(SDL_Renderer* des, Map map);
	void show3(SDL_Renderer* des, Map map, const SDL_Rect* clip = NULL);
		void show4(SDL_Renderer* des, Map map, const SDL_Rect* clip = NULL);
	bool CheckToMapX(Map map_data);
	SDL_Rect getRectframe();
	void setmapXY(const int& mp_x, const int& mp_y)
	{
		map_x_ = mp_x;
		map_y_ = mp_y;
	}
	void xuli(Map map);
	
	
};