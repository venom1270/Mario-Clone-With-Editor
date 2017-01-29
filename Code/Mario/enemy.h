#ifndef ENEMY_H
#define ENEMY_H

#include "movableentity.h"
#include "Globals.h"

class Enemy : public MovableEntity
{
private:
    int patrolLength;
    Direction dir;

public:
    Enemy();
    Enemy(sf::Texture* tex, QString texName, sf::Vector2f sp, int p);

    void movement(float deltaTime);

    void setPatrolLength(int p);
    void changeDirection();

    void setSpawnPoint(sf::Vector2f sp);

    int getPatrolLength();
};

#endif // ENEMY_H
