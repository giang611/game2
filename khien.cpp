#include"khien.h"
#include<vector>
khien::khien()
{
	width_frame = 0;
	height_frame = 0;
	frame = 0;
	map_x_ = 0;
	map_y_ = 0;
	x_pos = 0;
	y_pos = 0;
	status =0;
	map_x_ = 0;
	map_y_ = 0;
	heart_tt = 0;
	}
bool khien::LoadImg(string path, SDL_Renderer* screen,int stt) {
	tt = stt;
	bool ret = loadImg(path, screen,tt);
	if (ret == true) {
		width_frame = rect1[tt].w / 2;
		height_frame = rect1[tt].h;
	}
	return ret;
}
bool khien::LoadImg3(string path, SDL_Renderer* screen, int stt) {
	tt = stt;
	bool ret = loadImg(path, screen, tt);
	if (ret == true) {
		width_frame = rect1[tt].w;
		height_frame = rect1[tt].h;
	}
	return ret;
}
bool khien::LoadImg2(string path, SDL_Renderer* screen,int stt) {
	tt = stt;
	bool ret = loadImg(path, screen,tt);
	if (ret == true) {
		width_frame = rect1[tt].w;
		height_frame = rect1[tt].h;
	}
	return ret;
}

void khien::set_clip() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 2; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}

}
void khien::set_clip2() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 4; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}

}
void khien::set_clip3() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 4; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}

}
void khien::show(SDL_Renderer* des, Map map) {
	object = object1[tt];
	
	frame++;

	if (frame >= 4) {
		frame = 0;
	}

	
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, object, current_clip, &renderQuad);
}
void khien::show2(SDL_Renderer* des, Map map) {
	object = object1[tt];

	frame++;

	if (frame >= 4) {
		frame = 0;
	}
	rect.x = x_pos - map_x_;
	rect.y = y_pos - map_y_;

	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, object, current_clip, &renderQuad);
}
void khien::show3(SDL_Renderer* des, Map map, const SDL_Rect* clip) {
	object = object1[tt];

	
	rect.x = x_pos - map_x_;
	rect.y = y_pos - map_y_;

	
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, object, clip, &renderQuad);
}
void khien::show4(SDL_Renderer* des, Map map, const SDL_Rect* clip) {
	object = object1[tt];

	frame++;

	if (frame >= 4) {
		frame = 0;
	}
	

	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, object, current_clip, &renderQuad);
}

SDL_Rect khien::getRectframe()
{
	SDL_Rect rectt;
	rectt.x = rect.x;
	rectt.y = rect.y;
	rectt.w = width_frame;
	rectt.h = height_frame;
	return rectt;
}