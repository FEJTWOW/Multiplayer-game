#include "settings.h"

Settings::Settings()
{
    // Screen settings
    screen_size = {800,600};
    screen_point = {0,0};

    // Player settings
     player_speed = 10;
     player_size = {50,50};
     player_point = {0,0};
     player_color = Qt::red;

    // Bullet settings
     bullet_speed = 10;
     bullet_timer_in_ms = 20;
     bullet_size = {5,20};
     bullet_point = {0,0} ;
     bullet_color = Qt::blue;

    // Score settings
     score_color = Qt::red;
     score_font = {"System", 14};

    // Obstacles settings
     obstacle_min_size = 5;
     obstacle_max_size = 30;
        //
        //
    // Enemy settings
        //
        //
        //
        //
        //
        //
}
