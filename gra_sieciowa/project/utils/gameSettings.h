#ifndef GSETTINGS_H
#define GSETTINGS_H

#include <QSize>
#include <QPoint>
#include <QColor>
#include <QFont>
#include <QGradient>


constexpr QSize screenSize = { 800, 600 };
constexpr QPoint screenPoint = { 0, 0 };

constexpr int playerSpeed = 10;
constexpr QSize playerSize = { 35, 35 };
const QColor playerColor = Qt::red;
const QColor player_colors[6] = {Qt::red, Qt::cyan, Qt::blue, Qt::green, Qt::darkYellow, Qt::magenta};
const QGradient::Preset playerGradientColors[6] = {QGradient::StrongBliss, QGradient::AquaGuidance, QGradient::NightSky, QGradient::DustyGrass, QGradient::SandStrike, QGradient::MixedHopes};
constexpr int playerMaxCount = 5;
constexpr int playerMaxBullets = 5;
constexpr QPoint playerPoint = { 0, 0 };
constexpr int playerShotCd = 350;
constexpr int playerInvulTime = 1000;
constexpr QPointF playerSpawns[5] = {
    { 75, screenSize.height()-playerSize.height() },
    { 250, screenSize.height()-playerSize.height() },
    { 375, screenSize.height()-playerSize.height() },
    { 525, screenSize.height()-playerSize.height() },
    { 675, screenSize.height()-playerSize.height() }
};

constexpr int respawnTime = 5000;
constexpr int gameTimerRes = 60;

constexpr QSize bulletSize = {10,10};
constexpr QPoint bulletPoint = {0,0};
const QColor bulletColor= Qt::blue;
constexpr int bulletSpeed = 20;

constexpr QSize obstacleSize {20,50};
const QColor obstacleColor = Qt::darkGray;
constexpr double obstacleOpacity = 0.90;

constexpr int enemySpeed = 1;
constexpr QSize enemySize {50,50};
const QColor enemyColor = Qt::darkMagenta;
constexpr double enemyOpacity = 0.85;

constexpr double playerInvulnerableOpacity = 0.2;

const QColor scoreColor = Qt::red;
const QFont scoreFont = {"System", 14};
constexpr int scorePassiveIntervalInMs = 1500;
constexpr int scorePassiveValue = 30;
constexpr int scoreKillValue = 10000000;
constexpr int scoreEnemyHit = 2500;
constexpr int scoreObstacleHit = 20;

#endif // SETTINGS_H
