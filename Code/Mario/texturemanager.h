#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#pragma once

#include <QDir>
#include <QMap>
#include <vector>
#include <SFML/Graphics/Texture.hpp>

using std::vector;

class TextureManager
{
    QMap<QString, sf::Texture*> textures;
public:
    TextureManager();
    ~TextureManager();
    void loadTextures();
    sf::Texture* getTexture(QString texture);
};

#endif // TEXTUREMANAGER_H
