#ifndef COIN_H
#define COIN_H

#include "entity.h"

class Coin : public Entity
{
    int score;
public:
    Coin(sf::Texture *tex, QString texName, int x, int y, int s);
    int getScoreValue();
    void setScoreValue(int s);
};

#endif // COIN_H
