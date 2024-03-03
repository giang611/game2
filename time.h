#pragma once

class Time
{
public : Time();
	   ~Time();


	   void start();
	   void stop();
	   void pause();
	   void unpause();
	   
	   int getTicks();
	  
	   bool is_started();
	   bool is_paused();

private: 
	int start_ticks;
	int pause_ticks;

	bool is_start;
	bool is_pause;

};