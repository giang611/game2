#pragma once
#include"commonfunc.h"
#include"baseObject.h"

#define NUM_FRAME_EXP 8
class ExplosionObject :public baseObject
{
public:
	ExplosionObject();
	~ExplosionObject();

public:
	void set_clip();
	void set_clip2();
	void set_clip3();
	void set_frame(const int& frame_) {

		frame = frame_;
	}
	 bool loadImg(string path, SDL_Renderer* screen,int stt);
	 bool loadImg2(string path, SDL_Renderer* screen,int stt);
	 bool loadImg3(string path, SDL_Renderer* screen, int stt);
	void show(SDL_Renderer* screen);
	int get_frame_width() const { return frame_width__; }
	int get_frame_height() const { return frame_height__; }


private:
	int frame_width__;
	int frame_height__;
	unsigned int frame;
	SDL_Rect frame_clip_[12];
};