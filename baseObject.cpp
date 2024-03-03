#include"baseObject.h"

baseObject::baseObject() {
	object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;

}

baseObject::~baseObject() {
	
}
bool baseObject::loadImg(string path,SDL_Renderer* screen) {
	SDL_Texture* newtext = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	
	if (surface != NULL) {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newtext = SDL_CreateTextureFromSurface(screen, surface);
		if (newtext != NULL) {
			rect.w = surface->w;
			rect.h = surface->h;
		}
		SDL_FreeSurface(surface);

	}
	object = newtext;
	return object != NULL;
	
}
void baseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
	SDL_Rect renderquad = { rect.x,rect.y,rect.w,rect.h };
	SDL_RenderCopy(des, object, clip, &renderquad);
}
void baseObject::Free() {
	if (object != NULL) {
		SDL_DestroyTexture(object);
		object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}