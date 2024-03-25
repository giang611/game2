#pragma once
#include"commonfunc.h"
#include"baseObject.h"
class BulletObject : public baseObject {
public: 
	BulletObject();
	~BulletObject();

	enum BulletDir {
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
		DIR_UP =  22,
		DIR_UP_LEFT = 23,
		DIR_UP_RIGHT = 24,
		DIR_DOWN_LEFT= 25,
		DIR_DOWN_RIGHT = 26,
	};
	enum BulletType {
		SPHERE_BULLET= 50,
		LASER_BULLET= 51,

	};


	
	void set_x_val(const int& xVal) {
		x_val_ = xVal;
	}
	void set_y_val(const int& yVal) {
		y_val_ = yVal;
	}
	void set_is_move(const bool& isMove) {
		is_move = isMove;
	}
	int get_x_val() {
		return x_val_;
	}
	int get_y_val() {
		return y_val_;
	}
	bool get_is_move() {
		return is_move;
	}
	void xuliMove(const int& x_border, const int& y_border);
	void xuliMove2(const int& x_border, const int& y_border);
	void set_bullet_dir(const unsigned int& bulletDir) {
		bullet_dir = bulletDir;
	}
	unsigned int get_buller_dir() {
		return bullet_dir;
	}
	void set_bullet_type(const unsigned int& bulletType) {
		bullet_type = bulletType;
	}
	unsigned int get_buller_type() {
		return bullet_type;
	}
	void LoadImgBullet(SDL_Renderer* screen);
private:
	int x_val_;
	int y_val_;
	bool is_move;
	unsigned int bullet_dir;
	unsigned int bullet_type;
	

	


};
