#include "editor.h"
#include "ui_editor.h"
#include <thread>
#include <iostream>

Editor::Editor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
    //world = &w;
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(getEntityData()));
    timerFrequency = 100;
    lastMap = "";

    std::thread editorThread(&Editor::tred, this);
    editorThread.detach();

}

void Editor::tred()
{
    TextureManager tm;
    tm.loadTextures();
    World game(&tm);
    world = &game;
    game.run();
}

void Editor::loadMap(std::string name)
{
    std::string pName = ui->tbPlayerName->text().toStdString();
    if (pName != "")
    {
        std::cout << "LOADING MAP\n";
        world->setImportFile(name, pName, ui->sbTimeLimit->value()); //kasneje mogoce struktura za razlicne opcije
    }
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_bTest_clicked()
{
    if (ui->lwTextureList->selectedItems().count() > 0)
    {
        QString t = ui->lwTextureList->currentItem()->text();
        world->setAddTile(t, ui->sbAddTileCounter->value());
    }
}

void Editor::on_bTextureListRefresh_clicked()
{
    ui->lwTextureList->clear();
    ui->lwEnemyList->clear();
    ui->lwExitList->clear();
    ui->lwCoinList->clear();

    QDir dir;
    dir.cd("res\\textures");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);


    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);

        if (fileInfo.fileName().contains("tile")) ui->lwTextureList->addItem(fileInfo.fileName());
        if (fileInfo.fileName().contains("enemy")) ui->lwEnemyList->addItem(fileInfo.fileName());
        if (fileInfo.fileName().contains("exit")) ui->lwExitList->addItem(fileInfo.fileName());
        if (fileInfo.fileName().contains("coin")) ui->lwCoinList->addItem(fileInfo.fileName());
    }
}

void Editor::on_bToggleGridLines_clicked()
{
    world->toggleGridLines();
}

void Editor::on_bClearTileBuffer_clicked()
{
    world->unsetAddTile();
    world->unsetAddEnemy();
    world->unsetAddExit();
}

void Editor::on_bEnableSelectionMode_clicked()
{
    world->setSelectionMode(true, int(ui->cbOutline->isChecked()));
    getEntityData();
    enableTimer(ui->cbRealTime->isChecked());
}

void Editor::on_bDisableSelectionMode_clicked()
{
    world->setSelectionMode(false, 0); // ta nula bi bla lohka default v paramwetrih.?
    if (timer->isActive()) timer->stop();
    ui->sbSelectedEntityPositionX->setValue(0);
    ui->sbSelectedEntityPositionY->setValue(0);
}

void Editor::getEntityData()
{
    sf::Vector2f pos = world->getSelectedEntityPosition();
    ui->sbSelectedEntityPositionX->setValue(pos.x);
    ui->sbSelectedEntityPositionY->setValue(pos.y);
}

void Editor::on_cbRealTime_toggled(bool checked)
{
    enableTimer(checked);
    enableApplyButtons(!checked);
}

void Editor::enableTimer(bool cbRTChecked)
{
    if (cbRTChecked && !timer->isActive()) timer->start(timerFrequency);
    else if (!cbRTChecked && timer->isActive()) timer->stop();
}

void Editor::enableApplyButtons(bool b)
{
    ui->bApplyPosition->setEnabled(b);
}

void Editor::on_bApplyPosition_clicked()
{
    sf::Vector2f p;
    p.x = ui->sbSelectedEntityPositionX->value();
    p.y = ui->sbSelectedEntityPositionY->value();
    world->setEntityPosition(p);
    //world->set
}

void Editor::on_bDeleteSelectedEntity_clicked()
{
    world->deleteSelectedEntity();
}

void Editor::on_bApplyMapWidth_clicked()
{
    world->setMapWidth(ui->MapWidth->value());
}

void Editor::on_bExport_clicked()
{
    if (lastMap != "")
    {
        std::string emap = ui->tbExportFileName->text().toStdString();
        if (emap != "")
            world->exportToFile(emap);
    }
}

void Editor::on_bImport_clicked()
{
    std::cout << lastMap.toStdString() << std::endl;
    if (lastMap == "" && ui->tbPlayerName->text().toStdString() != "")
    {
        lastMap = ui->cbImportFileName->currentText();
        if (lastMap != "")
            loadMap(lastMap.toStdString());
    }
}

void Editor::on_bCleanMap_clicked()
{
    if (lastMap != "")
    {
        world->setCleanMap();
        lastMap = "";
    }
}

void Editor::on_bRefreshImportFileList_clicked()
{
    ui->cbImportFileName->clear();
    QDir directory("res\\maps\\");
    QStringList txtFilesAndDirectories = directory.entryList();
    txtFilesAndDirectories.removeOne(".");
    txtFilesAndDirectories.removeOne("..");
    ui->cbImportFileName->addItems(txtFilesAndDirectories);
}

void Editor::on_pushButton_clicked()
{
    if (ui->lwEnemyList->selectedItems().count() > 0)
    {
        QString t = ui->lwEnemyList->currentItem()->text();
        world->setAddEnemy(t);
    }
}

void Editor::on_bAddExit_clicked()
{
    if (ui->lwExitList->selectedItems().count() > 0)
    {
        QString t = ui->lwExitList->currentItem()->text();
        world->setAddExit(t, ""); //2. parameter je next level - ni implementiran
    }
}

void Editor::on_bAddCoin_clicked()
{
    if (ui->lwCoinList->selectedItems().count() > 0)
    {
        QString t = ui->lwCoinList->currentItem()->text();
        world->setAddCoin(t, ui->sbAddCoinCounter->value(), ui->sbCoinScoreValue->value());
    }
}

void Editor::on_bRestartMap_clicked()
{
    if (lastMap != "" && ui->tbPlayerName->text().toStdString() != "")
    {
        world->setCleanMap();
       // world->setImportFile(lastMap.toStdString(), std::string playerName);
        loadMap(lastMap.toStdString());
    }
}
