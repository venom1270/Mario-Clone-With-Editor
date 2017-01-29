#ifndef ENTITY_H
#define ENTITY_H

#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <QString>

enum class EntityType
{
    TILE,
    ENEMY,
    EXIT,
    PLAYER,
    COIN
};

class Entity : public sf::Sprite
{
protected:
    QString textureName; //kasneje PROPERTIES STRUCT
    EntityType entityType;
    bool collision;
public:
    ~Entity();
    Entity();
    Entity(sf::Texture *tex, QString texName, int x, int y);
    EntityType getEntityType();
    QString getTextureName();
    void setCollision(bool c);
    bool getCollision();

    //klamfanje
    virtual void clearStandingTile();
    //coin
    virtual int getScoreValue();
};

#endif // ENTITY_H
