#ifndef GSETTINGS_H
#define GSETTINGS_H

#include <QSize>
#include <QPoint>
#include <QColor>
#include <QFont>

constexpr QSize screenSize = { 800, 600 };
constexpr QPoint screenPoint = { 0, 0 };

constexpr int playerSpeed = 10;
constexpr QSize playerSize = { 35, 35 };
const QColor playerColor = Qt::red;
const QColor player_colors[6] = {Qt::red, Qt::cyan, Qt::blue, Qt::green, Qt::darkYellow, Qt::darkRed};
constexpr int playerMaxCount = 5;
constexpr int playerMaxBullets = 5;
constexpr QPoint playerPoint = { 0, 0 };
constexpr int playerShotCd = 350;
constexpr int playerInvulTime = 800;
constexpr QPointF playerSpawns[5] = {
    { 75, screenSize.height()-playerSize.height() },
    { 250, screenSize.height()-playerSize.height() },
    { 375, screenSize.height()-playerSize.height() },
    { 500, screenSize.height()-playerSize.height() },
    { 625, screenSize.height()-playerSize.height() }
};

constexpr int respawnTime = 5000;
constexpr int gameTimerRes = 60;

constexpr QSize bulletSize = {10,10};
constexpr QPoint bulletPoint = {0,0};
const QColor bulletColor= Qt::blue;
constexpr int bulletSpeed = 20;

constexpr QSize obstacleSize {20,50};

constexpr int enemySpeed = 1;
constexpr QSize enemySize {50,50};


const QColor scoreColor = Qt::red;
const QFont scoreFont = {"System", 14};
constexpr int scorePassiveIntervalInMs = 10000;
constexpr int scorePassiveValue = 30;
constexpr int scoreKillValue = 100;
constexpr int scoreEnemyHit = 30;
constexpr int scoreObstacleHit = 5;

#endif // SETTINGS_H
