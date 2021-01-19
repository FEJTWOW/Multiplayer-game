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

    // Player settings
         int player_speed;
         QSize player_size;
         QPoint player_point;
         QColor player_color;

    // Bullet settings
        int bullet_speed;
        QSize bullet_size;
        QPoint bullet_point;
        QColor bullet_color;

    // Score settings
        QColor score_color;
        QFont score_font;


    // Obstacles settings
        //
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
