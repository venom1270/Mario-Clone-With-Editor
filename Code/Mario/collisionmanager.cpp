#include "collisionmanager.h"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
CollisionManager::CollisionManager()
{
}

void CollisionManager::collision(MovableEntity& movable, QList<Entity *> &tiles, float deltaTime)
{

    sf::Vector2u pSize = movable.getTexture()->getSize();
    sf::Vector2f pPos = movable.getPosition();
    pPos.y -= movable.getVelocity().y * deltaTime / 16.6;

    for (unsigned int i = 0; i < tiles.length(); i++)
    {
        sf::Vector2u tSize = tiles[i]->getTexture()->getSize();
        sf::Vector2f tPos = tiles[i]->getPosition();
        if (pPos.x + pSize.x > tPos.x && pPos.x < tPos.x + tSize.x &&
            pPos.y + pSize.y > tPos.y && pPos.y < tPos.y + tSize.y)
        {

            if (tiles[i]->getCollision())
            {
                if (pPos.x + pSize.x - tPos.x < tPos.x + tSize.x - pPos.x) { movable.setPosition(sf::Vector2f(tPos.x - pSize.x, movable.getPosition().y)); movable.setVelocity(sf::Vector2f(0.f , movable.getVelocity().y)); }
                else { movable.setPosition(sf::Vector2f(tPos.x + tSize.x, movable.getPosition().y)); movable.setVelocity(sf::Vector2f(0.f, movable.getVelocity().y)); }
                //cout << pPos.x << " " << pPos.y << " " << tPos.x << " " << tPos.y << endl;
                //cout << "World: Player collision X" << endl;
                if (movable.getEntityType() == EntityType::ENEMY) { cout << "COLLISION!!!!" << endl; movable.changeDirection();}
            }
            else if (tiles[i]->getEntityType() == EntityType::COIN && movable.getEntityType() == EntityType::PLAYER)
            {
                movable.increaseScore(tiles[i]->getScoreValue());
                delete tiles[i];
                tiles.erase(tiles.begin() + i);
                i--;
                continue;
            }
        }
    }

    Entity* standingTile = movable.getStandingTile();

    if (standingTile != NULL)
    if (pPos.x >= standingTile->getPosition().x + standingTile->getTexture()->getSize().x ||
        pPos.x + pSize.x <= standingTile->getPosition().x) { movable.clearStandingTile(); }

    pPos = movable.getPosition();
    //pPos.y += movable.getVelocity().y;
    if (movable.getStandingTile() == NULL)
    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        if (tiles[i]->getCollision())
        {
            sf::Vector2u tSize = tiles[i]->getTexture()->getSize();
            sf::Vector2f tPos = tiles[i]->getPosition();
            if (pPos.x + pSize.x > tPos.x && pPos.x < tPos.x + tSize.x &&
                pPos.y + pSize.y > tPos.y && pPos.y < tPos.y + tSize.y)
            {
                if (pPos.y + pSize.y - tPos.y <= tPos.y + tSize.y - pPos.y)
                {
                    movable.setPosition(sf::Vector2f(movable.getPosition().x, tPos.y - pSize.y)); movable.setVelocity(sf::Vector2f(movable.getVelocity().x, 0.f));
                    movable.setStandingTile(&tiles[i]);
                }
                else
                {
                    movable.setPosition(sf::Vector2f(movable.getPosition().x, tPos.y + tSize.y));
                    movable.setVelocity(sf::Vector2f(movable.getVelocity().x, 0.f));
                }
                //cout << "World: Player collision Y" << endl;

            }
        }
    }
    //if (movable.getStandingTile() == NULL && movable.getEntityType() == EntityType::PLAYER) cout << "NULLLLL" << endl;


}

void CollisionManager::collision(Player &player, QList<Enemy *> &enemies, float deltaTime, GameState &gs)
{
    sf::Vector2f pPos = player.getPosition();
    sf::Vector2u pSize = player.getTexture()->getSize();

    for (unsigned i = 0; i < enemies.size(); i++)
    {
        sf::Vector2f ePos = enemies[i]->getPosition();
        sf::Vector2u eSize = enemies[i]->getTexture()->getSize();

        if (pPos.x + pSize.x > ePos.x && pPos.x < ePos.x + eSize.x &&
            pPos.y + pSize.y > ePos.y && pPos.y < ePos.y + eSize.y)
        {
            if (pPos.y + pSize.y - ePos.y <= player.getVelocity().y * deltaTime)
            {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                i--;
            }
            else
            {
                player.die();
                if (player.getHealth() < 1) gs = GameState::LOST;
            }


        }
    }
}

void CollisionManager::collision(Player &player, QList<Exit *> &exits, GameState &gs)
{
    sf::Vector2f pPos = player.getPosition();
    sf::Vector2u pSize = player.getTexture()->getSize();

    for (unsigned i = 0; i < exits.size(); i++)
    {
        sf::Vector2f tPos = exits[i]->getPosition();
        sf::Vector2u tSize = exits[i]->getTexture()->getSize();
        if (pPos.x + pSize.x > tPos.x && pPos.x < tPos.x + tSize.x &&
            pPos.y + pSize.y > tPos.y && pPos.y < tPos.y + tSize.y)
        {
            gs = GameState::WON;
            cout << exits[i]->getWinMessage().toStdString() << endl;
        }
    }
}

