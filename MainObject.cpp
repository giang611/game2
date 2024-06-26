#include"MainObject.h"
 

mainObject::mainObject(SDL_Renderer* des) {
	frame = 0;
	x_val = 0;
	y_val = 0;
	x_pos =0;
	y_pos = 0;
	width_frame =0;
	height_frame = 0;
	status = WALK_RIGHT;
	input_type.left = 0;
	input_type.right = 0;
	input_type.down = 0;
	input_type.up = 0;
	map_x = 0;
	map_y = 0;
	player_speed = 8;
	tt = 1;
	hp=5;
	tia3 = false;
	
}

void mainObject::doPlayer(Map& map_data,Mix_Chunk* a[5]) {
	
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
		 if (input_type.jump == 1) {
			if (on_ground == true) {
				y_val = -23;
				on_ground = false;
			}
			input_type.jump = 0;

		}
		checktoMap(map_data,a);
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
bool mainObject::LoadImg(string path, SDL_Renderer* screen,int stt) {
	tt = stt;
	bool ret = baseObject::loadImg(path, screen,tt);
	if (ret == true) {
		
		width_frame = rect1[tt].w / 8;
		height_frame = rect1[tt].h;
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
	object = object1[tt];
	//rect.x = rect1[tt].x;
	//rect.y = rect1[tt].y;
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
void mainObject::xulihd(SDL_Event event, SDL_Renderer* des,Mix_Chunk* bullet_sound[2]) {

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT: {
			status = WALK_RIGHT;
			input_type.right = 1;
			input_type.left = 0;
			UpdateImagePlayer(des);
			
		}
					   break;



		case SDLK_LEFT: {
			status = WALK_LEFT;
			input_type.left = 1;
			input_type.right = 0;
			UpdateImagePlayer(des);
		}
					  break;
		
		}

	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT: {
			status = WALK_RIGHT;
			input_type.right = 0;
			UpdateImagePlayer(des);
		}
					   break;



		case SDLK_LEFT: {
			status = WALK_LEFT;
			input_type.left = 0;
			UpdateImagePlayer(des);
		}
					  break;

		}
	}
    

	 if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			
			Mix_PlayChannel(-1, bullet_sound[0], 0);
			BulletObject* a = new BulletObject();
			a->set_bullet_type(a->SPHERE_BULLET);
			
			a->LoadImgBullet(des,tt);
			BulletObject* b = new BulletObject();
			b->set_bullet_type(a->LASER_BULLET);

			b->LoadImgBullet(des, tt);
			BulletObject* c = new BulletObject();
			c->set_bullet_type(a->LASER_BULLET);

			c->LoadImgBullet(des, tt);
			BulletObject* d = new BulletObject();
			d->set_bullet_type(a->LASER_BULLET);

			d->LoadImgBullet(des, tt);
			BulletObject* e = new BulletObject();
			e->set_bullet_type(a->SPHERE_BULLET);

			e->LoadImgBullet(des, tt);
			BulletObject* f = new BulletObject();
			f->set_bullet_type(a->SPHERE_BULLET);

			f->LoadImgBullet(des, tt);
			if (tia3 == false) {
				if (status == WALK_LEFT && input_type.left == 0 && input_type.right == 0)
				{
					a->set_bullet_dir(a->DIR_LEFT);
					a->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					a->set_x_val(-30);
					a->set_x_pos(this->rect.x + map_x);
					a->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
				}
				else if (input_type.left == 1)
				{

					a->set_bullet_dir(a->DIR_LEFT);
					a->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					a->set_x_val(-30);
					a->set_x_pos(this->rect.x + map_x);
					a->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					//a->setMapXY(map_x, map_y);

				}
				else
				{

					a->set_bullet_dir(a->DIR_RIGHT);
					a->setRect(x_pos - map_x + width_frame - 20, y_pos - map_y + 0.3 * height_frame);
					a->set_x_val(30);
					
					a->set_x_pos(this->rect.x + width_frame - 20 + map_x);
					a->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					//a->setMapXY(map_x, map_y);

				}


				a->set_is_move(true);

				bullet_list.push_back(a);
			}
			else
			{
				if (status == WALK_LEFT && input_type.left == 0 && input_type.right == 0)
				{
					d->set_bullet_dir(a->DIR_UP_LEFT);
					d->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					d->set_x_val(-30);
					
					d->set_x_pos(this->rect.x + map_x);
					d->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					d->set_is_move(true);

					bullet_list.push_back(d);
					b->set_bullet_dir(b->DIR_UP);
					b->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
				
					b->set_y_val(-30);
					b->set_x_val(-8);
					b->set_x_pos(this->rect.x + map_x);
					b->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					b->set_is_move(true);

					bullet_list.push_back(b);
					c->set_bullet_dir(c->DIR_UP_LEFT);
					c->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					c->set_x_val(-45);
					c->set_y_val(-30);
					c->set_x_pos(this->rect.x + map_x);
					c->set_y_pos(this->rect.y + 0.3 * height_frame + map_y-30);
					c->set_is_move(true);

					bullet_list.push_back(c);
					
					
					
				}
				else if (input_type.left == 1)
				{

					d->set_bullet_dir(a->DIR_UP_LEFT);
					d->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					d->set_x_val(-30);
					d->set_y_val(-30);
					d->set_x_pos(this->rect.x + map_x);
					d->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					d->set_is_move(true);

					bullet_list.push_back(d);
					b->set_bullet_dir(b->DIR_UP);
					b->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);

					b->set_y_val(-30);
					b->set_x_val(-8);
					b->set_x_pos(this->rect.x + map_x);
					b->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					b->set_is_move(true);

					bullet_list.push_back(b);
					c->set_bullet_dir(c->DIR_UP_LEFT);
					c->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					c->set_x_val(-45);
					c->set_y_val(-30);
					c->set_x_pos(this->rect.x + map_x);
					c->set_y_pos(this->rect.y + 0.3 * height_frame + map_y - 30);
					c->set_is_move(true);

					bullet_list.push_back(c);

				}
				else
				{

					d->set_bullet_dir(a->DIR_UP_LEFT);
					d->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					d->set_x_val(30);
					d->set_y_val(5);
					d->set_x_pos(this->rect.x + map_x);
					d->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					d->set_is_move(true);

					bullet_list.push_back(d);
					b->set_bullet_dir(b->DIR_UP);
					b->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);

					b->set_y_val(-30);
					b->set_x_val(15);
					b->set_x_pos(this->rect.x + map_x+30);
					b->set_y_pos(this->rect.y + 0.3 * height_frame + map_y);
					b->set_is_move(true);

					bullet_list.push_back(b);
					c->set_bullet_dir(c->DIR_UP_LEFT);
					c->setRect(x_pos - map_x, y_pos - map_y + 0.3 * height_frame);
					c->set_x_val(45);
					c->set_y_val(-20);
					c->set_x_pos(this->rect.x + map_x);
					c->set_y_pos(this->rect.y + 0.3 * height_frame + map_y );
					c->set_is_move(true);

					bullet_list.push_back(c);

				}


				
			}
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


void mainObject::checktoMap(Map& map_data,Mix_Chunk* a[5]) {
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;

	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;

	y1 = y_pos / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {

		if (x_val > 0) {
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STATE_MONNEY || val2 == STATE_MONNEY)
			{
				Mix_PlayChannel(-1, a[0], 0);
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
				Mix_PlayChannel(-1, a[0], 0);
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
				Mix_PlayChannel(-1, a[0], 0);
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
				Mix_PlayChannel(-1, a[0], 0);
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
	else if (x_pos + width_frame > map_data.max_x) {

		x_pos = map_data.max_x - width_frame - 1;
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
		if (input_type.left==1) {
			tt = 2;
			object = object1[tt];
			//loadImg("img//player_left.png", des);
		}
		else if(input_type.right==1) {
			tt = 1;
			object = object1[tt];
			//LoadImg("img//player_right.png",des);
		}
		else if (status == WALK_RIGHT) { tt = 1; object = object1[tt]; }
		else if (status == WALK_LEFT) {
			tt = 2;	object = object1[tt];
		}
	}
	else {
		if (input_type.left==1) {
			tt = 4;
			object = object1[tt];
			
		}
		else if(input_type.right==1){
			tt = 3;
			object = object1[tt];
		}
		else if (status == WALK_RIGHT) {
			tt = 3; object = object1[tt];
		}
		else if (status == WALK_LEFT) {
			tt = 4; object = object1[tt];
		}
	}


}

void mainObject::handleBullet(SDL_Renderer* des , Map& mapp) {
	for (int i = 0; i < bullet_list.size(); i++) {
		BulletObject* a = bullet_list.at(i);
		
		
		if (a != NULL) 
		{
			a->setMapXY(map_x, map_y);
			if (a->vc == true) { bullet_list.erase(bullet_list.begin() + i);
			if (a != NULL)
			{
				delete a;
				a = NULL;
			}continue; }
			
			if (a->get_is_move()) 
			{
				a->xuliMove(Screen_WIDTH, Screen_HEIGHT, mapp);
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