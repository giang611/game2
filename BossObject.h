#pragma once
#include"baseObject.h"
#include"commonfunc.h"
#include"BulletObject.h"


#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10

#define PLAYER_SPEED 2
#define PLAYER_HIGHT_VAL 10;
class BossObject : public baseObject
{
public:
	BossObject();
	~BossObject();
	void set_x_val(int xp) { x_val = xp; }
	void set_y_val(int yp) { y_val = yp; }

	void set_xpos(const int& xps) { x_pos = xps; }
	void set_ypos(const int& yps) { y_pos = yps; }

	int get_x_pos() { return x_pos; }
	int get_y_pos() { return y_pos; }

	void Show(SDL_Renderer* des);
	bool loadImg(string path,SDL_Renderer* screen);
	void set_clips();

	int get_width_frame() const { return width_frame; }
	int get_height_frame() const { return height_frame; }

	void setMapXY(const int mapx, const int mapy) { map_x = mapx; map_y = mapy; }

	void CheckToMap(Map& g_map);

	void CenterEnityOnMap(Map& g_map);
	void DoPlayer(Map& g_map);
	void InitPlayer();
	vector<BulletObject*> get_bullet_list() const { return bullet_list; }
	void set_bullet_list(const vector<BulletObject*>& an_list) {
		bullet_list = an_list;
	}
	void InitBullet(SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit, Map& mapp);
	void RemoveBullet(const int& idx);
	int getHp() { return hp; }
	SDL_Rect getRectframe();
	
private:
	int map_x;
	int map_y;
	int on_ground;
	int think_time;
	input input_type;
	int frame;
	SDL_Rect frame_clip[32];
	int x_pos;
	int y_pos;
	float x_val;
	float y_val;
	int width_frame;
	int height_frame;
	vector<BulletObject*> bullet_list;
	int hp;

};