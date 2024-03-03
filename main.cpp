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

baseObject duc;
TTF_Font* font_time=NULL;
bool Initdata() {
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        return false;

    }

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
    else{ 
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
        font_time = TTF_OpenFont("font//dlxfont_.ttf",15);
        if (font_time == NULL)
        {
            success = false;
        }
    
    }
    return success;;
}
bool Loadanh() {

    bool ret = duc.loadImg("img//2.png", g_screen);
    if (ret == false) return false;
    return true;
}
void close() {
    duc.Free();

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
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL) 
        {
            p_threat->LoadImg("img//threat_left.png", g_screen);
            p_threat->setClip();
            p_threat->set_type_move(p_threat->MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos_(500 + 500 * i);
            p_threat->set_y_pos_(200);
            int pos1 = p_threat->get_x_pos_() - 60;
            int pos2 = p_threat->get_x_pos_() + 60;
            p_threat->setAnimation(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
            

        } 
    }
    ThreatsObject* threats_objs = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if(p_threat!=NULL)
        {
            
            p_threat->LoadImg("img//threat_level.png", g_screen);
            p_threat->setClip();
            p_threat->set_x_pos_(700+i*1200);
            p_threat->set_y_pos_(250);
            p_threat->set_type_move(p_threat->STATIC_THREAT);
            p_threat->set_input_left(0);
            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }
    return list_threats;
}



int main(int argc, char* args[]) {
    Time fps_time;
    if (Initdata() == false) return -1;
    if (Loadanh() == false) return -1;
   

    Gamemap game_map;
    game_map.Loadmap("map/map01.dat");
    game_map.LoadTile(g_screen);
    
    PlayerPower player_power;
    player_power.Init(g_screen);

    PlayerMoney player_money;
    player_money.Init(g_screen);

    mainObject player;
    player.LoadImg("img//player_right.png", g_screen);
    player.set_clip();
    
    vector<ThreatsObject*> list_threat = MakeThreatList();

    //boss threat
    BossObject bossObject;
    bossObject.loadImg("img//boss_object.png", g_screen);
    bossObject.set_clips();
    
    int xposboss = 600;
    bossObject.set_xpos(xposboss);
    bossObject.set_ypos(10);
    ExplosionObject exp_threat;
    bool tRet = exp_threat.loadImg("img//exp3.png", g_screen);
    
    if (tRet)
    {
        exp_threat.set_clip();
     
    }
    else return -1;
    ExplosionObject exp_main;
    bool mRet = exp_main.loadImg("img//exp3.png", g_screen);

    if (mRet)
    {
        exp_main.set_clip();

    }
    else return -1;
    int num_die = 0;
    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject mark_game;
    mark_game.SetColor(mark_game.WHITE_TEXT);
    UINT mark_val = 0;
    TextObject money_game;
    money_game.SetColor(money_game.WHITE_TEXT);


    bool is_quit = false;
    
    while (!is_quit) {
        fps_time.start();
        
        while (SDL_PollEvent(&g_event) != 0) {
            if (g_event.type == SDL_QUIT) {

                is_quit = true;
            }
            player.xulihd(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
        SDL_RenderClear(g_screen);

        duc.Render(g_screen, NULL);
        
        Map map = game_map.gamemap;
        player.handleBullet(g_screen);
        player.setMapXY(map.start_x,map.start_y);
        
        player.doPlayer(map);
        player.show(g_screen);
       
        game_map.setMap(map);
        game_map.DrawMap(g_screen);

        GeometricFormat rectangle_size{ 0,0,Screen_WIDTH,40 };
        ColorData color_data(0, 80, 150);
        Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

        GeometricFormat outlineSize(1, 1, Screen_WIDTH - 1,38);
        ColorData color_data2(255, 0, 0);

        Geometric::RenderOutline(outlineSize, color_data2, g_screen);

        player_power.Show(g_screen);

        player_money.SetPos(Screen_WIDTH*0.5-300, 8);
        player_money.Show(g_screen);
       
        bossObject.setMapXY(map.start_x, map.start_y);
        bossObject.DoPlayer(map);
        bossObject.MakeBullet(g_screen, Screen_WIDTH, Screen_HEIGHT);
        bossObject.Show(g_screen);
        bool bcol3 = false;
        bool bcol4 = false;
        bool bcol5 = false;
        bcol3 = SDLCommonfunc::CheckCollision(player.getRectframe(), bossObject.getRectframe());
        for (int i = 0; i < player.get_bullet_list().size(); i++)
        {
            BulletObject* bulletp = player.get_bullet_list().at(i);
            bcol5 = SDLCommonfunc::CheckCollision(bulletp->getRect(), bossObject.getRectframe());
            if(bcol5)
            {
               int hpboss= bossObject.getHp();



            }
        }
        for (int i = 0; i < bossObject.get_bullet_list().size(); i++)
        {
            BulletObject* p_bullet = bossObject.get_bullet_list().at(i);
            
            bcol4 = SDLCommonfunc::CheckCollision(player.getRectframe(), p_bullet->getRect());
            if (bcol4)
            {
                bossObject.RemoveBullet(i);
            }

         }
        int width_exp_frame = exp_main.get_frame_width();
        int height_exp_frame = exp_main.get_frame_height();
        if (bcol3 == true||bcol4==true) {
            num_die++;
            for (int ex = 0; ex < 4; ex++)
            {
                int x_pos = (player.getRect().x + player.width_frame * 0.5) - width_exp_frame * 0.5;
                int y_pos = (player.getRect().y + player.height_frame * 0.5) - height_exp_frame * 0.5;

                exp_main.set_frame(ex);
                exp_main.setRect(x_pos, y_pos);
                exp_main.show(g_screen);
                SDL_RenderPresent(g_screen);

            }
             if (num_die <= 3)
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
                        if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
           
            
        }
       
        
        
        for (int i = 0; i < list_threat.size(); i++)
        {
            ThreatsObject* p_threat = list_threat.at(i);
            if(p_threat!=NULL)
            {
                p_threat->setmapXY(map.start_x, map.start_y);
               
                p_threat->impTypeMove(g_screen);
                p_threat->doPlayer(map);
                p_threat->MakeBullet(g_screen, Screen_WIDTH, Screen_HEIGHT);
                p_threat->show(g_screen);
                SDL_Rect rect_player = player.getRectframe();
                bool bcol1 = false;
                vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int jj = 0; jj < tBullet_list.size(); jj++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(jj);
                    if (pt_bullet != NULL)
                    {
                        bcol1 = SDLCommonfunc::CheckCollision(rect_player, pt_bullet->getRect());
                        if (bcol1)
                        {
                            p_threat->RemoveBullet(jj);
                            break;
                        }
                    }
                }
                SDL_Rect rect_threat = p_threat->getRectframe();
                bool bcol2= SDLCommonfunc::CheckCollision(rect_player,rect_threat);
               
                
                   
                

                if (bcol1 == true || bcol2 == true )
                {
                   

                    for (int ex = 0; ex < 4; ex++)
                    {
                        int x_pos = (player.getRect().x + player.width_frame *0.5) - width_exp_frame * 0.5;
                        int y_pos = (player.getRect().y + player.height_frame* 0.5) - height_exp_frame * 0.5;

                        exp_main.set_frame(ex);
                        exp_main.setRect(x_pos, y_pos);
                        exp_main.show(g_screen);
                        SDL_RenderPresent(g_screen);
                        
                    }
                    num_die++;
                    if (num_die <= 3)
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
                        if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                    }
                    



            }
        }
        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
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
                        if (bcol)
                        {
                            mark_val++;
                            for (int ex = 0; ex < 8; ex++)
                            {
                                int x_pos = p_bullet->getRect().x - frame_exp_width * 0.5;
                                int y_pos = p_bullet->getRect().y - frame_exp_height * 0.5;
                                exp_threat.set_frame(ex);
                                exp_threat.setRect(x_pos, y_pos);
                                exp_threat.show(g_screen);
                           }
                            player.RemoveBullet(r);
                            p_threat->Free();
                            list_threat.erase(list_threat.begin() + t);
                        }

                    }
                }
            }
        }
        //show game time
        string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;
        if (val_time <= 0)
        {
            if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
            {
                is_quit = true;
                break;
               
            }
        }
        else
        {
           string str_val = to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, Screen_WIDTH - 200, 15);

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
       
        //show boss
        int val = MAX_MAP_X * TILE_SIZE - (map.start_x + player.getRect().x);
        

        
        //if (val <= Screen_WIDTH) {
            
        //}
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
            p_threat = NULL;
        }
    }

    close();
    return 0;
   
}
