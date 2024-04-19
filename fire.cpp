#include"fire.h"
#include<vector>
fire::fire()
{
	 width_frame=0;
	 height_frame=0;
	 frame=0;
	 map_x_ = 0;
	 map_y_ = 0;
	 x_pos = 0;
	 y_pos = 0;
	 x_val_ = 0;
	 y_val_ = 0;
}
void fire::xuli(Map map)
{
	
		x_pos += x_val_;
		y_pos += y_val_;
	
}
bool fire::LoadImg(string path, SDL_Renderer* screen,int stt) {
	tt = stt;
	bool ret = loadImg(path, screen,tt);
	if (ret == true) {
		width_frame = rect1[tt].w / 8;
		height_frame = rect1[tt].h;
	}
	return ret;
}

void fire::set_clip() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 8; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}

}
void fire::show(SDL_Renderer* des,Map map) {
	xuli(map);
	frame++;
		
	if (frame >= 8) {
		frame = 0;
	}

	rect.x = x_pos-map_x_;
	rect.y = y_pos-map_y_;
	SDL_Rect* current_clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, object1[tt], current_clip, &renderQuad);
}
bool fire::CheckToMapX(Map map_data)
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
			
				return true;
			}
		}



	}

	x_pos += x_val_;
	y_pos += y_val_;


	return false;


}
SDL_Rect fire::getRectframe()
{
	SDL_Rect rectt;
	rectt.x = rect.x;
	rectt.y = rect.y;
	rectt.w = width_frame;
	rectt.h = height_frame;
	return rectt;
}