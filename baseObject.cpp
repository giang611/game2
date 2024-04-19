#include"baseObject.h"

baseObject::baseObject() {
	tt = 1;
	object1.resize(10);
	rect1.resize(10);
	for (int i = 0; i < object1.size(); i++)
	{
		object1[i] = NULL;
	}
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	
}

baseObject::~baseObject() {
	
}
bool baseObject::loadImg(string path,SDL_Renderer* screen,int status) {
	SDL_Texture* newtext = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	tt = status;
	if (surface != NULL) {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		newtext = SDL_CreateTextureFromSurface(screen, surface);
		if (newtext != NULL) {
			rect1[tt].w = surface->w;
			rect1[tt].h = surface->h;
		}
		
		SDL_FreeSurface(surface);

	}
	
	object1[tt] = newtext;
	return object1[tt] != NULL;
	
}
bool baseObject::loadImg2(string path, SDL_Renderer* screen) {
	SDL_Texture* newtext = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	
	if (surface != NULL) {
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
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
	
	object = object1[tt];
	rect.w = rect1[tt].w;
	rect.h = rect1[tt].h;
	SDL_Rect renderquad = { rect.x,rect.y,rect.w,rect.h };

	SDL_RenderCopy(des, object, clip, &renderquad);
}
void baseObject::Render2(SDL_Renderer* des, const SDL_Rect* clip) {
	
	SDL_Rect renderquad = { rect.x,rect.y,rect.w,rect.h };

	SDL_RenderCopy(des, object, clip, &renderquad);
} 
void baseObject::Render3(SDL_Renderer* des, const SDL_Rect* clip) {
	if (pos_list.size() != 0)
	{
		int back = pos_list.back();

		rect.w = back;
		SDL_Rect renderquad = { rect.x,rect.y,rect.w,rect.h };

		SDL_RenderCopy(des, object, clip, &renderquad);
	}
	else
	{
		SDL_Rect renderquad = { rect.x,rect.y,rect.w,rect.h };

		SDL_RenderCopy(des, object, clip, &renderquad);
	}
}

void baseObject::Free() {
	if (object != NULL) {
		SDL_DestroyTexture(object1[tt]);
		object1[tt] = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}