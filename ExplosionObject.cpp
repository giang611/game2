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
	SDL_Rect* currentclip = &frame_clip_[frame];
	SDL_Rect render_quad = { rect.x,rect.y,frame_width__,frame_height__ };
	if (currentclip != NULL)
	{
		render_quad.w = currentclip->w;
		render_quad.h = currentclip->h;

	}
	SDL_RenderCopy(des, object, currentclip, &render_quad);

}

bool ExplosionObject::loadImg(string path, SDL_Renderer* screen)
{
	bool ret = baseObject::loadImg(path, screen);
	if (ret==true)
	{
		frame_width__ = rect.w / NUM_FRAME_EXP;
		frame_height__ = rect.h;

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
