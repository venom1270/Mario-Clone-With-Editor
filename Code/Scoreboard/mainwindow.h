#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
using std::string;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    struct Field
    {
        string name;
        int score;
        int time;
    } s;

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
     static bool sortScores(const Field &a, const Field &b);
public slots:
    void refreshScores();


};

#endif // MAINWINDOW_H
