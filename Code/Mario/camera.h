#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "player.h"


//to je več al mjn sma prekopiran...loh je krneki
class Camera
{
    sf::View camera;
    int limitRight;
    int limitLeft;

    sf::RenderWindow* window;
    Player* player;

    int maxOffset; //za kok je od mariota kamera stran

public:
    ~Camera();
    Camera(sf::RenderWindow* window, Player* player, int maxOffset = 100);
    void update();
    sf::Vector2u getPosition();
    void setPosition(int x, int y);
    void setLimitRight(int w);
    int getMapWidth();
};

#endif // CAMERA_H
