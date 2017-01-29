#include "entity.h"

Entity::~Entity()
{
    collision = true;
}

Entity::Entity()
{
    collision = true;
}

Entity::Entity(sf::Texture* tex, QString texName, int x, int y)
{
    setTexture(*tex);
    textureName = texName;
    setPosition(float(x), float(y));
    entityType = EntityType::TILE;
    collision = true;
}


EntityType Entity::getEntityType()
{
    return entityType;
}

QString Entity::getTextureName()
{
    return textureName;
}

void Entity::setCollision(bool c)
{
    collision = c;
}

bool Entity::getCollision()
{
    return collision;
}

void Entity::clearStandingTile()
{
}

int Entity::getScoreValue()
{
}
