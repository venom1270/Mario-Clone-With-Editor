#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

#include "entity.h"

class MovableEntity : public Entity
{
protected:
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    sf::Vector2f maxVelocity;
    Entity** standingTile;
    sf::Vector2f spawnPoint;

    //player
    int score;

public:
    MovableEntity();
    void update(float deltaTime);
    virtual void movement(float deltaTime);

    sf::Vector2f getAcceleration();
    sf::Vector2f getVelocity();
    sf::Vector2f getMaxVelocity();
    sf::Vector2f getSpawnPoint();
    Entity* getStandingTile();

    void setAcceleration(sf::Vector2f a);
    void setVelocity(sf::Vector2f v);
    void setMaxVelocity(sf::Vector2f mv);
    void setSpawnPoint(sf::Vector2f sp);

    void setStandingTile(Entity* *e);
    void clearStandingTile();

    //player specific
    virtual void increaseScore(int s);
    virtual int getScore();

    //enemy specific
    virtual void changeDirection();
};

#endif // MOVABLEENTITY_H
