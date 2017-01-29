#ifndef PLAYER_H
#define PLAYER_H

#include "movableentity.h"
#include "Globals.h"

class Player : public MovableEntity
{
private:
    int health;
    int score;
    float jumpVelocity;

    sf::Texture* texLeft;
    sf::Texture* texRight;

    QString texLeftName;
    QString texRightName;

    bool dead;


public:
    ~Player();
    Player();
    Player(sf::Texture* left, sf::Texture* right, QString l, QString r, sf::Vector2f sp);

    void movement(Direction dir, float deltaTime);
    void update(float deltaTime);

    void jump();

    int getHealth();
    bool isDead();

    /*void increaseScore(int s);
    int getScore();*/

    void die();
};

#endif // PLAYER_H
