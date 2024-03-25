#include"BossObject.h"
BossObject::BossObject() {
	frame = 0;
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	width_frame = 0;
	height_frame = 0;
	think_time = 0;
	map_x = 0;
	map_y = 0;
	hp = 10;
}
BossObject::~BossObject() {

}
bool BossObject::loadImg(string path, SDL_Renderer* screen)
{
	bool ret = baseObject::loadImg(path, screen);

	if(ret == true)
	{
		width_frame = rect.w / 32;
		height_frame = rect.h;
	}
	return ret;
}
void BossObject::set_clips()
{
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 32; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void BossObject::Show(SDL_Renderer* screen)
{
	if (think_time == 0)
	{
		rect.x = x_pos - map_x;
		rect.y = y_pos - map_y;
		frame++;
		if(frame>=32)
		{
			frame = 0;
		}
		SDL_Rect* currentclip = &frame_clip[frame];
		SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
		if (currentclip != NULL)
		{
			renderQuad.w = currentclip->w;
			renderQuad.h = currentclip->h;
		}
		SDL_RenderCopy(screen, object, currentclip, &renderQuad);
	}
}






void BossObject::InitPlayer()
{
	x_val = 0;
	y_val = 0;
	if (x_pos > 256) {
		x_pos -= 256;
	}
	else x_pos = 0;
	y_pos = 0;
	think_time = 0;
	input_type.left = 1;
}
void BossObject::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

	y1 = y_pos / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{

		if (x_val > 0) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != 0 && val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY)) {

				x_val = 0;



			}
		}



		else if (x_val < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if ((val1 != 0 && val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY)) {

				x_val = 0;

			}

		}


	}

	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos+ y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val > 0) {
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if ((val1 != 0 && val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY)) {

				y_val = 0;
				on_ground = true;
			}

		}
		else if (y_val < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];



			if ((val1 != 0 && val1 != STATE_MONNEY) || (val2 != 0 && val2 != STATE_MONNEY))

			{
				y_val= 0;
			}


		}


	}

	x_pos += x_val;
	y_pos += y_val;

	if (x_pos < 0) { x_pos = 0; }
	else if (x_pos + width_frame > map_data.max_x) {

		x_pos = map_data.max_x - width_frame - 1;
	}
	if (y_pos > map_data.max_y) {
		think_time = 60;
	}


}

void BossObject::InitBullet(SDL_Renderer* screen)
{
	BulletObject* p_bullet = new BulletObject();
	bool ret = p_bullet->loadImg("img//boss bullet.png",screen);
	if (ret)
	{
		p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
		p_bullet->set_is_move(true);
		p_bullet->setRect(rect.x - 50, rect.y + height_frame - 30);
		p_bullet->set_x_val(15);
		bullet_list.push_back(p_bullet);
	}

}

void BossObject::MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit) {
	if (frame == 18)
	{
		InitBullet(des);
	}
	for (int i = 0; i < bullet_list.size(); i++)
	{
		BulletObject* p_bullet = bullet_list.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->xuliMove(x_limit, y_limit);
				p_bullet->Render(des);
			}
			else 
			{
				p_bullet->Free();
				bullet_list.erase(bullet_list.begin() + i);
				
				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}

}
void BossObject::RemoveBullet(const int& idx) {
	int size = bullet_list.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list.at(idx);
		bullet_list.erase(bullet_list.begin() + idx);

	}
}
SDL_Rect BossObject::getRectframe()
{
	SDL_Rect rectt;
	rectt.x = rect.x;
	rectt.y = rect.y;
	rectt.w = width_frame;
	rectt.h = height_frame;
	return rectt;
}
void BossObject::DoPlayer(Map& g_map)
{
	if (think_time == 0)
	{
		x_val = 0;
		y_val += GRAVITY_SPEED;

		if (y_val >= MAX_FALL_SPEED)
		{
			y_val = MAX_FALL_SPEED;
		}
		if (input_type.left == 1)
		{
			x_val -= PLAYER_SPEED;
		}
		else if (input_type.right == 1)
		{
			x_val += PLAYER_SPEED;
		}
		if (input_type.jump == 1)
		{
			if (on_ground == 1)
			{
				y_val = -PLAYER_HIGHT_VAL;
			}
			input_type.jump = 0;
		}
		CheckToMap(g_map);
	}

	if (think_time > 0)
	{
		think_time--;
		if (think_time == 0)
		{
			InitPlayer();
		}
	}



}
