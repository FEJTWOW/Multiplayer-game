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

    // Player settings
         int player_speed;
         QSize player_size;
         QPoint player_point;
         QColor player_color;
         int player_shot_cd_in_ms;

    // Bullet settings
        int bullet_speed;
        QSize bullet_size;
        QPoint bullet_point;
        QColor bullet_color;

    // Score settings
        QColor score_color;
        QFont score_font;


    // Obstacles settings
        int obstacle_min_size;
        int obstacle_max_size;
        //
        //
        //
    // Enemy settings
        //
        //
        //
        //
        //
        //


};

#endif // SETTINGS_H
