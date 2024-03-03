#include"ThreatsObject.h"
#include "MainObject.h"

ThreatsObject::ThreatsObject() {
	width_frame_ = 0;
	height_frame_ = 0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	on_ground_ = 0;
	come_back_time_ = 0;
	frame_ = 0;
	input_type_.right = 0;
	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left = 0;
	
	type_move_ = STATIC_THREAT;
	map_x_ = 0;
	map_y_ = 0;

}
ThreatsObject::~ThreatsObject()
{
	
}
bool ThreatsObject::LoadImg(string path, SDL_Renderer* screen) 
{
	bool ret = baseObject::loadImg(path, screen);
	if (ret == true) {
		width_frame_ = rect.w / THREAT_FRAME_NUM;
		height_frame_ = rect.h;
	}
	return ret;
}

void ThreatsObject::setClip() {
	if(width_frame_>0 && height_frame_>0)
	{
		for (int i = 0; i < THREAT_FRAME_NUM; i++) 
		{
			
				frame_clip_[i].x = i * width_frame_;
				frame_clip_[i].y = 0;
				frame_clip_[i].w = width_frame_;
				frame_clip_[i].h = height_frame_;
			}
		}
	}


void ThreatsObject::show(SDL_Renderer* des)
{
	if (come_back_time_ == 0)
	{
		rect.x = x_pos_ - map_x_;
		rect.y = y_pos_ - map_y_;
		frame_++;


		if (frame_ >= 8)
		{
			frame_ = 0;
		}
		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect RendQuad{ rect.x,rect.y,width_frame_,height_frame_ };
		SDL_RenderCopy(des, object, currentClip, &RendQuad);
	}
}
	


void ThreatsObject::doPlayer(Map& gmap) 
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY_SPEED;

		if (y_val_ >=THREAT_MAX_FALL_SPEED) 
		{
			y_val_ = THREAT_MAX_FALL_SPEED;
		}
		if (input_type_.left == 1) 
		{
			x_val_ -= THREAT_SPEED;
		}
		else if (input_type_.right == 1)
		{
			x_val_ += THREAT_SPEED;
		}
		checktoMap(gmap);
	}
	
	else if (come_back_time_ > 0) 
	{
		come_back_time_--;
		if(come_back_time_==0)
		{
			x_val_ = 0;
			y_val_ = 0;
			if (x_pos_ > 256)
			{
				x_pos_ -= 256;
				animation_a_ -= 256;
				animation_b_ -= 256;
			}
			else 
			{
				x_pos_ = 0;
			}
			y_pos_ = 0;
			
			input_type_.left = 1;
		}
	}

}
void ThreatsObject::checktoMap(Map& map_data) 
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = y_pos_ / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) 
	{

		if (x_val_ > 0) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != 0 && val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY)) {

				x_val_ = 0;
				


			}
		}



		else if (x_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if ((val1 != 0 && val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY)) {
				
				x_val_ = 0;

			}

		}


	}

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = x_pos_ / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != 0&& val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY)) {

				y_val_ = 0;
				on_ground_ = true;
			}

		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];



			if ((val1 != 0 && val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY))

			{
				y_val_ = 0;
			}


		}
	

	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) { x_pos_ = 0; }
	else if (x_pos_ + width_frame_ > map_data.max_x) {

		x_pos_ = map_data.max_x - width_frame_ - 1;
	}
	if (y_pos_ > map_data.max_y) {
		come_back_time_ = 60;
	}


}
void ThreatsObject::impTypeMove(SDL_Renderer* screen)
{
	if (type_move_ == STATIC_THREAT) 
	{
		;
	}
	else
	{
		if (on_ground_ == true)
		{
			if (x_pos_ >= animation_b_)
			{
				input_type_.left = 1;
				input_type_.right = 0;
				LoadImg("img//threat_left.png", screen);

			}
			else if (x_pos_ <= animation_a_)
			{
				input_type_.right = 1;
				input_type_.left = 0;
				
				LoadImg("img//threat_right.png", screen);

			}
		}
		else
		{
			if (input_type_.left == 1) 
			{


				LoadImg("img//threat_left.png", screen);
			}
		}
	}

}
void ThreatsObject::InitBullet(BulletObject* p_bullet,SDL_Renderer* screen)
	{
	if (p_bullet != NULL) 
	{
		p_bullet->set_bullet_type(p_bullet->LASER_BULLET);
		p_bullet->LoadImgBullet(screen);
		p_bullet->set_is_move(true);
		p_bullet->set_bullet_dir(p_bullet->DIR_LEFT);
		p_bullet->setRect(x_pos_ + 20, y_pos_ + 10);
		p_bullet->set_x_val(15);
		bullet_list_.push_back(p_bullet);

	}
	} 
void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < bullet_list_.size(); i++)
	{
		BulletObject* a = bullet_list_.at(i);
		if (a != NULL)
		{
			if (a->get_is_move())
			{
				int distan_bullet = rect.x+width_frame_ - a->getRect().x;
				if (distan_bullet < 300&& distan_bullet>0)
				{
					a->xuliMove(x_limit, y_limit);
					a->Render(screen);
				}
				else a->set_is_move(false);
				
			}
			else
			{
				a->set_is_move(true);
				a->setRect(rect.x + 20, rect.y + 10);

			}
		}
	}
}
void ThreatsObject::RemoveBullet(const int& idx) {
	int size = bullet_list_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list_.at(idx);
		bullet_list_.erase(bullet_list_.begin() + idx);

	}
}
SDL_Rect ThreatsObject::getRectframe()
{
	SDL_Rect rectt;
	rectt.x = rect.x;
	rectt.y = rect.y;
	rectt.w = width_frame_;
	rectt.h = height_frame_;
	return rectt;
}