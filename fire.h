#pragma once
#include"baseObject.h"
class fire:public baseObject
{
public:
	fire();

	int width_frame;
	int height_frame;
	int frame;
	float x_pos;
	float y_pos;
	float map_x_;
float map_y_;
	float x_val_, y_val_;
	vector<fire> fire_list;
	SDL_Rect frame_clip[8];
	bool LoadImg(string path, SDL_Renderer* screen,int stt);

	void set_clip();

	void show(SDL_Renderer* des,Map map);

	bool CheckToMapX(Map map_data);
	SDL_Rect getRectframe();
	void setmapXY(const int& mp_x, const int& mp_y)
	{
		map_x_ = mp_x;
		map_y_ = mp_y;
	}
	void xuli(Map map);
	void set_x_val_(const float& xVal)
	{
		x_val_ = xVal;
	}
	void set_y_val_(const float& yVal)
	{
		y_val_ = yVal;
	}
	void set_x_pos_(const float& x_pos_)
	{
		x_pos = x_pos_;
	}
	void set_y_pos_(const float& y_pos_)
	{
		y_pos = y_pos_;
	}
	float get_x_pos_() {
		return x_pos;
	}
	float get_y_pos_() {
		return y_pos;
	}
};