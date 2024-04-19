#pragma once
#include"commonfunc.h"
#include"baseObject.h"
#include"BulletObject.h"
#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3
class ThreatsObject :public baseObject {
public:
	ThreatsObject();
	~ThreatsObject();
	
	enum Typemove {
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
		FLY = 2,
		

	};
	void set_x_val_(const float& xVal) 
	{
		x_val_ = xVal;
	}
	void set_y_val_(const float& yVal)
	{
		y_val_ = yVal;
	}
	void set_x_pos_(const float& x_pos)
	{
		x_pos_ = x_pos;
	}
	void set_y_pos_(const float& y_pos)
	{
		y_pos_ = y_pos;
	}
	float get_x_pos_() {
		 return x_pos_;
	}
	 float get_y_pos_() {
		 return y_pos_;
	 }
	 void setmapXY(const int& mp_x,const int& mp_y) 
	 {
		 map_x_ = mp_x;
		 map_y_ = mp_y;
	 }
	 int get_width_frame_() {
		 return width_frame_;
	 }
	 int get_height_frame_() {
		 return height_frame_;
	 }
	 void set_type_move(const int& typemove) {
		 type_move_ = typemove;
	}
	 void setAnimation( const int& pos_a, const int& pos_b) {
		 animation_a_ = pos_a;
		 animation_b_ = pos_b;
	 }
	 void set_input_left(const int& ipleft) {
		 input_type_.left = ipleft;
	 }
	 void impTypeMove(SDL_Renderer* screen);
	 bool LoadImg3(string path, SDL_Renderer* screen, int status);
	 void setClip();
	 void setClip2();
	 bool LoadImg(string path, SDL_Renderer* screen,int status);
	 bool LoadImg2(string path, SDL_Renderer* screen, int status);
	 void show(SDL_Renderer* des);
	 void show3(SDL_Renderer* des);
	 void show4(SDL_Renderer* des);
	 void show2(SDL_Renderer* des);
	 void doPlayer(Map& gMap);
	 void doPlayer2(Map& gmap);
	 void checktoMap(Map& gMap);
	 
	 void set_bullet_list(vector<BulletObject*>& bl_list)
	 {
		 bullet_list_ = bl_list;

	 }
	 vector<BulletObject*> get_bullet_list()
	 {
		 return bullet_list_;

	 }
	 void InitBullet(BulletObject* bullet, SDL_Renderer* screen);
	 void InitBullet2(BulletObject* p_bullet, SDL_Renderer* screen);
    void InitBullet3(BulletObject* p_bullet, SDL_Renderer* screen);
	 void InitBullet4(BulletObject* p_bullet, SDL_Renderer* screen);
	 void InitBullet5(BulletObject* p_bullet, SDL_Renderer* screen);
	 void InitBullet6(BulletObject* p_bullet, SDL_Renderer* screen);
	 void InitBullet7(BulletObject* p_bullet, SDL_Renderer* screen);
	 void InitBullet8(BulletObject* p_bullet, SDL_Renderer* screen);
	 void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit, Map& mapp);
	 void MakeBullet2(SDL_Renderer* screen, const int& x_limit, const int& y_limit, Map& mapp,Mix_Chunk* a[2]);
	 void RemoveBullet(const int& idx);
	 SDL_Rect getRectframe();
	 int type_move_;
	 input input_type_;
private :
	int map_x_;
	int map_y_;
	float x_pos_;
	float y_pos_;
	float x_val_;
	float y_val_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;
	
	int animation_a_;
	int animation_b_;
	
	vector<BulletObject*> bullet_list_;

};

