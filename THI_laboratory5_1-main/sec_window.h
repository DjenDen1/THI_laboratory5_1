#pragma once

#include <QMainWindow>
#include "music_lib3.h"
#include "trackfactorymethod.h"

namespace Ui {
class sec_window;
}

class sec_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit sec_window(QWidget *parent = nullptr);
    ~sec_window();

    // Простой геттер, чтобы MainWindow мог забрать созданный трек
    MUSIC_COMPOSITION* getCreatedTrack() { return targetTrack; }

private slots:
    void on_genreBox_currentTextChanged(const QString &genre);
    void on_btnConfirm_clicked();     // Твоя кнопка CONFIRM
    void on_canConfirm_2_clicked();   // Твоя кнопка CANCEL

    void on_ggggggg_clicked();

private:
    Ui::sec_window *ui;
    MUSIC_COMPOSITION* targetTrack = nullptr; // Сюда сохраним результат работы фабрики
};
