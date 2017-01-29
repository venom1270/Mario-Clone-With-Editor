#include <iostream>
#include <QApplication>
#include "world.h"
#include "texturemanager.h"
#include "editor.h"
#include <thread>

using namespace std;

World* a;

void runEditor()
{

    TextureManager tm;
    tm.loadTextures();
    World game(&tm);
    a = &game;
    game.run();

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    /*thread editorThread(runEditor);
    editorThread.detach(); //more se končt pred koncem programa*/
    Editor editor;
    editor.show();
    app.exec();
    //
    return 0;
}

