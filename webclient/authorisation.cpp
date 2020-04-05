/**
 * @file authorisation.cpp
 * @brief authorisation
 * @author Bagrova Polina
 */
#include "authorisation.h"
#include "ui_authorisation.h"
#include <QMessageBox>

Authorisation::Authorisation(QWidget *parent) :
    QDialog(parent), ui(new Ui::Authorisation)
{
    ui->setupUi(this);
    connect(ui->ok, &QPushButton::clicked,
            this, &Authorisation::pushOk);
}

Authorisation::~Authorisation()
{
    delete ui;
}

void Authorisation::pushOk(){
    if(ui->nick->displayText() == "" || ui->nick->displayText() == " "){
        QMessageBox::information(NULL,QObject::tr("Ошибка"), tr("Введите никнейм!"));
        return;
    }
    nick = ui->nick->displayText();
    this->close();
    emit sendNick(ui->nick->displayText());
}

QString Authorisation::getNick(){
    return nick;
}

quint16 Authorisation::getPort()
{
    quint16 port = 1337;
    if (ui->port->displayText() == "")
        return port;
    else
        return ui->port->displayText().toUInt();
}
