#ifndef SETTINGS_H
#define SETTINGS_H

#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRect>

class Settings
{
public:
    Settings();

    // Screen settings
        QSize screen_size;
        QPoint screen_point;

    // Game settings
         int game_timer_res;
         int respawn_time_in_ms;

    // Player settings
         int player_speed;
         static const int player_max_count = 5;
         int player_max_bullets;
         QSize player_size;
         QPoint player_point;
         QColor player_color;
         QPointF player_spawns[5];
         int player_shot_cd_in_ms;
         int player_invul_time_in_ms;

    // Bullet settings
        int bullet_speed;
        QSize bullet_size;
        QPoint bullet_point;
        QColor bullet_color;

    // Score settings
        QColor score_color;
        QFont score_font;
        int score_passive_interval_in_ms;
        int score_passive_value;
        int score_kill_value;


    // Obstacles settings
        QSize obstacle_size;
        //
        //
        //
    // Enemy settings
        int enemy_speed;
        QSize enemy_size;
        //
        //
        //
        //
        //


};

#endif // SETTINGS_H
