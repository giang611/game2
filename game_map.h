#pragma once
#include"commonfunc.h"
#include"baseObject.h"

class Tilemat : public baseObject {
public: Tilemat() { ; }
	  ~Tilemat() { ; }


};

class Gamemap {
public: Gamemap() { ; }
	  ~Gamemap() { ; }
	   void Loadmap(string ten);
	   void LoadTile(SDL_Renderer* screen);
	   void DrawMap(SDL_Renderer* screen);
	   Map gamemap;
	   void setMap(Map& map_data) {
		   gamemap = map_data;


	   }

       private: 
		
	   Tilemat tilemat[20];

};