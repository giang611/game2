#include<vector>

#include"BulletObject.h"
#include"MainObject.h"
BulletObject::BulletObject() {
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
	bullet_type = SPHERE_BULLET;
}
BulletObject::~BulletObject() {
	

}
void BulletObject::xuliMove(const int& x_border, const int& y_border) {
	if (bullet_dir == DIR_RIGHT)
	{
		rect.x += x_val_;
		if (rect.x > x_border)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_LEFT)
	{
		rect.x -= x_val_;
		if (rect.x < 0)
		{
			is_move = false;
		}

	}
	else if (bullet_dir == DIR_UP)
	{
		rect.y -= y_val_;
		if (rect.y < 0)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP_LEFT)
	{
		rect.x -= x_val_;
		if (rect.x < 0)
		{
			is_move = false;
		}
		rect.y -= y_val_;
		if (rect.y < 0)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP_RIGHT)
	{
		rect.x += x_val_;
		if (rect.x > x_border)
		{
			is_move = false;
		}
		rect.y -= y_val_;
		if (rect.y < 0)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_DOWN_LEFT)
	{
		rect.x -= x_val_;
		if (rect.x < 0)
		{
			is_move = false;
		}
		rect.y += y_val_;
		if (rect.y > y_border)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_UP_RIGHT)
	{
		rect.x += x_val_;
		if (rect.x > x_border)
		{
			is_move = false;
		}
		rect.y += y_val_;
		if (rect.y > y_border)
		{
			is_move = false;
		}
	}
}
void BulletObject::xuliMove2(const int& x_border, const int& y_border) {
	 if (bullet_dir == DIR_LEFT)
	{
		rect.x -= x_val_;
		if (rect.x < x_border)
		{
			is_move = false;
		}

	}
	
}

void BulletObject::LoadImgBullet(SDL_Renderer* des){
	if (bullet_type == SPHERE_BULLET) 
	{
		loadImg("img//spherebullet.png", des);
	}
	else
	{
		loadImg("img//laserbullet.png", des);
	}


}
