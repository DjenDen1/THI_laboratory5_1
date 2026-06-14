#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "music_lib3.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();

    void on_addTrackButton_clicked();

    void on_editButton_clicked();

private:
    Ui::MainWindow *ui;

    std::vector<MUSIC_COMPOSITION*> myTracks;

    void refreshInterface();
};

#endif // MAINWINDOW_H
