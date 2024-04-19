#pragma once
#include<vector>
#include"commonfunc.h"
#include"baseObject.h"
#include"BulletObject.h"
#include"time.h"
class mainObject :public baseObject {
public:
	mainObject(SDL_Renderer* des);
	void doPlayer(Map& map_data, Mix_Chunk* a[5]);
	~mainObject();
	int width_frame;
	int height_frame;
	enum WALKTYPE {
		WALK_RIGHT = 0,
	    WALK_LEFT = 1,
	};
	bool LoadImg(string path, SDL_Renderer* screen,int status);
	void show(SDL_Renderer* des);
	void xulihd(SDL_Event event, SDL_Renderer* des, Mix_Chunk* bullet_sound[2]);
	void xulihd(SDL_Event event, SDL_Renderer* screen);
	void set_clip();
    void doPlayer(Map& map_data);
	void checktoMap(Map& map_data);
	void UpdateImagePlayer(SDL_Renderer* des);
	void setMapXY(const int map_x_, const int map_y_) {
		map_x = map_x_;
		map_y = map_y_;


	}
	void tinhMap(Map& map_data);
	void checktoMap(Map& map_data, Mix_Chunk* a[2]);
	void set_bullet_list(vector <BulletObject*> list) {
		bullet_list = list;
	}
	vector<BulletObject*> get_bullet_list() { return bullet_list; }
	void handleBullet(SDL_Renderer* des, Map& mapp);
	void IncreaseMoney();
	void RemoveBullet(const int& idx);
	SDL_Rect getRectframe();
	void set_comeback_time(const int& cb_time)
	{
		come_back_time = cb_time;
	} int hp;
	double x_pos;
	double y_pos;
	double player_speed;
	bool on_ground = false;
	int getMoneyCount() const { return money_count; }
	int status;
	int come_back_time;
	bool tia3;
	
private: 
	int money_count = 0;
	double x_val;
	double y_val;
	vector<BulletObject*> bullet_list;
	
	
	
	

	SDL_Rect frame_clip[8];
	input input_type;
	int frame;
	
	
	int map_x;
	int map_y;
	
		

};

