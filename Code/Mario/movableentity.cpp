#include "movableentity.h"

MovableEntity::MovableEntity()
{
    acceleration.x = 0.1;
    acceleration.y = 0.05;
    velocity.x = 0.f;
    velocity.y = 0.f;
    maxVelocity.x = 8.f;
    maxVelocity.y = 30.f;
    standingTile = NULL;
    score = 0;
}

void MovableEntity::update(float deltaTime)
{
    if (standingTile == NULL) velocity.y += acceleration.y * deltaTime;
    move(velocity.x, velocity.y * deltaTime / 16.6);
}

void MovableEntity::movement(float deltaTime)
{

}

sf::Vector2f MovableEntity::getAcceleration()
{
    return acceleration;
}

sf::Vector2f MovableEntity::getVelocity()
{
    return velocity;
}

sf::Vector2f MovableEntity::getMaxVelocity()
{
    return maxVelocity;
}

sf::Vector2f MovableEntity::getSpawnPoint()
{
    return spawnPoint;
}

Entity* MovableEntity::getStandingTile()
{
    if (standingTile != NULL) return *standingTile;
    else return NULL;
}

void MovableEntity::setAcceleration(sf::Vector2f a)
{
    acceleration = a;
}

void MovableEntity::setVelocity(sf::Vector2f v)
{
    velocity = v;
}

void MovableEntity::setMaxVelocity(sf::Vector2f mv)
{
    maxVelocity = mv;
}

void MovableEntity::setSpawnPoint(sf::Vector2f sp)
{
    spawnPoint = sp;
}

void MovableEntity::setStandingTile(Entity* *e)
{
    standingTile = e;
}

void MovableEntity::clearStandingTile()
{
    standingTile = NULL;
}

void MovableEntity::changeDirection()
{
}
