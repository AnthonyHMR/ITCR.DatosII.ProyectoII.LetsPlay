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

    obj["Players"] = ui->nPlayers->text();
    obj["GameMode"] = ui->gameMode->text();

    game = new Game(obj);
    game->show(ui->gameMode->value());

    this->close();
}
