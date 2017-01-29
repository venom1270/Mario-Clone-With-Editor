#ifndef EDITOR_H
#define EDITOR_H
#pragma once

#include <QWidget>
#include "world.h"
#include <QTimer>

namespace Ui {
class Editor;
}

class Editor : public QWidget
{
    Q_OBJECT
    
public:
    explicit Editor(QWidget *parent = 0);
    //explicit Editor(World& w, QWidget *parent = 0);
    ~Editor();
    
private slots:
    void on_bTest_clicked();

    void on_bTextureListRefresh_clicked();

    void on_bToggleGridLines_clicked();

    void on_bClearTileBuffer_clicked();

    void on_bEnableSelectionMode_clicked();

    void on_bDisableSelectionMode_clicked();

    void getEntityData();

    void on_cbRealTime_toggled(bool checked);

    void on_bApplyPosition_clicked();

    void on_bDeleteSelectedEntity_clicked();

    void on_bApplyMapWidth_clicked();

    void on_bExport_clicked();

    void on_bImport_clicked();

    void on_bCleanMap_clicked();

    void on_bRefreshImportFileList_clicked();

    void on_pushButton_clicked();

    void on_bAddExit_clicked();

    void on_bAddCoin_clicked();

    void on_bRestartMap_clicked();

private:
    Ui::Editor *ui;
    World* world;
    QTimer* timer;
    int timerFrequency;
    QString lastMap;

    void enableTimer(bool cbRTChecked);
    void enableApplyButtons(bool b);
    void tred();
    void loadMap(std::string name);
};

#endif // EDITOR_H
