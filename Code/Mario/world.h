#ifndef WORLD_H
#define WORLD_H

#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include <texturemanager.h>
#include <vector>
#include "player.h"
#include "camera.h"
#include <windows.h>
#include "collisionmanager.h"
#include "enemy.h"
#include "coin.h"
#include "exit.h"
#include "Globals.h"
#include <QList>

using std::vector;

class World
{
private:

    //VPRAŠANJE AL DAT DA TALE VID EDITORJA AL DA PAČ EDITOR Z GET FUNKCJAM POBERE...
    sf::Text t;
    sf::Text pauseText;
    sf::Font f;
    GameState gs;

    //TIME LIMIT
    sf::Clock timer;
    int timeLimit;
    int remainingTime;
    sf::Text timerText;

    sf::Text gameOverText;
    sf::Text winText;
    sf::Text winDetails;
    bool scoreExported;

    struct EditorVariables
    {
        Entity* buffer; //to je za tile in coine
        EntityType bufferType; //za to da če damo več tilov, da ve al narest coin al tile
        Enemy* eBuffer;
        Exit* exitBuffer;
        int eBufferCount; //za zač. pozicijo in patrol
        int counter;

        bool drawGridLines;

        bool selectionMode;
        bool cleanMap;
        Entity* selection;
        Entity** selectionPointer;
        int selectionDrawMode;
        std::string importFile;
        std::string playerName;
    } ev;

    struct Tools
    {
        sf::Clock addTileMouseTimer;
        bool isLeftMouseDown;
        int mapWidth;
    } tools;

    sf::RenderWindow* window;
    TextureManager* tm;
    CollisionManager* cm;
    Camera* camera;

    //entitiji
    //vector<Entity*> tiles;
    QList<Entity*> tiles;
    QList<Enemy*> enemies;
    QList<Exit*> exits;
    Player* player;
    Entity* standingTile;

    void checkInput();
    void checkEvents();
    void update();
    void drawing();

    bool hasFocus;
    float deltaTime;

    HWND hWnd;


    //PRIVATE FUNKCIJE (EDITOR..)
    void drawGridLines();
    void drawSelectionLines();
    void defaultValues();


public:
    void addTile(QString tex, int x, int y); //addEntity() ?
    void addEnemy(QString tex, int x, int y, int pLength);
    void addExit(QString tex, int x, int y, QString winMsg, QString nextMap);
    void addCoin(QString tex, int x, int y, int score);
    World(TextureManager *textureManager);
    void run();
    void importFromFile(std::string f); //missing param


    //EDITOR FUNKCIJE
    void setAddTile(QString tex, int count);
    void unsetAddTile();
    void setAddEnemy(QString tex);
    void unsetAddEnemy();
    void setAddExit(QString tex, QString nextLevel);
    void unsetAddExit();
    void setAddCoin(QString tex, int count, int score);
    //void unsetAddCoin(); //tega nerabimo ker gre coin po entitybufferju

    void toggleGridLines();
    void setSelectionMode(bool b, int drawMode);
    sf::Vector2f getSelectedEntityPosition();
    void deleteSelectedEntity();

    void setEntityPosition(sf::Vector2f pos);
    void setMapWidth(int w);
    int getMapWidth();
    void exportToFile(std::string f);
    void setImportFile(std::string f, std::string playerName, int timeLimit);
    void setCleanMap();

    void cleanMap();
};

#endif // WORLD_H
