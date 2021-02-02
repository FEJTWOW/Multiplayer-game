#ifndef GSETTINGS_H
#define GSETTINGS_H

#include <QSize>
#include <QPoint>
#include <QColor>

constexpr QSize screen_size = { 800, 600 };
constexpr QPoint screen_point = { 0, 0 };

constexpr int player_speed = 10;
constexpr QSize player_size = { 35, 35 };
constexpr int player_max_count = 5;
constexpr int player_max_bullets = 5;
constexpr QPoint player_point = { 0, 0 };
constexpr int player_shot_cd = 350;
constexpr int player_invul_time = 800;
constexpr QPointF player_spawns[5] = {
    { 75, screen_size.height()-player_size.height() },
    { 250, screen_size.height()-player_size.height() },
    { 375, screen_size.height()-player_size.height() },
    { 500, screen_size.height()-player_size.height() },
    { 625, screen_size.height()-player_size.height() }
};

constexpr int respawn_time = 5000;


#endif // SETTINGS_H
