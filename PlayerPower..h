#pragma once

#include"commonfunc.h"
#include"baseObject.h"

class PlayerPower : public baseObject
{

public:
	PlayerPower();
	~PlayerPower();

	void SetNum(const int& num) { number = num; }
	void AddPos(const int& xPos);
	void Show(SDL_Renderer* screen);
	void Init(SDL_Renderer* screen);

	void InitCrease();
	void Decrease();

private:
	int number;
	vector<int> pos_list;


};

class PlayerMoney :public baseObject {

public:
	PlayerMoney();
	~PlayerMoney();

	void Init(SDL_Renderer* screen);
	void Show(SDL_Renderer* screen);
	void SetPos(const int& x, const int& y) {
		x_pos = x;
		y_pos = y;
	}
private:
	int x_pos;
	int y_pos;


};