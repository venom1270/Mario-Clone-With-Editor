#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <string>
#include <vector>
#include <QTimer>

using std::string;
using std::vector;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer::singleShot(1000,this,SLOT(refreshScores()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshScores()
{

    vector<Field> scores;


    std::ifstream myfile ("scores.txt");
    if (myfile.is_open())
    {
        while (myfile >> s.score >> s.time >> s.name)
        {
            scores.push_back(s);
        }
        myfile.close();

        std::sort(scores.begin(), scores.end(), *sortScores);

        QString outputs[15];
        int i = 0;
        for (i = 0; i < scores.size() && i < 15; i++)
        {
            outputs[i] = QString::fromUtf8(scores[i].name.c_str()) + " | Rezultat: " + QString::number(scores[i].score) + " | Preostali čas: " + QString::number(scores[i].time);
        }
        for (;i < 15;i++)
        {
            outputs[i] = "Kekec";
        }

        ui->lFirst->setText(outputs[0]);
        ui->lSecond->setText(outputs[1]);
        ui->lThird->setText(outputs[2]);
        ui->lFour->setText(outputs[3]);
        ui->lFive->setText(outputs[4]);
        ui->lSix->setText(outputs[5]);
        ui->lSeven->setText(outputs[6]);
        ui->lEight->setText(outputs[7]);
        ui->lNine->setText(outputs[8]);
        ui->lTen->setText(outputs[9]);
        ui->lEleven->setText(outputs[10]);
        ui->lTwelve->setText(outputs[11]);
        ui->lThirteen->setText(outputs[12]);
        ui->lFourteen->setText(outputs[13]);
        ui->lFifteen->setText(outputs[14]);
    }

    QTimer::singleShot(1000,this,SLOT(refreshScores()));

}

bool MainWindow::sortScores(const MainWindow::Field &a, const MainWindow::Field &b)
{
    if (a.score == b.score)
    {
        return a.time < b.time;
    }
    else
        return a.score > b.score;
}

void MainWindow::on_pushButton_clicked()
{
    refreshScores();
}
