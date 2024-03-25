#pragma once
#include"commonfunc.h"
class baseObject {
public:
	baseObject();
	~baseObject();
	void setRect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	
	SDL_Rect getRect() const { return rect; }
	SDL_Texture* getObject() const { return object; }
	virtual bool loadImg(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Free();

	SDL_Texture* object;
	SDL_Rect rect;
};

