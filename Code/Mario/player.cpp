#include "player.h"
#include <iostream>

using std::cout;
using std::endl;

Player::Player()
{
    score = 0;
}

Player::~Player()
{
    cout << "DELETING PLAYER";
}

Player::Player(sf::Texture* left, sf::Texture* right, QString l, QString r, sf::Vector2f sp)
{
    spawnPoint = sp;

    texLeft = left;
    texRight = right;
    texLeftName = l;
    texRightName = r;
    setTexture(*texRight);
    textureName = texRightName;
    standingTile = NULL;

    entityType = EntityType::PLAYER;

    dead = false;
    health = 3;

    score = 0;

    setPosition(sp);

    jumpVelocity = -20;
}

void Player::movement(Direction dir, float deltaTime)
{
    if (dir == Direction::RIGHT)
    {
        if (velocity.x < 0) velocity.x = 0;
        velocity.x += acceleration.x * deltaTime;

        if (textureName == texLeftName)
        {
            textureName = texRightName;
            setTexture(*texRight);
        }
    }
    else if (dir == Direction::LEFT)
    {
        if (velocity.x > 0) velocity.x = 0;
        velocity.x -= acceleration.x * deltaTime;

        if (textureName == texRightName)
        {
            textureName = texLeftName;
            setTexture(*texLeft);
        }
    }
    else velocity.x = 0;

    if (velocity.x > maxVelocity.x * deltaTime / 16.6) velocity.x = maxVelocity.x * deltaTime / 16.6;
    if (velocity.x < -maxVelocity.x * deltaTime / 16.6) velocity.x = -maxVelocity.x * deltaTime / 16.6;
    if (velocity.y > maxVelocity.y * deltaTime / 16.6) velocity.y = maxVelocity.y * deltaTime / 16.6;
}

void Player::update(float deltaTime)
{
    if (getPosition().y + getTexture()->getSize().y >= 800) die();
    else
    {
        if (standingTile == NULL) velocity.y += acceleration.y * deltaTime;
        move(velocity.x, 0);
        if (velocity.y != 0) move(0, velocity.y * deltaTime / 16.6);
    }
}

void Player::jump()
{
    standingTile = NULL;
    velocity.y = jumpVelocity;
}

void Player::die()
{
    health--;
    if (health <= 0)
    {
        dead = true;
        cout << "PLAYER is DEAD!" << endl; //POL MORM ŠE NAREST DA SE ŠPIL USTAV
    }
    else
    {
        setPosition(spawnPoint);
        velocity.x = 0;
        velocity.y = 0;
    }
    standingTile = NULL;
}

int Player::getHealth()
{
    return health;
}

bool Player::isDead()
{
    return dead;
}

void MovableEntity::increaseScore(int s)
{
    score += s;
}

int MovableEntity::getScore()
{
    return score;
}

