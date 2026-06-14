#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sec_window.h"
#include <QMessageBox>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    refreshInterface();
}

MainWindow::~MainWindow()
{
    for (auto track : myTracks) {
        delete track;
    }
    delete ui;
}

void MainWindow::refreshInterface()
{
    ui->trackListWidget->clear();
    int totalDuration = 0;

    for (auto track : myTracks) {
        if (!track) continue;

        QString itemText = QString::fromStdString(track->Inctroduce() + " | " + track->technical_intro());
        ui->trackListWidget->addItem(itemText);

        totalDuration += track->getDuration();
    }

    ui->totalDurationLabel->setText("Общее время диска: " + QString::number(totalDuration) + " сек.");
}

void MainWindow::on_addButton_clicked()
{
    sec_window *secWin = new sec_window(this);


    connect(secWin, &QObject::destroyed, this, [this, secWin]() {
        MUSIC_COMPOSITION* track = secWin->getCreatedTrack();
        if (track) {
            myTracks.push_back(track);
            refreshInterface();
        }
    });

    secWin->setAttribute(Qt::WA_DeleteOnClose);
    secWin->show();
}

void MainWindow::on_deleteButton_clicked()
{
    int selectedRow = ui->trackListWidget->currentRow();

    if (selectedRow < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите трек для удаления!");
        return;
    }

    delete myTracks[selectedRow];
    myTracks.erase(myTracks.begin() + selectedRow);

    refreshInterface();
}

void MainWindow::on_addTrackButton_clicked()
{

    sec_window *secWin = new sec_window(this);


    connect(secWin, &QObject::destroyed, this, [this, secWin]() {
        MUSIC_COMPOSITION* track = secWin->getCreatedTrack();
        if (track) {
            myTracks.push_back(track);
            refreshInterface();
        }
    });

    secWin->setAttribute(Qt::WA_DeleteOnClose);
    secWin->show();
}


void MainWindow::on_editButton_clicked()
{
    int selectedRow = ui->trackListWidget->currentRow();
    std::string newTitle = ui->paramEdit1_main->text().trimmed().toStdString();
    QString durationStr = ui->paramEdit2_main->text().trimmed();


    myTracks[selectedRow]->setDuration(durationStr.toInt());
    myTracks[selectedRow]->setTitle(newTitle);

    refreshInterface();


}

