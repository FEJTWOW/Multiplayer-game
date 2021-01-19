#ifndef PLAYERACTION_H
#define PLAYERACTION_H

enum action { moveUp, moveDown, moveLeft, moveRight, shoot };

struct PlayerAction
{
    action action;
};

#endif // PLAYERACTION_H
