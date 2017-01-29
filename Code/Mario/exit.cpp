#include "exit.h"
#include <iostream>


Exit::Exit()
{
    entityType = EntityType::EXIT;
}

Exit::Exit(sf::Texture *tex, QString texName, int x, int y, QString winMsg, QString nm)
{
    setTexture(*tex);
    textureName = texName;
    setPosition(sf::Vector2f(x, y));
    winMessage = winMsg;
    nextMap = nm;

}

QString Exit::getWinMessage()
{
    return winMessage;
}

QString Exit::getNextMap()
{
    return nextMap;
}
