#include "baseObject.h"
#include"game_map.h"
#include"MainObject.h"
#include"time.h"
#include"ThreatsObject.h"
#include"ExplosionObject.h"
#include"TextObject.h"
#include"PlayerPower..h"
#include"Geometric.h"
#include"BossObject.h"
#include"fire.h"
#include"khien.h"
baseObject back_ground;
baseObject back_ground2;
baseObject back_ground3;
baseObject back_ground4;
baseObject menu;
vector<int> pos_listt;
int dem = 0;
bool win = false,lose=false;
bool dan33 = false;
int dem1[10] = { 0 };
int dem2[10] = { 0 };
TTF_Font* font_time = NULL;
int i = 0;
int j = 1;
double time_khienn;
double time_dann;
bool fire1 = false, fire2 = false, fire11 = false, fire22 = false;
bool fire_tt=false;
bool fire_tt2 = false;
bool stt_boss = false;
int tt_boss = 0;
int thu = 0;
bool tt_hp = false;
bool Initdata() {
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;

    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 == -1))
    
        return false;
        g_sound_bullet[0]=Mix_LoadWAV("bulletat1.wav");
        g_sound_bullet[1]= Mix_LoadWAV("bulletat2.wav");
        g_sound_exp[0] = Mix_LoadWAV("exp1at.wav");
        g_sound_exp[1] = Mix_LoadWAV("exp2at.wav");
        g_sound_exp[2] = Mix_LoadWAV("at2.wav");
        g_sound_exp[3] = Mix_LoadWAV("at3.wav");
        g_sound_exp[4] = Mix_LoadWAV("expth.wav");
        item[0] = Mix_LoadWAV("coin.wav");
        item[1] = Mix_LoadWAV("coin2.wav");
        item[2] = Mix_LoadWAV("nhacnen.wav");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("game cua toi",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Screen_WIDTH,
        Screen_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
        success = false;
    }
    else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) {
            success = false;
        }
        else {
            SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        }
        if (TTF_Init() == -1)
        {
            success = false;
        }
        font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
        if (font_time == NULL)
        {
            success = false;
        }

    }
    return success;;
}

bool showMenu()
{
    Mix_PlayChannel(-1, item[2], -1);
    bool g_menu = menu.loadImg("img//menu.png", g_screen,1);
    menu.Render(g_screen, NULL);
    const int kitem = 2;
    SDL_Rect pos_arr[kitem];
    pos_arr[0].x = 200;
    pos_arr[0].y = 400;
    pos_arr[1].x = 200;
    pos_arr[1].y = 500;
    TextObject text_menu[kitem];
    text_menu[0].SetText("Play Game");
    text_menu[0].SetColor(TextObject::MENU_TEXT);
    text_menu[0].setX(pos_arr[0].x);
    text_menu[0].setY(pos_arr[0].y);
    text_menu[1].SetText("Exit");
    text_menu[1].SetColor(TextObject::MENU_TEXT);
    text_menu[1].setX(pos_arr[1].x);
    text_menu[1].setY(pos_arr[1].y);
    bool selected[2] = { 0,0 };
    int xm = 0; int ym = 0;
    SDL_Event m_event;


    text_menu[0].LoadFromRenderText(font_time, g_screen);
    text_menu[0].RenderText(g_screen, pos_arr[0].x, pos_arr[0].y);
    text_menu[1].LoadFromRenderText(font_time, g_screen);
    text_menu[1].RenderText(g_screen, pos_arr[1].x, pos_arr[1].y);
    while (true)
    {
       

           while (SDL_PollEvent(&m_event))
           {
               switch (m_event.type)
               {
               case SDL_QUIT:
                       return 1;
               case SDL_MOUSEMOTION:
               {
                   xm = m_event.motion.x;
                   ym = m_event.motion.y;
                   for (int i = 0; i < kitem; i++)
                   {
                       if (SDLCommonfunc::checkmouse(xm, ym, text_menu[i].getRect()))
                       {
                           
                           if (selected[i] == false)
                           {
                               selected[i] = 1;
                               text_menu[i].SetColor(TextObject::RED_TEXT);
                               text_menu[i].LoadFromRenderText(font_time, g_screen);
                               text_menu[i].RenderText(g_screen, pos_arr[i].x, pos_arr[i].y);
                           }
                       }
                       else {
                           if (selected[i] == true)
                           {
                               selected[i] = 0;
                               text_menu[i].SetColor(TextObject::MENU_TEXT);
                               text_menu[i].LoadFromRenderText(font_time, g_screen);
                               text_menu[i].RenderText(g_screen, pos_arr[i].x, pos_arr[i].y);
                               
                           }
                       }
                   }
               }
               break;
               case SDL_MOUSEBUTTONDOWN:
               {
                   xm = m_event.button.x;
                   ym = m_event.button.y;
                   for (int i = 0; i < kitem; i++)
                   {
                       if (SDLCommonfunc::checkmouse(xm, ym, text_menu[i].getRect()))
                       {
                           return i;
                       }
                   }
               }
               break;
               case SDL_KEYDOWN:
                   if (m_event.key.keysym.sym == SDLK_ESCAPE)
                   {
                       return 1;
                   }
               default:
                   break;
               }
           }
          
           SDL_RenderPresent(g_screen);
    }
    return 1;
}

bool Loadanh() {

    bool ret = back_ground.loadImg("img//2.png", g_screen,1);
    back_ground3.loadImg("img//brg2.jpg", g_screen, 1);
    back_ground4.loadImg("img//gameover.jpg", g_screen, 1);
    back_ground2.loadImg("img//bg3.png", g_screen, 1);
    if (ret == false) return false;
    return true;
}
void close() {
    back_ground.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
}
vector<ThreatsObject*> MakeThreatList()
{
    vector<ThreatsObject*> list_threats;


    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for (int i = 0; i < 15; i++)
    {      
        ThreatsObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
           
            p_threat->LoadImg("img//threat_right.png", g_screen, 2);
            p_threat->LoadImg("img//threat_left.png", g_screen, 1);
            p_threat->setClip();
            p_threat->set_type_move(p_threat->MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos_(1000 + 1500 * i);
          
            if (i == 1)
            {
                p_threat->set_x_pos_(1528);
                
            }
            else if (i == 2) p_threat->set_x_pos_(3507);
            else if (i == 5) p_threat->set_x_pos_(7683);
            else if (i == 6) p_threat->set_x_pos_(8411);
            else if (i == 7)  p_threat->set_x_pos_(13019);
            else if (i == 8)  p_threat->set_x_pos_(13311);
            else if (i == 9)  p_threat->set_x_pos_(13639);
            else if (i == 10)  p_threat->set_x_pos_(13920);
            else if (i == 11)  p_threat->set_x_pos_(14728);
            else if (i == 12)  p_threat->set_x_pos_(15320);
            else if (i == 13)  p_threat->set_x_pos_(15744);
           
           

                p_threat->set_y_pos_(0);
            
            int pos1 = p_threat->get_x_pos_() - 60;
            int pos2 = p_threat->get_x_pos_() + 60;
            p_threat->setAnimation(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);


        }
    }
    ThreatsObject* threats_objs = new ThreatsObject[20];
    ThreatsObject* fly = new ThreatsObject[15];
    for(int i = 1; i < 13; i++)
    {
        ThreatsObject* fly = new ThreatsObject[15];
        ThreatsObject* p_threat = (fly + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg2("img//bombay.png", g_screen, 1);
            p_threat->setClip2();
            p_threat->set_type_move(p_threat->FLY);

            if (i == 1)
            {
                p_threat->set_x_pos_(2650);
                p_threat->set_y_pos_(100);
            }
            else if (i == 2)
            {
                p_threat->set_x_pos_(4100);
                p_threat->set_y_pos_(100);
            }
            else if (i == 3)
            {
                p_threat->set_x_pos_(11051);
                p_threat->set_y_pos_(100);
            }
            else if (i == 4)
            {
                p_threat->set_x_pos_(13464);
                p_threat->set_y_pos_(250);
            }
            else if (i == 5)
            {
                p_threat->set_x_pos_(16227);
                p_threat->set_y_pos_(80);
            }
            else if (i == 6)
            {
                p_threat->set_x_pos_(16227+300);
                p_threat->set_y_pos_(80);
            }
            else if (i == 7)
            {
                p_threat->set_x_pos_(16227+600);
                p_threat->set_y_pos_(80);
            }
            else if (i == 8)
            {
                p_threat->set_x_pos_(16227 + 900);
                p_threat->set_y_pos_(80);
            }
            else if (i == 9)
            {
                p_threat->set_x_pos_(16227 + 1200);
                p_threat->set_y_pos_(80);
            }
            else if (i == 10)
            {
                p_threat->set_x_pos_(16227 + 1500);
                p_threat->set_y_pos_(80);
            }
            else if (i == 11)
            {
                p_threat->set_x_pos_(16227 + 1800);
                p_threat->set_y_pos_(80);
            }
            else if (i == 12)
            {
                p_threat->set_x_pos_(2650+200);
                p_threat->set_y_pos_(100);
            }
           
            

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            BulletObject* p_bullet2 = new BulletObject();
            p_threat->InitBullet2(p_bullet2, g_screen);
            BulletObject* p_bullet3 = new BulletObject();
            p_threat->InitBullet3(p_bullet3, g_screen);
            BulletObject* p_bullet4 = new BulletObject();
            p_threat->InitBullet4(p_bullet4, g_screen);
            BulletObject* p_bullet5 = new BulletObject();
            p_threat->InitBullet5(p_bullet5, g_screen);
            BulletObject* p_bullet6 = new BulletObject();
            p_threat->InitBullet6(p_bullet6, g_screen);
            BulletObject* p_bullet7 = new BulletObject();
            p_threat->InitBullet7(p_bullet7, g_screen);
            BulletObject* p_bullet8 = new BulletObject();
            p_threat->InitBullet8(p_bullet8, g_screen);
           
            list_threats.push_back(p_threat);
        }
    }
    for (int i = 0; i < 14; i++)
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if (p_threat != NULL)
        {

            p_threat->LoadImg("img//threat_level.png", g_screen,1);
            p_threat->LoadImg3("img//threat_level1.png", g_screen, 2);

           // p_threat->setClip();
            if (i == 1)
            {
                p_threat->set_x_pos_(6859);
                p_threat->set_y_pos_(386);
            }
            else  if (i == 0)
            {
                p_threat->set_x_pos_(6043);
                p_threat->set_y_pos_(191.8);
            }
            else if (i == 2)
            {

                p_threat->set_x_pos_(7760);
                p_threat->set_y_pos_(386);
            }

            else if (i == 3)
            {
                p_threat->set_x_pos_(8388);
                p_threat->set_y_pos_(386);
            }
            else if (i == 4)
            {
                p_threat->set_x_pos_(10253);
                p_threat->set_y_pos_(386);
            }
            else if (i == 5)
            {
                p_threat->set_x_pos_(11599);
                p_threat->set_y_pos_(191.8);
            }
            else if (i == 6)
            {
                p_threat->set_x_pos_(11783);
                p_threat->set_y_pos_(191.8);
            }
            else if (i == 7)
            {
                p_threat->set_x_pos_(12111);
                p_threat->set_y_pos_(191.8);
            }
            else if (i == 8)
            {
                p_threat->set_x_pos_(12359);
                p_threat->set_y_pos_(191.8);
            }
            else if (i == 9)
            {
                p_threat->set_x_pos_(12487);
                p_threat->set_y_pos_(191.8);
            }
            else if (i == 10)
            {
                p_threat->set_x_pos_(14736);
                p_threat->set_y_pos_(386);
            }
            else if (i == 11)
            {
                p_threat->set_x_pos_(14736+150);
                p_threat->set_y_pos_(386);
            }
            else if (i == 12)
            {
                p_threat->set_x_pos_(14736 + 600);
                p_threat->set_y_pos_(386);
            }
            else if (i == 13)
            {
                p_threat->set_x_pos_(14736 +850);
                p_threat->set_y_pos_(386);
            }
            else if (i == 14)
            {
                p_threat->set_x_pos_(14736 + 850+150);
                p_threat->set_y_pos_(386);
            }


           
            
            p_threat->set_type_move(p_threat->STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);
        }
    }   
   
    return list_threats;
}

 
 vector<fire*> makelistfire()
 {
     vector<fire*> fire_list;
     fire* list_fire = new fire[20];
     for (int i = 0; i < 5; i++)
     {
         fire* tmp = list_fire + i;
         if (tmp != nullptr)
         {
            bool rett= tmp->LoadImg("img//fire.png", g_screen,1);
            tmp->set_clip();
             tmp->set_x_val_(-15);
             tmp->set_y_val_(8);
             tmp->set_x_pos_(1700 + 300 * i-500);
             tmp->set_y_pos_(0);
           
         }
         fire_list.push_back(tmp);
     }
     return fire_list;

 }
 
 vector<fire*> makelistfire2()
 {
     vector<fire*> fire_list2;
     fire* list_fire2 = new fire[20];
     for (int i = 0; i < 10; i++)
     {
         fire* tmp = list_fire2 + i;
         if (tmp != nullptr)
         {
             bool rettt = tmp->LoadImg("img//fire.png", g_screen,1);
             tmp->set_clip();
             tmp->set_x_val_(-15);
             tmp->set_y_val_(8);
             tmp->set_x_pos_(9939-640 + 300 * i-300);
             tmp->set_y_pos_(100);

         }
         fire_list2.push_back(tmp);
     }
     return fire_list2;

 }
 vector<ExplosionObject*> makelistexp()
 {
     vector<ExplosionObject*> exp_list;
     ExplosionObject* exp_list2 = new ExplosionObject[30];
     for (int i = 0; i < 30; i++)
     {
         ExplosionObject* tmp = exp_list2 + i;
           
         if (tmp != NULL)
         {
             tmp->loadImg3("img//exp2.png", g_screen, 1);
             tmp->set_clip3();
             
         }
         exp_list.push_back(tmp);
     }
     return exp_list;

 }
 

 int main(int argc, char* args[])
 {
     pos_listt.push_back(0);
     Time fps_time;
     if (Initdata() == false) return -1;
     if (Loadanh() == false) return -1;
     bool rett = showMenu();
     bool is_quit = false;
     if (rett == 1) is_quit = true;

     Gamemap game_map;
     game_map.Loadmap("map/map04.dat");
     game_map.LoadTile(g_screen);

     PlayerPower player_power;
     player_power.Init(g_screen, player_power.tt);

     PlayerMoney player_money;
     player_money.Init(g_screen);

     mainObject player(g_screen);
     player.LoadImg("img//player_right.png", g_screen, 1);
     player.LoadImg("img//player_left.png", g_screen, 2);
     player.LoadImg("img//jum_right.png", g_screen, 3);
     player.LoadImg("img//jum_left.png", g_screen, 4);
     player.set_clip();
     khien khienn;
     khienn.LoadImg("img//khien.png", g_screen, 1);
     khienn.set_clip();
     khien warning;
     warning.LoadImg3("img//warning.png", g_screen, 1);
     warning.set_clip3();
    vector< khien*> khien_item;

     baseObject khien_item2;
     baseObject dan4;
     baseObject hp_item;
     baseObject hp;
     vector<baseObject*> hp1;
     baseObject boss_item;

     boss_item.loadImg2("img//boss_item.png", g_screen);

     hp_item.loadImg2("img//hp1.png", g_screen);
     khien_item2.loadImg("img//khien3.png", g_screen, 1);
     
     dan4.loadImg("img//bullet.png", g_screen, 1);
     hp.loadImg2("img//hp.png", g_screen);
    
     khien* khien_tmp = new khien[20];
     for (int i = 0; i < 4; i++)
     {
         khien* ktmp = khien_tmp + i;
         if (i == 0) {
            
             ktmp->LoadImg("img//khien2.png", g_screen, 1);
             ktmp->set_clip2();
             ktmp->x_pos = 1680;
             ktmp->y_pos = 383.8;
         }
         
        
         else if (i == 2)
         {
             ktmp->LoadImg("img//khien2.png", g_screen, 1);
             ktmp->set_clip2();
             ktmp->x_pos =11920;
             ktmp->y_pos = 191.8;
         }
         else if (i == 3)
         {
             ktmp->LoadImg("img//khien2.png", g_screen, 1);
             ktmp->set_clip2();
             ktmp->x_pos = 17250;
             ktmp->y_pos = 383.8;
         }
         khien_item.push_back(ktmp);
     }

     khien fire4;
     fire4.LoadImg("img//exp4.png", g_screen, 1);
     fire4.set_clip();
     //khien_item2.set_clip2();
     vector<khien*> heart;
     khien dan3;
     dan3.LoadImg3("img//box.png", g_screen, 1);
     dan3.set_clip3();

     {     khien* heart1 = new khien[10];
     for (int i = 0; i < 3; i++)
     {
         khien* heart3 = heart1 + i;
         heart3->LoadImg3("img//heart.png", g_screen, 1);
         heart3->set_clip3();
         heart.push_back(heart3);
     }
     }
     khien fire_item;
     khien fire_item2;
     fire_item.LoadImg3("img/fire3.png", g_screen, 1);
     fire_item.set_clip3();
     fire_item2.LoadImg3("img/fire3.png", g_screen, 1);
     fire_item2.set_clip3();
     Map map = game_map.gamemap;

     vector<ThreatsObject*> list_threat = MakeThreatList();

     vector<fire*> list_fire = makelistfire();
     vector<fire*> list_fire2 = makelistfire2();
     //boss threat
     BossObject bossObject;
     int hpboss = bossObject.getHp();
     bossObject.loadImg("img//boss_object.png", g_screen, 1);
     bossObject.set_clips();

     int xposboss = MAX_MAP_X * TILE_SIZE - Screen_WIDTH * 0.6;
     int yposboss = 20;


     ExplosionObject exp_threat;
     bool tRet = exp_threat.loadImg("img//exp3.png", g_screen, 1);
     ExplosionObject exp_fire;
     bool ttRet = exp_fire.loadImg2("img//Explosion.png", g_screen, 1);
     vector<ExplosionObject*> exp_list;



     if (ttRet)
     {
         exp_fire.set_clip2();

     }
     if (tRet)
     {
         exp_threat.set_clip();

     }
     else return -1;
     ExplosionObject exp_main;
     bool mRet = exp_main.loadImg("img//exp3.png", g_screen, 1);

     if (mRet)
     {
         exp_main.set_clip();

     }
     else return -1;
     
     TextObject time_game;
     time_game.SetColor(TextObject::WHITE_TEXT);
     TextObject time_khien;
     TextObject time_dan;
     time_khien.SetColor(TextObject::RED_TEXT);
     time_game.SetColor(TextObject::WHITE_TEXT);
     TextObject mark_game;
     mark_game.SetColor(mark_game.WHITE_TEXT);
     UINT mark_val = 0;
     TextObject money_game;
     money_game.SetColor(money_game.WHITE_TEXT);





     while (!is_quit) {
         fps_time.start();

         while (SDL_PollEvent(&g_event) != 0) {
             if (g_event.type == SDL_QUIT) {

                 is_quit = true;
             }
             if(lose==false)
             player.xulihd(g_event, g_screen, g_sound_bullet);

         }
         if (lose == true)
         {

             SDL_RenderClear(g_screen);
             back_ground4.Render(g_screen, NULL);

             SDL_RenderPresent(g_screen);
         }
         else
         {
             if (player.y_pos < MAX_MAP_Y * TILE_SIZE) dem = 0;
             if (player.y_pos >= MAX_MAP_Y * TILE_SIZE && dem == 0)
             {
                 player.hp--;
                 dem++;
                 player_power.Decrease();
                 if (player.hp <= 0)
                 {
                     lose = true;
                     SDL_RenderClear(g_screen);
                     back_ground4.Render(g_screen, NULL);

                     SDL_RenderPresent(g_screen);
                 }
             }
             SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
             SDL_RenderClear(g_screen);

             back_ground.Render(g_screen, NULL);


             player.handleBullet(g_screen, map);
             player.setMapXY(map.start_x, map.start_y);

             player.doPlayer(map, item);
             player.show(g_screen);
             for (int i = 0; i < khien_item.size(); i++)
             {
                 khien* tmp = khien_item.at(i);
                 tmp->setmapXY(map.start_x, map.start_y);
                 tmp->show2(g_screen, map);

                 bool bcolkhien = SDLCommonfunc::CheckCollision(player.getRectframe(), tmp->getRectframe());

                 if (bcolkhien && dem1[i] == 0)
                 {
                     Mix_PlayChannel(-1, item[1], 0);
                     dem1[i] = 1;
                     tmp->Free();
                 }
                 if (bcolkhien == true) {
                     khienn.status = 1;
                 }
                 if (khienn.status == 1) {
                     khien_item2.setRect(0, 40);
                     khien_item2.Render(g_screen, NULL);
                     khienn.setRect(player.getRect().x - 14, player.getRect().y - 11);
                     khienn.show(g_screen, map);
                 }
             }
             
             if (khienn.status == 1) {
                 khien_item2.setRect(0, 40);
                 khien_item2.Render(g_screen, NULL);
                 khienn.setRect(player.getRect().x - 14, player.getRect().y - 11);
                 khienn.show(g_screen, map);
             }
             for (int i = 0; i < 3; i++)
             {
                 khien* tmp = heart.at(i);
                 if (i == 0)
                 {
                     if (tmp->heart_tt == 0)
                     {

                         tmp->setmapXY(map.start_x, map.start_y);
                         tmp->setRect(2992 - tmp->map_x_, 258.8 - tmp->map_y_);
                         tmp->show(g_screen, map);
                     }
                 }
                 else if (i == 1)
                 {
                     if (tmp->heart_tt == 0)
                     {

                         tmp->setmapXY(map.start_x, map.start_y);
                         tmp->setRect(10696 - tmp->map_x_, 255 - tmp->map_y_);
                         tmp->show(g_screen, map);
                     }
                 }
                 else if (i == 2)
                 {
                     if (tmp->heart_tt == 0)
                     {

                         tmp->setmapXY(map.start_x, map.start_y);
                         tmp->setRect(6600 - tmp->map_x_, 383.8 - tmp->map_y_);
                         tmp->show(g_screen, map);
                     }
                 }
                
             }

             if (fire_tt == false) {
                 fire_item.setmapXY(map.start_x, map.start_y);
                 fire_item.setRect(13464 - fire_item.map_x_, 383 - fire_item.map_y_);
                 fire_item.show(g_screen, map);

             }
             if (fire_tt2 == false) {
                 fire_item2.setmapXY(map.start_x, map.start_y);
                 fire_item2.setRect(15096 - fire_item2.map_x_, 383 - fire_item2.map_y_);
                 fire_item2.show(g_screen, map);

             }
             bool bcolfire = false; bool bcolfire1 = false;
             bcolfire = SDLCommonfunc::CheckCollision(player.getRectframe(), fire_item.getRectframe());
             bcolfire1 = SDLCommonfunc::CheckCollision(player.getRectframe(), fire_item2.getRectframe());
             if (bcolfire)
             {

                 if (fire_tt == false) { thu = 1; }

                 fire_tt = true;
             }
             if (bcolfire1)
             {

                 if (fire_tt2 == false) { thu = 1; }

                 fire_tt2 = true;
             }
             for (int i = 0; i < 3; i++)
             {
                 khien* heartt = heart.at(i);
                 bool bcolheart = SDLCommonfunc::CheckCollision(player.getRectframe(), heartt->getRectframe());
                 if (bcolheart && dem2[i] == 0)
                 {

                     if (heartt->heart_tt == 0)
                     {
                         dem2[i] = 1;
                         Mix_PlayChannel(-1, item[1], 0);
                         player_power.InitCrease();
                         player.hp++;
                         heartt->heart_tt = 1;

                     }

                 }
             }
             if (dan33 == false) {
                 dan3.setmapXY(map.start_x, map.start_y);
                 dan3.setRect(9933 - dan3.map_x_, 191 - dan3.map_y_);
                 dan3.show(g_screen, map);
                 
             }
             if (player.tia3 == true)
             {
                 dan3.Free();
                 dan4.setRect(0, 90);
                 dan4.Render(g_screen);
             }
             if (dan33 == false) {
                 bool bcolit = SDLCommonfunc::CheckCollision(player.getRectframe(), dan3.getRectframe());
                 if (bcolit == true)
                 {
                    
                     dan33 = true; player.tia3 = true;
                 }
             }
             game_map.setMap(map);
             game_map.DrawMap(g_screen);

             GeometricFormat rectangle_size{ 0,0,Screen_WIDTH,40 };
             ColorData color_data(0, 80, 150);
             Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

             GeometricFormat outlineSize(1, 1, Screen_WIDTH - 1, 38);
             ColorData color_data2(255, 0, 0);

             Geometric::RenderOutline(outlineSize, color_data2, g_screen);

             player_power.Show(g_screen);

             player_money.SetPos(Screen_WIDTH * 0.5 - 300, 8);
             player_money.Show(g_screen);
             int val = MAX_MAP_X * TILE_SIZE - (map.start_x + player.getRect().x);
             bool bcol3 = false;
             bool bcol4 = false;
             bool bcol5 = false;


             int width_exp_frame = exp_main.get_frame_width();
             int height_exp_frame = exp_main.get_frame_height();
             if (val <= Screen_WIDTH && tt_boss == 0)
             {
                 tt_boss = 1;
                 stt_boss = true;

             }
             if (stt_boss == true)
             {
                 if (hpboss > 0)
                 {



                     bossObject.set_xpos(xposboss);
                     bossObject.set_ypos(yposboss);
                     bossObject.setMapXY(map.start_x, map.start_y);
                     bossObject.DoPlayer(map);
                     bossObject.Show(g_screen);
                     bossObject.MakeBullet(g_screen, Screen_WIDTH, Screen_HEIGHT, map,g_sound_bullet);





                     bcol3 = SDLCommonfunc::CheckCollision(player.getRectframe(), bossObject.getRectframe());
                     for (int i = 0; i < player.get_bullet_list().size(); i++)
                     {
                         if (hpboss <= 0) break;
                         BulletObject* bulletp = player.get_bullet_list().at(i);
                         bcol5 = SDLCommonfunc::CheckCollision(bulletp->getRect(), bossObject.getRectframe());
                         if (bcol5)
                         {
                             pos_listt.push_back(400 - 20 * pos_listt.size());


                             hp.pos_list.push_back(400 - 20 * (pos_listt.size() - 1));




                             hpboss--;
                             for (int ex = 0; ex < 8; ex++)
                             {
                                 Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                 int x_pos = bulletp->getRect().x;
                                 int y_pos = bulletp->getRect().y;
                                 
                                 exp_main.set_frame(ex);
                                 exp_main.setRect(x_pos, y_pos);
                                 exp_main.show(g_screen);
                                 SDL_RenderPresent(g_screen);

                             }
                             player.RemoveBullet(i);
                             if (hpboss == 0) {
                                 break;


                             }



                         }

                     }
                     hp.setRect(100, 50);

                     hp.Render3(g_screen);
                     boss_item.setRect(0, 50);
                     boss_item.Render2(g_screen);
                     if (pos_listt.size() != 1)
                     {
                         for (int r = 0; r < pos_listt.size() - 1; r++)
                         {
                             hp_item.setRect(pos_listt[pos_listt.size() - 1 - r] + hp.rect.x, 50);

                             hp_item.Render2(g_screen);
                         }
                     }
                     bool checkk = false;
                     if (player.x_pos + Screen_WIDTH >= xposboss) checkk = true;
                     for (int i = 0; i < bossObject.get_bullet_list().size(); i++)
                     {
                         BulletObject* p_bullet = bossObject.get_bullet_list().at(i);

                         bcol4 = SDLCommonfunc::CheckCollision(player.getRectframe(), p_bullet->getRect());
                         if (bcol4)
                         {
                             bossObject.RemoveBullet(i);
                         }
                         if (checkk == false)  bossObject.RemoveBullet(i);

                     }

                     if ((bcol3 == true || bcol4 == true) && hpboss > 0&&khienn.status==0)
                     {

                         player.hp--;
                         for (int ex = 0; ex < 4; ex++)
                         {
                             Mix_PlayChannel(-1, g_sound_exp[0], 0);
                             int x_pos = (player.getRect().x + player.width_frame * 0.5) - width_exp_frame * 0.5;
                             int y_pos = (player.getRect().y + player.height_frame * 0.5) - height_exp_frame * 0.5;
                            
                             exp_main.set_frame(ex);
                             exp_main.setRect(x_pos, y_pos);
                             exp_main.show(g_screen);
                             SDL_RenderPresent(g_screen);

                         }
                         if (player.hp > 0)
                         {


                             player.x_pos -= 300;
                             player.y_pos -= 300;
                             SDL_Delay(1000);
                             player_power.Decrease();
                             player_power.Render(g_screen);
                             continue;
                         }
                         else
                         {
                             lose = true;
                             SDL_RenderClear(g_screen);
                             back_ground4.Render(g_screen, NULL);

                             SDL_RenderPresent(g_screen);
                         }


                     }
                 }
                 else
                 {
                     win = true;
                     SDL_RenderClear(g_screen);
                     back_ground3.Render(g_screen, NULL);

                     SDL_RenderPresent(g_screen);


                 }

             }



             for (int i = 0; i < list_threat.size(); i++)
             {
                 ThreatsObject* p_threat = list_threat.at(i);

                 p_threat->setmapXY(map.start_x, map.start_y);
                 if (p_threat != NULL)
                 {
                     if (p_threat->type_move_ == p_threat->FLY)
                     {


                         p_threat->impTypeMove(g_screen);
                         p_threat->doPlayer2(map);
                         vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                         for (int jj = 0; jj < tBullet_list.size(); jj++)
                         {
                             BulletObject* pt_bullet = tBullet_list.at(jj);

                             pt_bullet->setMapXY(map.start_x, map.start_y);
                         }
                         p_threat->MakeBullet2(g_screen, Screen_WIDTH, Screen_HEIGHT, map, g_sound_bullet);

                         cout << player.x_pos << " " << player.y_pos << endl;
                         p_threat->show2(g_screen);

                     }
                     else if (p_threat->type_move_ == p_threat->MOVE_IN_SPACE_THREAT)
                     {
                         p_threat->setmapXY(map.start_x, map.start_y);

                         p_threat->impTypeMove(g_screen);
                         p_threat->doPlayer(map);
                         //  p_threat->MakeBullet(g_screen, Screen_WIDTH, Screen_HEIGHT, map);

                         p_threat->show3(g_screen);
                     }
                     else
                     {

                         p_threat->setmapXY(map.start_x, map.start_y);
                         if (p_threat->get_x_pos_() - 150 <= player.x_pos && p_threat->get_x_pos_() + 150 >= player.x_pos && player.y_pos >= p_threat->get_y_pos_() - 100)
                         {






                             fire4.setmapXY(map.start_x, map.start_y);


                             fire4.setRect(p_threat->rect.x - 100, p_threat->rect.y - 200);
                             bool firec = SDLCommonfunc::CheckCollision(player.getRectframe(), fire4.getRectframe());
                             if (!firec)
                             {
                                 Mix_PlayChannel(-1, g_sound_exp[4], 0);
                                 fire4.show4(g_screen, map);
                                 SDL_RenderPresent(g_screen);
                             }
                             if (firec)
                             {
                                 if (player.hp > 0)
                                 {

                                     fire4.setRect(player.rect.x - 100, player.rect.y - 200);
                                     for (int z = 0; z < 2; z++)
                                     {
                                         Mix_PlayChannel(-1, g_sound_exp[4], 0);
                                         fire4.frame++;
                                         fire4.show4(g_screen, map);
                                         SDL_RenderPresent(g_screen);
                                     }
                                     if (khienn.status == 0)
                                     {
                                         player.hp--;
                                         player.x_pos -= 300;
                                         player.y_pos -= 300;
                                         SDL_Delay(1000);
                                         player_power.Decrease();
                                         player_power.Render(g_screen);
                                     }
                                     p_threat->Free();
                                     list_threat.erase(list_threat.begin() + i);
                                     mark_val++;



                                 }
                                 else
                                 {
                                     lose = true;
                                     SDL_RenderClear(g_screen);
                                     back_ground4.Render(g_screen, NULL);

                                     SDL_RenderPresent(g_screen);
                                 }
                                 if (player.hp <= 0)
                                 {
                                     lose = true;
                                     SDL_RenderClear(g_screen);
                                     back_ground4.Render(g_screen, NULL);

                                     SDL_RenderPresent(g_screen);
                                 }


                             }






                         }

                         else {

                             p_threat->show4(g_screen);
                         }


                     }
                     SDL_Rect rect_player = player.getRectframe();
                     bool bcol1 = false;
                     bool ckhien1 = false;
                     bool ckhien2 = false;
                     vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                     for (int jj = 0; jj < tBullet_list.size(); jj++)
                     {
                         BulletObject* pt_bullet = tBullet_list.at(jj);

                         pt_bullet->setMapXY(map.start_x, map.start_y);

                         //  cout << pt_bullet->map_x << "   " << pt_bullet->map_y << endl;
                        
                         if (pt_bullet != NULL)
                         {
                             bcol1 = SDLCommonfunc::CheckCollision(rect_player, pt_bullet->getRect());
                             ckhien1 = SDLCommonfunc::CheckCollision(khienn.getRectframe(), pt_bullet->getRect());

                             if (bcol1)
                             {

                                 //p_threat->RemoveBullet(jj);
                                 break;
                             }
                         }
                     }
                     SDL_Rect rect_threat = p_threat->getRectframe();
                     bool bcol2 = SDLCommonfunc::CheckCollision(rect_player, rect_threat);
                     ckhien2 = SDLCommonfunc::CheckCollision(khienn.getRectframe(), rect_threat);



                     if (khienn.status == 0) {
                         if (bcol1 == true || bcol2 == true)
                         {


                             for (int ex = 0; ex < 4; ex++)
                             {
                                 int x_pos = (player.getRect().x + player.width_frame * 0.5) - width_exp_frame * 0.5;
                                 int y_pos = (player.getRect().y + player.height_frame * 0.5) - height_exp_frame * 0.5;
                                 Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                 exp_main.set_frame(ex);
                                 exp_main.setRect(x_pos, y_pos);
                                 exp_main.show(g_screen);
                                 SDL_RenderPresent(g_screen);

                             }
                             player.hp--;
                             if (player.hp > 0)
                             {


                                 player.x_pos -= 300;
                                 player.y_pos -= 300;
                                 SDL_Delay(1000);
                                 player_power.Decrease();
                                 player_power.Render(g_screen);
                                 continue;
                             }
                             else
                             {
                                 lose = true;
                                 SDL_RenderClear(g_screen);
                                 back_ground4.Render(g_screen, NULL);

                                 SDL_RenderPresent(g_screen);
                             }
                         }
                     }
                     else
                     {
                         if (ckhien1 || ckhien2)
                         {
                             if (ckhien2)
                             {
                                 p_threat->Free();
                                 list_threat.erase(list_threat.begin() + i);
                                 mark_val++;
                             }

                             for (int ex = 0; ex < 8; ex++)
                             {
                                 int x_pos = (player.getRect().x + player.width_frame * 0.5) - width_exp_frame * 0.5;
                                 int y_pos = (player.getRect().y + player.height_frame * 0.5) - height_exp_frame * 0.5;
                                 Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                 exp_main.set_frame(ex);
                                 exp_main.setRect(x_pos, y_pos);
                                 exp_main.show(g_screen);
                                 SDL_RenderPresent(g_screen);

                             }

                         }














                     }



                 }
             }


             vector<BulletObject*> bullet_arr = player.get_bullet_list();
             for (int r = 0; r < bullet_arr.size(); r++)
             {
                 BulletObject* p_bullet = bullet_arr.at(r);
                 if (p_bullet != NULL)
                 {
                     for (int t = 0; t < list_threat.size(); t++)
                     {
                         ThreatsObject* p_threat = list_threat.at(t);
                         if (p_threat != NULL)
                         {
                             SDL_Rect tRect;
                             tRect.x = p_threat->getRect().x;
                             tRect.y = p_threat->getRect().y;
                             tRect.w = p_threat->get_width_frame_();
                             tRect.h = p_threat->get_height_frame_();

                             SDL_Rect bRect = p_bullet->getRect();
                             bool bcol = SDLCommonfunc::CheckCollision(tRect, bRect);
                             if (bcol && p_threat->type_move_ != p_threat->STATIC_THREAT)
                             {
                                 mark_val++;
                                 for (int ex = 0; ex < 8; ex++)
                                 {
                                     Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                     int frame_exp_width = exp_threat.get_frame_width();
                                     int frame_exp_height = exp_threat.get_frame_height();
                                     int x_pos = p_bullet->getRect().x - frame_exp_width * 0.5;
                                     int y_pos = p_bullet->getRect().y - frame_exp_height * 0.5;
                                     exp_threat.set_frame(ex);
                                     exp_threat.setRect(x_pos, y_pos);
                                     exp_threat.show(g_screen);
                                 }
                                 player.RemoveBullet(r);
                                 p_threat->Free();
                                 list_threat.erase(list_threat.begin() + t);
                                 mark_val++;
                             }
                             else if (bcol && p_threat->type_move_ == p_threat->STATIC_THREAT)

                             {
                                 player.RemoveBullet(r);
                                 if (p_bullet->bullet_dir == p_bullet->DIR_LEFT||p_bullet->bullet_dir==p_bullet->DIR_UP_LEFT)
                                 {
                                     mark_val++;
                                     for (int ex = 0; ex < 8; ex++)
                                     {
                                         Mix_PlayChannel(-1, g_sound_exp[0], 0);
                                         int frame_exp_width = exp_threat.get_frame_width();
                                         int frame_exp_height = exp_threat.get_frame_height();
                                         int x_pos = p_bullet->getRect().x - frame_exp_width * 0.5;
                                         int y_pos = p_bullet->getRect().y - frame_exp_height * 0.5;
                                         exp_threat.set_frame(ex);
                                         exp_threat.setRect(x_pos, y_pos);
                                         exp_threat.show(g_screen);
                                     }

                                     p_threat->Free();
                                     list_threat.erase(list_threat.begin() + t);
                                     mark_val++;
                                 }
                             }

                         }
                     }
                 }
             }
             if (player.x_pos >= 1250 && fire1 == false)
             {
                 fire11 = true;
             }
             else if (player.x_pos >= 1450)
             {
                 fire11 = false;
             }
             if (fire11 == true)
             {
                 warning.setRect(1120, 50);
                 warning.show(g_screen, map);
             }
             if (player.x_pos >= 1450)
             {

                 fire1 = true;

             }
             if (fire1 == true)
             {
                 for (int i = 0; i < list_fire.size(); i++)
                 {

                     fire* tmp = list_fire.at(i);

                     if (tmp != NULL)
                     {
                         tmp->setmapXY(map.start_x, map.start_y);
                         tmp->show(g_screen, map);
                         bool bcol6 = SDLCommonfunc::CheckCollision(player.getRectframe(), tmp->getRectframe());



                         if (bcol6 || tmp->CheckToMapX(map))
                         {
                             if (bcol6 == true && khienn.status == 0)
                             {
                                 player.hp--;
                                 if (player.hp > 0 <= 3)
                                 {
                                     for (int i = 0; i < 12; i++)
                                     {
                                         Mix_PlayChannel(-1, g_sound_exp[3], 0);
                                         exp_fire.set_frame(i);
                                         exp_fire.setRect(player.getRect().x - 50, player.getRect().y - 50);
                                         exp_fire.show(g_screen);

                                         SDL_RenderPresent(g_screen);
                                     }

                                     player.x_pos -= 300;
                                     player.y_pos -= 300;
                                     SDL_Delay(1000);
                                     player_power.Decrease();
                                     player_power.Render(g_screen);
                                     list_fire.clear();
                                     continue;
                                 }
                                 else
                                 {
                                     lose = true;
                                     SDL_RenderClear(g_screen);
                                     back_ground4.Render(g_screen, NULL);

                                     SDL_RenderPresent(g_screen);
                                 }
                             }
                             tmp->Free();
                             // list_fire.erase(list_fire.begin() + i);

                             for (int i = 0; i < 12; i++)
                             {
                                 Mix_PlayChannel(-1, g_sound_exp[3], 0);

                                 exp_fire.set_frame(i);
                                 exp_fire.setRect(tmp->getRect().x, tmp->getRect().y);
                                 exp_fire.show(g_screen);
                                 SDL_RenderPresent(g_screen);
                             }


                         }

                     }
                 }

             }
             if (player.x_pos >= 9200 && fire2 == false)
             {
                 fire22 = true;
             }
             else if (player.x_pos >= 1450)
             {
                 fire22 = false;
             }
             if (fire22 == true)
             {
                 warning.setRect(1120, 50);
                 warning.show(g_screen, map);
             }
             if (player.x_pos >= 9400)
             {
                 fire2 = true;
             }
             if (fire2 == true)
             {
                 for (int i = 0; i < list_fire2.size(); i++)
                 {


                     fire* tmp = list_fire2.at(i);

                     if (tmp != NULL)
                     {
                         tmp->setmapXY(map.start_x, map.start_y);
                         tmp->show(g_screen, map);

                         bool bcol7 = SDLCommonfunc::CheckCollision(player.getRectframe(), tmp->getRectframe());



                         if (bcol7 || tmp->CheckToMapX(map))
                         {
                             if (bcol7 == true)
                             {

                                 if (player.hp > 0)
                                 {
                                     for (int i = 0; i < 12; i++)
                                     {
                                         Mix_PlayChannel(-1, g_sound_exp[3], 0);
                                         exp_fire.set_frame(i);
                                         exp_fire.setRect(player.getRect().x - 50, player.getRect().y - 50);
                                         exp_fire.show(g_screen);

                                         SDL_RenderPresent(g_screen);
                                     }
                                     if (khienn.status == 0)
                                     {
                                         player.hp--;
                                         player.x_pos -= 300;
                                         player.y_pos -= 300;
                                         SDL_Delay(1000);
                                         player_power.Decrease();
                                         player_power.Render(g_screen);
                                         list_fire2.clear();
                                         break;
                                     }
                                     list_fire2.clear();
                                 }
                                 else
                                 {
                                     lose = true;
                                     SDL_RenderClear(g_screen);
                                     back_ground4.Render(g_screen, NULL);

                                     SDL_RenderPresent(g_screen);
                                 }
                             }
                             tmp->Free();
                             //   list_fire2.erase(list_fire2.begin() + i);

                             for (int i = 0; i < 12; i++)
                             {

                                 exp_fire.set_frame(i);
                                 exp_fire.setRect(tmp->x_pos, tmp->y_pos);
                                 exp_fire.show(g_screen);
                                 SDL_RenderPresent(g_screen);
                             }


                         }
                     }
                 }

             }

             if (win == false && lose == false) {


                 string str_time = "Time: ";
                 Uint32 time_val2;
                 Uint32 time_val3;
                 Uint32 time_val = SDL_GetTicks() / 1000;
                 if (khienn.status == 0) {

                     time_val2 = SDL_GetTicks() / 1000;
                     time_khienn = double(time_val2);
                 }
                 if (player.tia3 == false) {

                     time_val3 = SDL_GetTicks() / 1000;
                     time_dann = double(time_val3);
                 }
                 string str_khien = "";
                 string str_dan = "";
                 
                 Uint32 val_time = 300 - time_val;
                 if (val_time <= 0)
                 {
                     lose = true;
                     SDL_RenderClear(g_screen);
                     back_ground4.Render(g_screen, NULL);

                     SDL_RenderPresent(g_screen);
                 }
                 else
                 {
                     string str_val = to_string(val_time);
                     str_time += str_val;

                     time_game.SetText(str_time);
                     time_game.LoadFromRenderText(font_time, g_screen);
                     time_game.RenderText(g_screen, Screen_WIDTH - 200, 15);

                 }

                 if (khienn.status == 1) {
                     Uint32 time_val_khien = SDL_GetTicks() / 1000 - time_khienn;


                     Uint32 val_khien = 15 - time_val_khien;

                     if (val_khien >= 1000)
                     {
                         khienn.status = 0;
                     }
                     else {

                         string str_val2 = to_string(val_khien);
                         str_khien += str_val2;
                         str_khien += "s";

                         time_khien.SetText(str_khien);
                         time_khien.LoadFromRenderText(font_time, g_screen);
                         time_khien.RenderText(g_screen, 40, 60);
                     }
                 }
                 if (player.tia3 == true) {
                     Uint32 time_val_dan = SDL_GetTicks() / 1000 - time_dann;


                     Uint32 val_dan = 15 - time_val_dan;

                     if (val_dan >= 1000)
                     {
                         player.tia3 = false;
                     }
                     else {

                         string str_val3 = to_string(val_dan);
                         str_dan += str_val3;
                         str_dan += "s";

                         time_dan.SetText(str_dan);
                         time_dan.LoadFromRenderText(font_time, g_screen);
                         time_dan.RenderText(g_screen, 40, 120);
                     }
                 }
                 string val_str_mark = to_string(mark_val);
                 string strMark("Mark: ");
                 strMark += val_str_mark;

                 mark_game.SetText(strMark);
                 mark_game.LoadFromRenderText(font_time, g_screen);
                 mark_game.RenderText(g_screen, Screen_WIDTH * 0.5 - 50, 15);

                 int money_count = player.getMoneyCount();
                 string money_str = to_string(money_count);
                 money_game.SetText(money_str);
                 money_game.LoadFromRenderText(font_time, g_screen);
                 money_game.RenderText(g_screen, Screen_WIDTH * 0.5 - 250, 15);


                 for (int i = 0; i < list_threat.size(); i++)
                 {
                     ThreatsObject* tmp = list_threat.at(i);
                     if (tmp->type_move_ == ThreatsObject::FLY)
                     {

                     }
                 }

                 if (thu == 1)
                 {
                     SDL_RenderClear(g_screen);
                     back_ground2.Render(g_screen, NULL);
                     SDL_RenderPresent(g_screen);



                     thu = 0;

                     for (int i = 0; i < list_threat.size(); i++)
                     {
                         ThreatsObject* tmp = list_threat.at(i);
                         if (tmp != NULL)
                         {


                             if (tmp->rect.x >= fire_item.rect.x - Screen_WIDTH / 2 && tmp->rect.x <= fire_item.rect.x + Screen_WIDTH / 2)
                             {

                                 ExplosionObject* exp_firetmp1 = new ExplosionObject();
                                 exp_firetmp1->loadImg3("img//exp2.png", g_screen, 1);
                                 exp_firetmp1->set_clip3();
                                 for (int jj = 0; jj < 12; jj++)
                                 {
                                     Mix_PlayChannel(-1, g_sound_exp[1], 0);
                                     exp_firetmp1->set_frame(jj);
                                     exp_firetmp1->setRect(tmp->getRect().x - 50, tmp->getRect().y);
                                     exp_firetmp1->show(g_screen);
                                     SDL_Delay(50);
                                     SDL_RenderPresent(g_screen);
                                 }


                                 exp_list.push_back(exp_firetmp1);
                                 tmp->Free();
                                 list_threat.erase(list_threat.begin() + i);
                                 mark_val++;
                                 i--;

                             }


                         }
                     }
                 }
             }

                 

             }
             j++;
             SDL_RenderPresent(g_screen);

             int real_time = fps_time.getTicks();
             int time_one_frame = 1000 / fps;
             if (real_time < time_one_frame) {
                 int delay_time = time_one_frame - real_time;
                 if (delay_time >= 0) {
                     SDL_Delay(delay_time);
                 }
             }

         }
         for (int i = 0; i < list_threat.size(); i++)
         {
             ThreatsObject* p_threat = list_threat.at(i);
             if (p_threat)
             {
                 p_threat->Free();
                 p_threat = nullptr;
             }
         }
        

         list_threat.clear();
         close();
         return 0;
     

}
