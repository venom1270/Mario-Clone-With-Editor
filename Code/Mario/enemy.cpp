#include "enemy.h"
#include <iostream>

using std::cout;
using std::endl;

Enemy::Enemy()
{
    patrolLength = 0;
}

Enemy::Enemy(sf::Texture *tex, QString texName, sf::Vector2f sp, int p)
{
    entityType = EntityType::ENEMY;
    setTexture(*tex);
    textureName = texName;
    spawnPoint = sp;
    setPosition(spawnPoint);
    patrolLength = p;
    standingTile = NULL;
    dir = Direction::RIGHT;
    maxVelocity.x /= 2;
    velocity.x = maxVelocity.x / 1000;
    velocity.y = 0.f;
    acceleration.x = .5;
}

void Enemy::movement(float deltaTime)
{
    if (dir == Direction::RIGHT)
    {
        if (getPosition().x - spawnPoint.x > patrolLength)
        {
            changeDirection();
        }
    }
    else
    {
        if (getPosition().x < spawnPoint.x)
        {
            changeDirection();
        }
    }
    int f = 1;
    if (dir == Direction::LEFT) f = -1;
    velocity.x += f * acceleration.x * deltaTime / 16.6;

    if (velocity.x > maxVelocity.x * deltaTime / 16.6) velocity.x = maxVelocity.x * deltaTime / 16.6;
    if (velocity.x < -maxVelocity.x * deltaTime / 16.6) velocity.x = -maxVelocity.x * deltaTime / 16.6;
    if (velocity.y > maxVelocity.y * deltaTime / 16.6) velocity.y = maxVelocity.y * deltaTime / 16.6;

    /*if (standingTile == NULL)
    {
        velocity.y += acceleration.y * deltaTime; //skače neki..ni tuki problem...
        //velocity.x = 0.f;
    }*/
}

void Enemy::setPatrolLength(int p)
{
    patrolLength = p;
}

void Enemy::changeDirection()
{
    if (dir == Direction::RIGHT)
    {
        dir = Direction::LEFT;
        cout << "SPREMINJAM LEVO" << endl;
        velocity.x = -1;
    }
    else
    {
        dir = Direction::RIGHT;
        cout << "SPREMINJAM DESNO" << endl;
        velocity.x = 1;
    }
}

void Enemy::setSpawnPoint(sf::Vector2f sp)
{
    spawnPoint = sp;
}

int Enemy::getPatrolLength()
{
    return patrolLength;
}
