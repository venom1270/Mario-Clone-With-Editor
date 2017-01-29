#include "texturemanager.h"
#include <QMapIterator>
#include <iostream>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
    QMapIterator<QString, sf::Texture*> i(textures);
    while (i.hasNext())
    {
        i.next();
        std::cout << "TextureManager: Brisem sliko " << i.key().toStdString() << std::endl;
        delete i.value();
    }
}

void TextureManager::loadTextures()
{
    QDir dir;
    dir.cd("res\\textures");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    std::cout << dir.currentPath().toStdString();
    sf::Texture* t;

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        t = new sf::Texture();
        if (t->loadFromFile(fileInfo.filePath().toStdString()))
        {
            std::cout << "TextureManager: Slika " << fileInfo.filePath().toStdString() << " nalozena!\n";
            textures.insert(fileInfo.fileName(), t);
        }
        else delete t;
    }
}

sf::Texture* TextureManager::getTexture(QString texture)
{
    if (textures.contains(texture))
    {
        std::cout << "TextureManager: Vracam teksturo " << texture.toStdString() << std::endl;
        return textures.value(texture);
    }
    else
    {
        std::cout << "TextureManager: Vracam NULL za teksturo " << texture.toStdString() << std::endl;
        return NULL;
    }
}
