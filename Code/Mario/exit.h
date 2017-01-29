#ifndef EXIT_H
#define EXIT_H

#include "entity.h"

class Exit : public Entity
{
private:
    QString nextMap;
    QString winMessage;
public:
    Exit();
    Exit(sf::Texture *tex, QString texName, int x, int y, QString winMsg, QString nm);
    QString getWinMessage();
    QString getNextMap();
};

#endif // EXIT_H
