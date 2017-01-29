#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "movableentity.h"
#include "enemy.h"
#include "player.h"
#include <vector>
#include "Globals.h"
#include "exit.h"
#include <QList>

class CollisionManager
{
    bool log;
public:
    CollisionManager();
    void collision(MovableEntity &movable, QList<Entity *> &tiles, float deltaTime);
    void collision(Player &player, QList<Enemy*> &enemies, float deltaTime, GameState& gs);
    void collision(Player &player, QList<Exit*> &exits, GameState& gs);
};

#endif // COLLISIONMANAGER_H
