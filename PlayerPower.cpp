#include"PlayerPower..h"

PlayerPower::PlayerPower()
{
	number = 0;
}
PlayerPower::~PlayerPower()
{

}
void PlayerPower::AddPos(const int& xp)
{
	pos_list.push_back(xp);
}
void PlayerPower::Init(SDL_Renderer * screen,int stt) {
	tt = stt;
	loadImg("img//player_pw.png", screen,tt);
	number = 3;
	if (pos_list.size() > 0)
	{
		pos_list.clear();
	}
	AddPos(20);
	AddPos(60);
	AddPos(100);
	
}

void PlayerPower::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos_list.size(); i++)
	{
		rect.x = pos_list.at(i);
		rect.y = 0;
		Render(screen);
	}
}
void PlayerPower::Decrease() {
	number--;
	pos_list.pop_back();
}
void PlayerPower::InitCrease()
{
	number++;
	int last_pos = pos_list.back();
	last_pos += 40;
	pos_list.push_back(last_pos);
}

PlayerMoney::PlayerMoney() {
x_pos = 0;
y_pos = 0;
}
PlayerMoney::~PlayerMoney() {

}
void PlayerMoney::Init(SDL_Renderer* screen) {
	bool ret = loadImg("img//money_img.png", screen,tt);
}
void PlayerMoney::Show(SDL_Renderer* screen)
{
	rect.x = x_pos;
	rect.y = y_pos;
	Render(screen);
}