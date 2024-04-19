#pragma once
#include"commonfunc.h"
class baseObject {
public:
	baseObject();
	~baseObject();
	int tt;
	void setRect(const int& x, const int& y) {
		rect.x = x;
		rect.y = y;
	}
	
	SDL_Rect getRect() const { return rect; }
	SDL_Texture* getObject(int status) const { return object1[status]; }
	virtual bool loadImg(std::string path, SDL_Renderer* screen,int status);
	virtual bool loadImg2(std::string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Render2(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void Render3(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	
	void Free();
	vector<int> pos_list;
	vector< SDL_Texture*> object1;
	SDL_Texture* object;
	vector<SDL_Rect> rect1;
	SDL_Rect rect;
};

