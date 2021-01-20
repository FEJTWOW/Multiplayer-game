#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "score.h"
#include "settings.h"
#include "obstacle.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include "serversocket.h"


// Generalnie jest zrobione bardzo na szypko i jest bardzo źle
// Trzeba:
//  1. Z gracza zrobić graczy
//  2. Z punktów gracza zrobić punkty graczy
//  3. Enemy - w zasadzie to można przerobić jakoś na przeszkody?
//      To jest czysto testowe/niepotrzebne/eksperymentalne
//  4. Trzeba wszystko zrefaktorować tak, żeby było trzymane w porządnej strukturze ->
//      Gra -> Gracze -> Każdy ma swoje pociski -> Pociski muszą badać z kim mają kolizję, żeby wiedzieć kto zabił itp.
//                    -> Każdy ma swoje punkty życia
//                    -> Każdy ma swoje punkty+ można śledzić inne statystyki (kill streak itp.)
//                      (tu w zasadzie można po prostu mieć x struktur mających analogiczne indeksy czy cos)
//                    -> Zależnie od tego, z jaką strukturą skończymy, trzeba będzie przemyśleć, gdzie dane rzeczy mają się wykonywać/sprawdzać itp
//                    -> Trzeba przemyśleć, jako co dodać innych graczy (też po prostu Player i korzystać z focusu? zadziała?)
//                    -> Można potencjalnie dodać opcje do np. zmiany rozdzielczości itp.
//
//
// 5. Większość rzeczy trzeba zrefaktoryzować ze stałych na zmienne (jakieś tam rozmiary okna itp. jako część klasy, porobić konstruktory itp.)
// 6. Do bullet->move() dodać obsługę Key_UP/Down + Key_Left/Right na raz.
//      Usunąć kolizję pocisków z sobą (tudzież nie uwzględniać pkt.)
//  Wiecej mi sie nie chce na razie


class Game: public QGraphicsView
{
public:
    Game(QWidget * parent =0);
    void initGame();
    void addNewPlayer(QPoint point, QSize size);
    void generateObstacles(int count);
    QGraphicsScene * graphicsScene;
    QList <Player*> players;
    QList <Score*> playerScores;
    Settings * settings;
    int numOfPlayers;
private:
    ServerSocket* sock;
};

#endif // GAME_H
