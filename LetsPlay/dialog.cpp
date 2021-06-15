#include "dialog.h"
#include "ui_dialog.h"

#include <QJsonObject>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QJsonObject obj;

    obj["GameMode"] = ui->gameMode->value();

    game = new Game(obj, ui->nPlayers->value(), ui->maxGoals->value());
    game->show();

    this->close();
}
