#include "coin.h"

Coin::Coin(sf::Texture *tex, QString texName, int x, int y, int s)
    :Entity(tex, texName, x, y)
{
    entityType = EntityType::COIN;
    score = s;
    collision = false;
}

int Coin::getScoreValue()
{
    return score;
}

void Coin::setScoreValue(int s)
{
    score = s;
}
