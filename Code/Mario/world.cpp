#include "world.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Globals.h"

using std::cout;
using std::endl;
using std::string;

World::World(TextureManager *textureManager)
{
    gs = GameState::CLEAN;
    window = new sf::RenderWindow;
    tm = textureManager;
    standingTile = NULL;
    //importFromFile();
    //player = new Player(tm->getTexture("mario_left.png"), tm->getTexture("mario_right.png"), "left", "right", sf::Vector2f(100.f, 100.f));
    //camera = new Camera(window, player);

    cm = new CollisionManager();

    defaultValues();



}

void World::run()
{
    defaultValues();
   // gs = GameState::PLAYING;

    f.loadFromFile("res\\fonts\\arial.ttf");
    t.setFont(f);
    t.setPosition(700, 50);
    t.setCharacterSize(15);
    t.setColor(sf::Color::Cyan);

    pauseText.setFont(f);
    pauseText.setCharacterSize(20);
    pauseText.setColor(sf::Color::White);

    timerText.setFont(f);
    timerText.setCharacterSize(30);
    timerText.setColor(sf::Color::White);

    gameOverText.setFont(f);
    gameOverText.setCharacterSize(50);
    gameOverText.setColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");

    winText.setFont(f);
    winText.setCharacterSize(40);
    winText.setColor(sf::Color::Cyan);
    winText.setString("VICTORY");

    winDetails.setFont(f);
    winDetails.setCharacterSize(20);
    winDetails.setColor(sf::Color::White);

    sf::Clock timer2;
    window->create(sf::VideoMode(800, 600), "Mario");
    timer2.restart();
    //window->setFramerateLimit(60);
    while (!(hWnd = ::FindWindow(NULL, L"Mario")));

    float fps = 1.f / 60.f;
    float timeSinceLastUpdate = 0.f;

    while (window->isOpen())
    {
        if (gs == GameState::CLEAN)
        {
            if (ev.importFile != "") importFromFile(ev.importFile);
            checkEvents();
        }
        else
        {
            deltaTime = timer2.getElapsedTime().asMicroseconds()/1000.f;
            timer2.restart();
            timeSinceLastUpdate += deltaTime/1000;
            while (timeSinceLastUpdate >= fps)
            {
                deltaTime = fps*1000;
                sf::String s;
                s = std::to_string( 1/timeSinceLastUpdate );
                t.setString(s);
                checkInput();
                if (gs == GameState::PLAYING) update();
                timeSinceLastUpdate -= fps;
            }

        }

        drawing();
        //window->draw(t); FPS

        window->display();

        if (ev.cleanMap)
        {
            cleanMap();
            ev.cleanMap = false;
        }

    }
}




void World::checkInput()
{
    checkEvents();

    if (gs == GameState::PAUSED)
    {
        pauseText.setString("PRESS SPACE TO BEGIN");
        pauseText.setPosition(800/3, 600/2);
        sf::View v = window->getView();
        v.setCenter(400,300);
        window->setView(v);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            gs = GameState::PLAYING;
            hasFocus = true;
            timer.restart();
        }
    }
    else if (hasFocus) //tole komenti ce pavza nebo delala
    {
        bool l = false, r = false;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){    player->movement(Direction::LEFT, deltaTime); l = true;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){    player->movement(Direction::RIGHT, deltaTime); r = true;}
        if ((l && r) || (!l && !r)) player->movement(Direction::NONE, deltaTime);//čudn
        if (player->getStandingTile() != NULL) if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player->jump();

        sf::Vector2i mp = sf::Mouse::getPosition(*window);
        mp.x += camera->getPosition().x;
        mp.y += camera->getPosition().y;

        //EDITOR FUKCIJE
        if (ev.buffer != NULL)
        {
            ev.buffer->setPosition((mp.x/50)*50, (mp.y/50)*50);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!tools.isLeftMouseDown)
                {
                    tools.isLeftMouseDown = true;
                    tiles.push_back(ev.buffer);
                    ev.counter--;
                    if (ev.counter > 0)
                    {
                        Entity* be;
                        switch (ev.bufferType)
                        {
                            case EntityType::TILE: be = new Entity(tm->getTexture(ev.buffer->getTextureName()), ev.buffer->getTextureName(), -50, -50); break;
                            case EntityType::COIN: be = new Coin(tm->getTexture(ev.buffer->getTextureName()), ev.buffer->getTextureName(), -50, -50, ev.buffer->getScoreValue());break;
                            default: cout << "WARNING EVBUFFERTYPE UNDEFINED!" << endl; break;
                        }


                        ev.buffer = be;
                    }
                    else
                    {
                        ev.buffer = NULL;
                    }

                }
            }
            else tools.isLeftMouseDown = false;
        }

        if (ev.eBuffer != NULL)
        {
            if (ev.eBufferCount == 0)ev.eBuffer->setPosition((mp.x/50)*50, (mp.y/50)*50);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!tools.isLeftMouseDown)
                {
                    tools.isLeftMouseDown = true;
                    if (ev.eBufferCount == 0)
                    {
                        sf::Vector2f pos = sf::Vector2f((mp.x/50)*50, (mp.y/50)*50);
                        ev.eBuffer->setPosition(pos);
                        ev.eBuffer->setSpawnPoint(pos);
                        ev.eBufferCount++;
                    }
                    else if (ev.eBufferCount == 1)
                    {
                        int p = (mp.x/50)*50 - ev.eBuffer->getPosition().x;
                        ev.eBuffer->setPatrolLength(p);
                       // if (p < 0) ev.eBuffer->changeDirection();
                        enemies.push_back(ev.eBuffer);
                        ev.eBuffer = NULL;
                        ev.eBufferCount = 0;
                    }
                }
            }
            else tools.isLeftMouseDown = false;
        }

        if (ev.exitBuffer != NULL)
        {
            ev.exitBuffer->setPosition((mp.x/50)*50, (mp.y/50)*50);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!tools.isLeftMouseDown)
                {
                    tools.isLeftMouseDown = true;
                    exits.push_back(ev.exitBuffer);
                    ev.exitBuffer = NULL;
                }
            }
            else tools.isLeftMouseDown = false;
        }

        if (ev.selectionMode)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (!tools.isLeftMouseDown)
                {
                    tools.isLeftMouseDown = true;
                    bool s = false; //selected
                    for (unsigned int i = 0; i < tiles.size(); i++)
                    {
                        if (mp.x > tiles[i]->getPosition().x && mp.x < tiles[i]->getPosition().x + tiles[i]->getTexture()->getSize().x &&
                            mp.y > tiles[i]->getPosition().y && mp.y < tiles[i]->getPosition().y + tiles[i]->getTexture()->getSize().y)
                        {
                            ev.selection = tiles[i];
                            cout << "Entity Selected!" << endl;
                            s = true;
                            break;
                        }
                    }
                    for (unsigned int i = 0; i < enemies.size(); i++)
                    {
                        if (mp.x > enemies[i]->getPosition().x && mp.x < enemies[i]->getPosition().x + enemies[i]->getTexture()->getSize().x &&
                            mp.y > enemies[i]->getPosition().y && mp.y < enemies[i]->getPosition().y + enemies[i]->getTexture()->getSize().y)
                        {
                            ev.selection = enemies[i];
                            cout << "Enemy Selected!" << endl;
                            s = true;
                            break;
                        }
                    }
                    for (unsigned int i = 0; i < exits.size(); i++)
                    {
                        if (mp.x > exits[i]->getPosition().x && mp.x < exits[i]->getPosition().x + exits[i]->getTexture()->getSize().x &&
                            mp.y > exits[i]->getPosition().y && mp.y < exits[i]->getPosition().y + exits[i]->getTexture()->getSize().y)
                        {
                            ev.selection = exits[i];
                            cout << "Exit Selected!" << endl;
                            s = true;
                            break;
                        }
                    }
                    if (mp.x > player->getPosition().x && mp.x < player->getPosition().x + player->getTexture()->getSize().x &&
                        mp.y > player->getPosition().y && mp.y < player->getPosition().y + player->getTexture()->getSize().y)
                    {
                        ev.selection = player;
                        cout << "Player Selected!" << endl;
                        s = true;
                    }
                    if (!s)
                    {
                        cout << "Entity  Deselected!" << endl;
                        ev.selection = NULL;
                        ev.selectionPointer = NULL;
                    }
                }
            }
            else tools.isLeftMouseDown = false;
        }
        if (tools.mapWidth != 0)
        {
            camera->setLimitRight(tools.mapWidth);
            tools.mapWidth = 0;
        }
    }


}

void World::checkEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::LostFocus)
            hasFocus = false;
        else if (event.type == sf::Event::GainedFocus)
            hasFocus = true;
    }
}

void World::update()
{
    player->update(deltaTime);
    for (unsigned i = 0; i < enemies.size(); i++) enemies[i]->movement(deltaTime);
    for (unsigned i = 0; i < enemies.size(); i++) enemies[i]->update(deltaTime);
    cm->collision(*player, tiles, deltaTime);
    for (unsigned i = 0; i < enemies.size(); i++) cm->collision(*enemies[i], tiles, deltaTime);
    cm->collision(*player, enemies, deltaTime, gs);
    cm->collision(*player, exits, gs);
    camera->update();
    if (player->isDead()) gs = GameState::LOST;
}

void World::drawing()
{//cout << "LOOOOOP";
    window->clear(sf::Color::Black);
    if (gs == GameState::PLAYING)
    {
        //cout << tiles.size() << endl;
        for (Entity* e: tiles)
        {
            window->draw(*e);
        }
        for (unsigned int i = 0; i < enemies.size(); i++) window->draw(*enemies[i]);
        for (unsigned int i = 0; i < exits.size(); i++) window->draw(*exits[i]);
        window->draw(*player);
        //EDITOR BUFFER
        if (ev.buffer != NULL) window->draw(*ev.buffer);
        if (ev.eBuffer != NULL) window->draw(*ev.eBuffer);
        if (ev.exitBuffer != NULL) window->draw(*ev.exitBuffer);
        if (ev.drawGridLines) drawGridLines();
        if (ev.selectionMode && ev.selection != NULL) drawSelectionLines();

        //IN-GAME UI
        t.setCharacterSize(20);
        std::string  life = "Lives: " + QString::number(player->getHealth()).toStdString();
        t.setString(life);
        t.setPosition(camera->getPosition().x+20, camera->getPosition().y+10);
        window->draw(t);
        std::string  score = "Score: " + QString::number(player->getScore()).toStdString();
        t.setString(score);
        t.setPosition(camera->getPosition().x+20, camera->getPosition().y+50);

        if (timeLimit > 0)
        {
            remainingTime = timeLimit - timer.getElapsedTime().asSeconds();
            std::string tt = QString::number(remainingTime).toStdString();
            timerText.setString(tt);
            timerText.setPosition(camera->getPosition().x+600, camera->getPosition().y+20);
            if (remainingTime < 1)
            {
                gs = GameState::LOST;
            }
            window->draw(timerText);
        }
        //TEXT
        window->draw(t);

        //KONEC IN-GAME UI
    }
    else if (gs == GameState::LOST)
    {
        gameOverText.setPosition(camera->getPosition().x+800/2-160, 200);
        window->draw(gameOverText);
    }
    else if (gs == GameState::WON)
    {
        winText.setPosition(camera->getPosition().x+800/2-110, 200);

        winDetails.setPosition(camera->getPosition().x + 800/2 -100, 300);
        std::string s = "Score: " + QString::number(player->getScore()).toStdString();
        s += "\n";
        if (timeLimit != 0) s += "Remaining time: " + QString::number(remainingTime).toStdString();

        winDetails.setString(s);

        window->draw(winText);
        window->draw(winDetails);

        //EXPORT
        if (!scoreExported && timeLimit != 0)
        {
            std::ofstream myfile;
            myfile.open ("scores.txt", std::ios::app);
            myfile << player->getScore();
            myfile << " " << remainingTime << " " << ev.playerName << "\n";
            myfile.close();
            scoreExported = true;
        }

    }
    else if (gs == GameState::PAUSED) window->draw(pauseText);


}


void World::addTile(QString tex, int x, int y)
{
    Entity* e = new Entity(tm->getTexture(tex), tex, x, y);
    tiles.push_back(e);
    cout << "World: Postavljam tile " << tex.toStdString() << " na pozicijo " << x << " " << y << endl;
}

void World::addEnemy(QString tex, int x, int y, int pLength)
{
    Enemy* e = new Enemy(tm->getTexture(tex), tex, sf::Vector2f(x, y), pLength);
    enemies.push_back(e);
}

void World::addExit(QString tex, int x, int y, QString winMsg, QString nextMap)
{
    Exit* e = new Exit(tm->getTexture(tex), tex, x, y, winMsg, nextMap);
    exits.push_back(e);
}

void World::addCoin(QString tex, int x, int y, int score)
{
    Entity* c = new Coin(tm->getTexture(tex), tex, x, y, score);
    c->setCollision(false);
    tiles.push_back(c);
}


void World::drawGridLines()
{
    for (unsigned int i = 50; i < camera->getPosition().x+800; i += 50)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(i, 0)),
            sf::Vertex(sf::Vector2f(i, 600))
        };

        window->draw(line, 2, sf::Lines);
    }

    for (unsigned int i = 50; i < camera->getPosition().y+600; i += 50)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, i)),
            sf::Vertex(sf::Vector2f(800+camera->getPosition().x, i))
        };

        window->draw(line, 2, sf::Lines);
    }
}

void World::drawSelectionLines()
{

    sf::Vector2f sPos = ev.selection->getPosition();
    sf::Vector2u sSize = ev.selection->getTexture()->getSize();

    float s = 3;

    sf::RectangleShape selectionBox[4];

    if (ev.selectionDrawMode == 0) //METODA 1
    {
        selectionBox[0].setPosition(sPos);
        selectionBox[0].setSize(sf::Vector2f(sSize.x, s));

        selectionBox[1].setPosition(sPos.x + sSize.x - s, sPos.y);
        selectionBox[1].setSize(sf::Vector2f(s, sSize.y));

        selectionBox[2].setPosition(sPos.x, sPos.y + sSize.y - s);
        selectionBox[2].setSize(sf::Vector2f(sSize.x, s));

        selectionBox[3].setPosition(sPos);
        selectionBox[3].setSize(sf::Vector2f(s, sSize.y));
    }
    else if (ev.selectionDrawMode == 1) //METODA 2
    {
        selectionBox[0].setPosition(sPos.x - s, sPos.y - s);
        selectionBox[0].setSize(sf::Vector2f(sSize.x + s, s));

        selectionBox[1].setPosition(sPos.x + sSize.x, sPos.y - s);
        selectionBox[1].setSize(sf::Vector2f(s, sSize.y + s));

        selectionBox[2].setPosition(sPos.x, sPos.y + sSize.y);
        selectionBox[2].setSize(sf::Vector2f(sSize.x + s, s));

        selectionBox[3].setPosition(sPos.x - s, sPos.y);
        selectionBox[3].setSize(sf::Vector2f(s, sSize.y + s));
    }


    //window->draw(line, 5, sf::LinesStrip);
    for (unsigned i = 0; i < 4; i++)
    {
        selectionBox[i].setFillColor(sf::Color::Red);
        window->draw(selectionBox[i]);
    }
}

void World::defaultValues()
{
    //EDITOR VARIABLES
    ev.buffer = NULL;
    ev.eBuffer = NULL;
    ev.exitBuffer = NULL;
    ev.bufferType = EntityType::TILE;
    ev.eBufferCount = 0;
    ev.counter = 0;
    ev.drawGridLines = false;
    hasFocus = true;
    ev.selection = NULL;
    ev.selectionMode = false;
    ev.importFile = "";
    //tools.mapWidth = 0;
    tools.addTileMouseTimer.restart();
    tools.isLeftMouseDown = false;
    standingTile = NULL;
    ev.cleanMap = false;

    //TIMER
    //timeLimit = 30; //s

    //SCORES
    scoreExported = false;
}

//EDITOR FUNKCIJE

void World::setAddTile(QString tex, int count)
{
    unsetAddEnemy();
    unsetAddExit();
    if (ev.buffer != NULL) cout << "Buffer already set!" << endl;
    else
    {
        ev.counter = count;
        ev.buffer = new Entity(tm->getTexture(tex), tex, -50,0);
        ev.bufferType = EntityType::TILE;
    }
    if (!hasFocus && hWnd) SetForegroundWindow(hWnd);
}

void World::unsetAddTile()
{
    if (ev.buffer != NULL)
    {
        delete ev.buffer;
        ev.buffer = NULL;
        cout << "Buffer cleared!" << endl;
    }
    else
    {
        cout << "Buffer was not set!" << endl;
    }
}

void World::setAddEnemy(QString tex)
{
    unsetAddTile();
    unsetAddExit();
    if (ev.eBuffer != NULL) cout << "Enemy buffer already set!" << endl;
    else
    {
        ev.eBuffer = new Enemy(tm->getTexture(tex), tex, sf::Vector2f(-50.f, -50.f), 0);
    }
    if (!hasFocus && hWnd) SetForegroundWindow(hWnd);
}

void World::unsetAddEnemy()
{
    if (ev.eBuffer != NULL)
    {
        ev.eBufferCount = 0;
        delete ev.eBuffer;
        ev.eBuffer = NULL;
        cout << "Enemy buffer cleared!" << endl;
    }
    else
    {
        cout << "Buffer was not set!" << endl;
    }
}

void World::setAddExit(QString tex, QString nextLevel)
{
    unsetAddTile();
    unsetAddEnemy();
    if (ev.exitBuffer != NULL) cout << "Exit buffer already set!" << endl;
    else
    {
        ev.exitBuffer = new Exit(tm->getTexture(tex), tex, -50, -50, "YOU WON!", nextLevel);
        cout << "QWEQWEQW" << endl;
    }
    if (!hasFocus && hWnd) SetForegroundWindow(hWnd);
}

void World::unsetAddExit()
{
    if (ev.exitBuffer != NULL)
    {
        delete ev.exitBuffer;
        ev.exitBuffer = NULL;
        cout << "Exit buffer cleared!" << endl;
    }
    else
    {
        cout << "Exit buffer was not set!" << endl;
    }
}

void World::setAddCoin(QString tex, int count, int score)
{
    unsetAddEnemy();
    unsetAddExit();
    if (ev.buffer != NULL) cout << "Coin buffer already set!" << endl;
    else
    {
        ev.counter = count;
        ev.buffer = new Coin(tm->getTexture(tex), tex, -50,-50, score);
        ev.bufferType = EntityType::COIN;
    }
    if (!hasFocus && hWnd) SetForegroundWindow(hWnd);
}


void World::toggleGridLines()
{
    if (ev.drawGridLines) ev.drawGridLines = false;
    else ev.drawGridLines = true;
}

void World::setSelectionMode(bool b, int drawMode)
{
    if (!b) ev.selection = NULL;
    ev.selectionMode = b;
    ev.selectionDrawMode = drawMode;
}

sf::Vector2f World::getSelectedEntityPosition()
{
    if (ev.selection == NULL) return sf::Vector2f(0, 0);
    else return ev.selection->getPosition();
}

void World::deleteSelectedEntity()
{
    if (ev.selection != NULL)
    {
        for (unsigned i = 0; i < tiles.size(); i++)
        {
            if (tiles[i] == ev.selection)
            {
                delete tiles[i];
                tiles.erase(tiles.begin() + i);
                break;
            }
        }
        for (unsigned i = 0; i < enemies.size(); i++)
        {
            if (enemies[i] == ev.selection)
            {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                break;
            }
        }
        for (unsigned i = 0; i < exits.size(); i++)
        {
            if (exits[i] == ev.selection)
            {
                delete exits[i];
                exits.erase(exits.begin() + i);
                break;
            }
        }
        ev.selection = NULL;
    }
    else cout << "Warning: Nothing selected!" << endl;
}

void World::setEntityPosition(sf::Vector2f pos)
{
    if (ev.selection != NULL) ev.selection->setPosition(pos);
    EntityType tmp = ev.selection->getEntityType();
    if (tmp == EntityType::PLAYER || tmp == EntityType::ENEMY)
    {
        ev.selection->clearStandingTile();
    }
}

void World::setMapWidth(int w)
{
    tools.mapWidth = w;
}

int World::getMapWidth()
{
    return camera->getMapWidth();
}

//1-Entity, 2-Enemy, 3-Exit, 4-Coins 0-Player
void World::exportToFile(std::string f)
{
    std::ofstream myfile ("res\\maps\\"+f);
    if (myfile.is_open())
    {
        myfile << "0 " << player->getSpawnPoint().x << " " << player->getSpawnPoint().y << " " << camera->getMapWidth() << endl;
        for (unsigned int i = 0; i < tiles.size(); i++)
        {
            std::string tempType = "";
            std::string score = "";
            switch (tiles[i]->getEntityType())
            {
                case EntityType::TILE: tempType = "1"; break;
                case EntityType::COIN: tempType = "4"; score = " " + QString::number(tiles[i]->getScoreValue()).toStdString(); break;
                default: tempType = "1"; break;
            }



            myfile << tempType << " " << tiles[i]->getTextureName().toStdString() << " " <<  tiles[i]->getPosition().x << " " << tiles[i]->getPosition().y << score << endl;
        }
        for (unsigned int i = 0; i < enemies.size(); i++)
        {
            myfile << "2" << " " << enemies[i]->getTextureName().toStdString() << " " << enemies[i]->getSpawnPoint().x << " " << enemies[i]->getSpawnPoint().y << " " << enemies[i]->getPatrolLength() << endl;
        }
        for (unsigned int i = 0; i < exits.size(); i++)
        {
            myfile << "3" << " " << exits[i]->getTextureName().toStdString() << " " << exits[i]->getPosition().x << " " << exits[i]->getPosition().y << " " << exits[i]->getNextMap().toStdString() << endl;
        }
        myfile.close();
        cout << "Export Successful!" << endl;
    }
    else cout << "Unable to export map!";
}

void World::setImportFile(std::string f, std::string playerName, int timeLimit)
{
    ev.importFile = f;
    ev.playerName = playerName;
    this->timeLimit = timeLimit;
}

void World::setCleanMap()
{
    ev.cleanMap = true;
}


void World::importFromFile(std::string f)
{
    tiles.reserve(1000);
    string line, nextMap;
    int x, y, patrol;
    int t;
    std::ifstream myfile ("res\\maps\\"+f);
    if (myfile.is_open())
    {
        while (myfile >> t)
        {
            switch (t)
            {
                case 0: myfile >> x >> y >> t;  player = new Player(tm->getTexture("mario_left.png"), tm->getTexture("mario_right.png"), "left", "right", sf::Vector2f((float)x, (float)y)); tools.mapWidth = t; break;
                case 1: myfile >> line >> x >> y; addTile(QString::fromStdString(line), x, y); break;
                case 2: myfile >> line >> x >> y >> patrol; addEnemy(QString::fromStdString(line), x, y, patrol); break;
                case 3: myfile >> line >> x >> y >> nextMap; addExit(QString::fromStdString(line), x, y, "YEY YOU WON!!!", QString::fromStdString(nextMap)); break;
                case 4: myfile >> line >> x >> y >> t; addCoin(QString::fromStdString(line), x, y, t); break;
                default: cout << "ERROR" << endl;
            }
            cout << "IMPORTING... " << t << endl;
        }
        myfile.close();
        cout << "1..." << endl;
        camera = new Camera(window, player);
        cout << "2..." << endl;
        gs = GameState::PAUSED;
        cout << "3..." << endl;
        defaultValues();
        cout << "4..." << endl;
        window->setSize(sf::Vector2u(800,600));
        hasFocus = false;
    }
    else cout << "IMPORT ERROR!" << endl;

    /*addEnemy("enemy_rakec.png", 200, 300, 200);
    addExit("exit_symbol.png", 300, 300, "YOU WON", "qwe");*/
}



void World::cleanMap()
{
    for (unsigned int i = 0; i < tiles.size(); i++)
    {
        delete tiles[i];
    }
    for (unsigned int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i];
    }
    for (unsigned int i = 0; i < exits.size(); i++)
    {
        delete exits[i];
    }
    tiles.clear();
    enemies.clear();
    exits.clear();
    delete player;
    delete camera;
    //window->setSize(sf::Vector2u(100,100));
    gs = GameState::CLEAN;
}


