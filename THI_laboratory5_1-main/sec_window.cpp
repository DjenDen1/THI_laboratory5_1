#include "sec_window.h"
#include "ui_sec_window.h"
#include <QMessageBox>

sec_window::sec_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::sec_window)
{
    ui->setupUi(this);

    setWindowModality(Qt::ApplicationModal);

    on_genreBox_currentTextChanged(ui->genreBox->currentText());
}

sec_window::~sec_window()
{
    delete ui;
}

void sec_window::on_genreBox_currentTextChanged(const QString &genre)
{
    if (genre == "Popsong") {
        ui->lblParam1->setText("Язык текста:");
        ui->lblParam2->setText("Тип вокала:");
    } else if (genre == "Electronic") {
        ui->lblParam1->setText("Инструмент:");
        ui->lblParam2->setText("Битрейт:");
    } else if (genre == "Symphony") {
        ui->lblParam1->setText("Главный инстр.:");
        ui->lblParam2->setText("Кол-во частей:");
    } else if (genre == "Opera") {
        ui->lblParam1->setText("Тип вокала:");
        ui->lblParam2->setText("Язык (не исп.):");
    }
}

void sec_window::on_btnConfirm_clicked()
{
    QString title = ui->titleEdit->text().trimmed();
    QString durationStr = ui->durationEdit->text().trimmed();
    QString p1 = ui->paramEdit1->text().trimmed();
    QString p2 = ui->paramEdit2->text().trimmed();


    if (title.isEmpty() || durationStr.isEmpty() || p1.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполните поля формы!");
        return;
    }

    int duration = durationStr.toInt();
    QString genre = ui->genreBox->currentText();
    TrackFactory* factory = nullptr;

    if (genre == "Electronic") {
        factory = new ElectronicTrackFactory(p1.toStdString(), p2.toInt());
    }
    else if (genre == "Symphony") {
        factory = new SymphonyFactory(p1.toStdString(), p2.toInt());
    }
    else if (genre == "Popsong") {
        factory = new PopsongFactory(p1.toStdString(), p2.toStdString());
    }
    else if (genre == "Opera") {
        factory = new OperaFactory(p1.toStdString());
    }

    if (factory) {
        targetTrack = factory->CreateTrack(title.toStdString(), duration);
        delete factory;
    }

    this->close();
}


void sec_window::on_canConfirm_2_clicked()
{
    targetTrack = nullptr;
    this->close();
}

void sec_window::on_ggggggg_clicked()
{

}

