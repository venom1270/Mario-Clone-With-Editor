#include "camera.h"

#include <iostream>

using std::cout;
using std::endl;


Camera::~Camera()
{
    cout << "DELETING CAMERA";
}

Camera::Camera(sf::RenderWindow *window, Player *player, int maxOffset)
{

    this->player = player;
    this->window = window;

    limitLeft = 0;
    limitRight = 2000;

    this->maxOffset = maxOffset;

    //camera.setSize(window->getSize().x, window->getSize().y);

    camera = window->getView();
    camera.setSize(800, 600);
    camera.setCenter(400, 300);
    //camera.zoom(2);

    // EPIC DEBUG UTILITY
    /*cout << window->getView().getCenter().x << " " << window->getView().getCenter().y << endl;
    cout << window->getDefaultView().getCenter().x << " " << window->getDefaultView().getCenter().y << endl;
    cout << window->getSize().x << " " << window->getSize().y << endl;
    cout << camera.getCenter().x << " " << camera.getCenter().y << endl;*/

}

void Camera::update()
{
    //multiplier se ne obnese - mario začne lagirat
    //float velocityMultiplier = 1.5f;

    int x = camera.getCenter().x;
    int y = camera.getCenter().y;

    int sx = camera.getSize().x / 2;
    int sy = camera.getSize().y / 2;
/*
    cout << endl << "*****************" << endl;
    cout << x << " " << y << endl;
    cout << player->getPlayer().getPosition().x + maxOffset << endl;
*/

    if (player->getPosition().x + maxOffset < x && x-sx > limitLeft)
    {
        camera.setCenter(player->getPosition().x + maxOffset, sy);
    }
    if (player->getPosition().x + player->getTexture()->getSize().x - maxOffset > x && x+sx < limitRight)
    {
        camera.setCenter(player->getPosition().x + player->getTexture()->getSize().x - maxOffset, sy);
    }


    if (camera.getCenter().x - sx < 0) camera.setCenter(sx, y);

    //NOVO ZA ČE UMRE DA SE RECENTRIRA KAMERA --- FIX TO JE KRNEKI NEJ BO ZAKOMENTIRAN
   /* if (x - sx != 0) //TO NAJBRŽ SAM ZA LEVO STRAN DELA -- če kamera ni v začetni legi preverja če je mario 'ušel'
        if (player->getPosition().x > x + maxOffset || player->getPosition().x + player->getTexture()->getSize().x < x - maxOffset) //ali je mario preveč ušel
        {
            if (player->getPosition().x < limitRight)camera.setCenter(player->getPosition().x, y); // nanj repozicionira
            if (camera.getCenter().x - camera.getSize().x < 0)      //preverimo samo zato da je lepa tranzicija kot repozicijoniramo
            {
                camera.setCenter(400, 300); //y koordinata se lahko spremeni
            }//kasneje še if za desno stran
        }*/




    window->setView(camera);
}

sf::Vector2u Camera::getPosition()
{
    sf::Vector2u v;
    v.x = camera.getCenter().x - window->getSize().x/2;
    v.y = camera.getCenter().y - window->getSize().y/2;
    return v;
}

void Camera::setPosition(int x, int y)
{
    camera.setCenter(x+window->getSize().x/2, y+window->getSize().y/2);
}

void Camera::setLimitRight(int w)
{
    limitRight = w;
}

int Camera::getMapWidth()
{
    return limitRight;
}
