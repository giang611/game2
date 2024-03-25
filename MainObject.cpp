#include"MainObject.h"

mainObject::mainObject() {
	frame = 0;
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	width_frame = 0;
	height_frame = 0;
	status = -1;
	input_type.left = 0;
	input_type.right = 0;
	input_type.down = 0;
	input_type.up = 0;
	map_x = 0;
	map_y = 0;
}
void mainObject::doPlayer(Map& map_data) {
	if (come_back_time == 0) {
		x_val = 0;
		y_val += 0.8;
		if (y_val >= 10) {
			y_val = 10;
		}
		if (input_type.left == 1) {
			x_val -= player_speed;
		}
		else if (input_type.right == 1) {
			x_val += player_speed;
		}
		else if (input_type.jump == 1) {
			if (on_ground == true) {
				y_val = -23;
				on_ground = false;
			}
			input_type.jump = 0;

		}
		checktoMap(map_data);
		tinhMap(map_data);
	}
	if (come_back_time > 0) {
		come_back_time--;
		if (come_back_time == 0) {
			if (x_pos > 256) {
				x_pos -= 256;


			}
			else { x_pos = 0; }
			y_pos = 0;
			x_val = 0;
			y_val = 0;


		}
	}
}
mainObject::~mainObject() {

	}
SDL_Rect mainObject::getRectframe()
{
	SDL_Rect rectt;
	rectt.x = rect.x;
	rectt.y = rect.y;
	rectt.w = width_frame;
	rectt.h = height_frame;
	return rectt;
}
bool mainObject::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = baseObject::loadImg(path, screen);
	if (ret == true) {
		width_frame = rect.w / 8;
		height_frame = rect.h;
	}
	return ret;
}
void mainObject::set_clip() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 8; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}

}
void mainObject::show(SDL_Renderer* des) {
	
	UpdateImagePlayer(des);
	if (input_type.left == 1 || input_type.right == 1) {
		frame++;
	}
	else 
	{
		frame = 0;
	}
	if (frame >= 8) {
		frame = 0;
	}

	rect.x = x_pos - map_x;
	rect.y = y_pos - map_y;
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad= { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, object, current_clip, &renderQuad);
}
void mainObject::xulihd(SDL_Event event, SDL_Renderer* screen) {

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT: {
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			UpdateImagePlayer(screen);
			
		}
					   break;



		case SDLK_LEFT: {
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			UpdateImagePlayer(screen);
		}
					  break;
		
		}

	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT: {
			status = WALK_RIGHT;
			input_type.right = 0;
		}
					   break;



		case SDLK_LEFT: {
			status = WALK_LEFT;
			input_type.left = 0;
		}
					  break;

		}
	}
    

	 if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			BulletObject* a = new BulletObject();
			a->set_bullet_type(a->SPHERE_BULLET);
			a->LoadImgBullet(screen);
			if (status == WALK_LEFT) 
			{
				a->set_bullet_dir(a->DIR_LEFT);
				a->setRect(this->rect.x , this->rect.y + 0.3 * height_frame);
			}
			else 
			{
				a->set_bullet_dir(a->DIR_RIGHT);
				a->setRect(this->rect.x + width_frame - 20, this->rect.y + 0.3 * height_frame);
			}
			
			a->set_x_val(20);
			a->set_is_move(true);
			
			bullet_list.push_back(a);
			
		}
		else if (event.button.button == SDL_BUTTON_LEFT) {
			input_type.jump = 1;
		}
	}
		
}

void mainObject::tinhMap(Map& map_data) {
	map_data.start_x = x_pos - (Screen_WIDTH / 2);
	if (map_data.start_x < 0) {
		map_data.start_x = 0;
	}
	else if (map_data.start_x + Screen_WIDTH >= map_data.max_x) {

		map_data.start_x = map_data.max_x - Screen_WIDTH;
	}

	map_data.start_y = y_pos - (Screen_HEIGHT / 2);
	if (map_data.start_y < 0) {
		map_data.start_y = 0;
	}

	else if (map_data.start_y + Screen_HEIGHT >= map_data.max_y) {
		map_data.start_y = map_data.max_y - Screen_HEIGHT;
	}
}


void mainObject::checktoMap(Map& map_data) {
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	
	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE; 
	x2 = (x_pos + x_val + width_frame -1  ) / TILE_SIZE;

	y1 = y_pos / TILE_SIZE;
	y2 = (y_pos + height_min -1) / TILE_SIZE;
	
	if (x1 >= 0 && x2 < MAX_MAP_X && y1>=0 && y2<MAX_MAP_Y) {

		if (x_val > 0) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STATE_MONNEY || val2 == STATE_MONNEY)
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			else 
			{
				if (val1 != 0 || val2 != 0) {

					x_pos = x2 * TILE_SIZE;
					x_pos -= width_frame + 1;
					x_val = 0;



				}
			}

		}

		else if (x_val < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];
			if (val1 == STATE_MONNEY || val2 == STATE_MONNEY)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreaseMoney();
			}
			else 
			{
				if (val1 != 0 || val2 != 0) {
					x_pos = (x1 + 1) * TILE_SIZE;
					x_val = 0;

				}
			}
		}

	}
	
	
	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = x_pos / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val > 0) {
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STATE_MONNEY || val2 == STATE_MONNEY)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			else 
			{
				if (val1 != 0 || val2 != 0) {
					y_pos = y2 * TILE_SIZE;
					y_pos -= height_frame + 1;
					y_val = 0;
					on_ground = true;
				}
			}
		}
			else if (y_val < 0) 
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == STATE_MONNEY || val2 == STATE_MONNEY) 
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreaseMoney();
			}
			else
			{


				if (val1 != 0 && val2 != 0) 
				
				{
					y_pos = (y1 + 1) * TILE_SIZE;
					y_val = 0;
				}
			}

			}
					
		}

	x_pos += x_val;
	y_pos += y_val;
	
	if (x_pos < 0) { x_pos = 0; }
	 else if (x_pos + width_frame >map_data.max_x) {

		x_pos = map_data.max_x- width_frame - 1;
	}
	if (y_pos > map_data.max_y) {
		come_back_time = 60;
	}


}
void mainObject::IncreaseMoney() {
	money_count++;
}
void mainObject::UpdateImagePlayer(SDL_Renderer* des) {
	if (on_ground == true) {
		if (status == WALK_LEFT) {
			LoadImg("img//player_left.png",des);
		}
		else {
			LoadImg("img//player_right.png",des);
		}

	}
	else {
		if (status == WALK_LEFT) {
			LoadImg("img//jum_left.png", des);

		}
		else {
		LoadImg("img//jum_right.png", des);
		}

	}


}

void mainObject::handleBullet(SDL_Renderer* des) {
	for (int i = 0; i < bullet_list.size(); i++) {
		BulletObject* a = bullet_list.at(i);
		if (a != NULL) 
		{
			if (a->get_is_move()) 
			{
				a->xuliMove(Screen_WIDTH, Screen_HEIGHT);
				a->Render(des);
			}
			else
			{
				bullet_list.erase(bullet_list.begin() + i);
				if (a != NULL)
				{
					delete a;
					a = NULL;
				}

			}

		}
		

	}
}
void mainObject::RemoveBullet(const int& idx) 
{
	int size = bullet_list.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bullet_list.at(idx);
		bullet_list.erase(bullet_list.begin()+idx);

	}

}