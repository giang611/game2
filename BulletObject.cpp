#include<vector>

#include"BulletObject.h"

BulletObject::BulletObject() {
	x_val_ = 0;
	y_val_ = 0;
	is_move = false;
	bullet_type = SPHERE_BULLET;
	vc = false;
	x_pos = 0;
	y_pos = 0;
	width_frame = 0;
	height_frame = 0;
	map_x = 0; map_y = 0;
}
BulletObject::~BulletObject() {
	

}

void BulletObject::xuliMove(const int& x_border, const int& y_border,Map& mapp) {
	if (bullet_dir == DIR_RIGHT)
	{
		if (CheckToMapX(mapp)) vc = true;
		else {
			rect.x = x_pos - map_x;
			vc = false;
		}
	
		
		if (rect.x > x_border)
		{
			is_move = false;
		}
	}
	else if (bullet_dir == DIR_LEFT)
	{
		if (CheckToMapX(mapp)) vc = true;
		else {// rect.x += x_val_;
			rect.x = x_pos - map_x;
		vc = false; }
		
		
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
bool BulletObject::CheckToMapX(Map map_data)
{

	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val_) / TILE_SIZE;
	x2 = (x_pos + x_val_ + width_frame - 1) / TILE_SIZE;

	y1 = y_pos / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {

		if (x_val_ > 0) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			
				if (val1 != 0 || val2 != 0) {

					x_pos = x2 * TILE_SIZE;
					x_pos -= width_frame + 1;
					x_val_ = 0;
					is_move = false;
					return true;


				
			}

		}

		else if (x_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == STATE_MONNEY || val2 == STATE_MONNEY)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				
			}
			else
			{
				if (val1 != 0 || val2 != 0) {
					x_pos = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
					is_move = false;
					return true;

				}
			}
		}

	}


	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val_) / TILE_SIZE;
	y2 = (y_pos + y_val_ + height_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			
				if (val1 != 0 || val2 != 0) {
					y_pos = y2 * TILE_SIZE;
					y_pos -= height_frame + 1;
					y_val_ = 0;
					is_move = false;
					return true;
				
				}
			
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			


				if (val1 != 0 && val2 != 0)

				{
					y_pos = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
					is_move = false;
					return true;
				}
			}

		

	}

	x_pos += x_val_;
	y_pos += y_val_;

	
	return false;


}
