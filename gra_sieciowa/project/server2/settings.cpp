#include "settings.h"

Settings::Settings()
{
    // Screen settings
    screen_size = {800,600};
    screen_point = {0,0};

    // Game settings
    game_timer_res = 20;
    respawn_time_in_ms = 5000;

    // Player settings
     player_speed = 7;
     player_size = {35,35};
     player_point = {0,0};
     player_color = Qt::red;//Qt::cyan
     player_shot_cd_in_ms = 350;
     player_max_count = 5;
     player_max_bullets = 5;
     player_invul_time_in_ms = 800;
     player_spawns[0] = QPointF(75, screen_size.height()-player_size.height());
     player_spawns[1] = QPointF(250, screen_size.height()-player_size.height());
     player_spawns[2] = QPointF(375, screen_size.height()-player_size.height());
     player_spawns[3] = QPointF(500, screen_size.height()-player_size.height());
     player_spawns[4] = QPointF(625, screen_size.height()-player_size.height());

    // Bullet settings
     bullet_speed = 8;
     bullet_size = {5,20};
     bullet_point = {0,0} ;
     bullet_color = Qt::blue;

    // Score settings
     score_color = Qt::red;
     score_font = {"System", 14};
     score_passive_interval_in_ms = 1000;   // This would need to setup another timer
     score_passive_value = 30;
     score_kill_value = 5000;

    // Obstacles settings
     obstacle_min_size = 5;
     obstacle_max_size = 30;
        //
        //
    // Enemy settings
     enemy_speed = 1;
     enemy_size = {50,50};
        //
        //
        //
        //
}
