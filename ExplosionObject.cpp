#include"ExplosionObject.h"

ExplosionObject::ExplosionObject()
{
	frame_height__ = 0 ;
		frame_width__ = 0;
		frame = 0;

}
ExplosionObject::~ExplosionObject() {

}
void ExplosionObject::show(SDL_Renderer* des) {
	object = object1[tt];
	SDL_Rect* currentclip = &frame_clip_[frame];
	SDL_Rect render_quad = { rect.x,rect.y,frame_width__,frame_height__ };
	if (currentclip != NULL)
	{
		render_quad.w = currentclip->w;
		render_quad.h = currentclip->h;

	}
	SDL_RenderCopy(des, object, currentclip, &render_quad);

}

bool ExplosionObject::loadImg(string path, SDL_Renderer* screen,int stt)
{
	tt = stt;
	bool ret = baseObject::loadImg(path, screen,tt);
	if (ret==true)
	{
		frame_width__ = rect1[tt].w / NUM_FRAME_EXP;
		frame_height__ = rect1[tt].h;

	}
	return ret;
}
bool ExplosionObject::loadImg2(string path, SDL_Renderer* screen,int stt)
{
	tt = stt;
	bool ret = baseObject::loadImg(path, screen,tt);
	if (ret == true)
	{
		frame_width__ = rect1[tt].w / 12;
		frame_height__ = rect1[tt].h;

	}
	return ret;
}
bool ExplosionObject::loadImg3(string path, SDL_Renderer* screen, int stt)
{
	tt = stt;
	bool ret = baseObject::loadImg(path, screen, tt);
	if (ret == true)
	{
		frame_width__ = rect1[tt].w / 5;
		frame_height__ = rect1[tt].h;

	}
	return ret;
}
void ExplosionObject::set_clip() {
	if (frame_width__ > 0 && frame_height__ > 0) {
		for (int i = 0; i < NUM_FRAME_EXP; i++) {
			frame_clip_[i].x = i * frame_width__;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = frame_width__;
			frame_clip_[i].h = frame_height__;
		}
	}
}
void ExplosionObject::set_clip2() {
	if (frame_width__ > 0 && frame_height__ > 0) {
		for (int i = 0; i < 12; i++) {
			frame_clip_[i].x = i * frame_width__;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = frame_width__;
			frame_clip_[i].h = frame_height__;
		}
	}
}
void ExplosionObject::set_clip3() {
	if (frame_width__ > 0 && frame_height__ > 0) {
		for (int i = 0; i < 5; i++) {
			frame_clip_[i].x = i * frame_width__;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = frame_width__;
			frame_clip_[i].h = frame_height__;
		}
	}
}
