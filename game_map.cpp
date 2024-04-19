#include"game_map.h"
void Gamemap::Loadmap(string name) {
	FILE* f=NULL;
	fopen_s(&f, name.c_str(), "rb");
	if (f == NULL) return;

	gamemap.max_x = 0;
	gamemap.max_y = 0;

	for (int i = 0; i < MAX_MAP_Y; i++) 
	{
		for (int j = 0; j < MAX_MAP_X; j++) 
		{
			fscanf_s(f, "%d", &gamemap.tile[i][j]);
			int val = gamemap.tile[i][j];
			if (val > 0) 
			{
				if (j > gamemap.max_x) {
					gamemap.max_x = j;
				}
				if (i > gamemap.max_y) {
					gamemap.max_y = i;
				}
			}
		}
	}

	gamemap.max_x = (gamemap.max_x + 1) * TILE_SIZE;
	gamemap.max_y = (gamemap.max_y + 1) * TILE_SIZE;

	gamemap.start_x = 0;
	gamemap.start_y = 0;
	gamemap.file_name = name;
	fclose(f);
}

	void Gamemap::LoadTile(SDL_Renderer* screen) {
		char file[30];
		FILE* f = NULL;
		for (int i = 0; i < 20; i++) {
			sprintf_s(file, "map/%d.png", i);

			fopen_s(&f, file, "rb");
			if (f == NULL) continue;
			fclose(f);
			tilemat[i].loadImg(file, screen,tilemat[i].tt);
			
		}
	}
	void Gamemap::DrawMap(SDL_Renderer* screen) {
		int map_x_ = (gamemap.start_x / TILE_SIZE);

		int map_y_ = gamemap.start_y / TILE_SIZE;
		int x1 = 0;
		int x2 = 0;
		int y1 = 0;
		int y2 = 0;
		x1 = (gamemap.start_x % TILE_SIZE) * - 1;
		x2 = x1 + Screen_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

		y1 = (gamemap.start_y % TILE_SIZE) * -1;
		y2 = y2 + Screen_HEIGHT + (y2 == 0 ? 0 : TILE_SIZE);
	
		for (int i = y1; i < y2; i+=TILE_SIZE) {
			map_x_ = gamemap.start_x / TILE_SIZE;
			for (int j = x1; j < x2; j += TILE_SIZE) {
				int val = gamemap.tile[map_y_][map_x_];
				if (val > 0) {
					
				//	tilemat[val].object = tilemat[val].object1[tilemat[val].tt];
				//	tilemat[val].rect.w = tilemat[val].rect1[tilemat[val].tt].w;
				//	tilemat[val].rect.h = tilemat[val].rect1[tilemat[val].tt].h;
					tilemat[val].setRect(j, i);
					tilemat[val].Render(screen);
				}
				map_x_++;
			}
			map_y_++;
	   }
	}




