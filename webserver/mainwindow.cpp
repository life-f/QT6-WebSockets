/**
 * @file mainwindow.cpp
 * @brief server
 * @author Bagrova Polina
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QtWebSockets>
#include <QDebug>
//#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Server");
    icon.addFile(":/images/icon.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Tray Program" "\n"
                         "Работа со сворачиванием программы трей");
    setMenu();
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(ui->status, &QComboBox::currentTextChanged,
            this, &MainWindow::serverStart);
    connect(ui->tray, &QPushButton::clicked, this, &MainWindow::tray);
    connect(ui->settings, &QPushButton::clicked, this, &MainWindow::setSettings);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tray()
{
    if(this->isVisible()){
        this->hide();
        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
        trayIcon->showMessage("Tray Program",
                              "Приложение свернуто в трей. Для того чтобы, развернуть окно приложения, щелкните по иконке приложения в трее",
                              icon, 2000);
    }
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:
        if(!this->isVisible()){
            this->show();
        } else {
            this->hide();
        }
        break;
    default:
        break;
    }
}

void MainWindow::setMenu(){
    QMenu* menu = new QMenu(this);
    QAction* viewWin = new QAction("Развернуть окно", this);
    connect(viewWin, SIGNAL(triggered()), this, SLOT(show()));
    QAction* start = new QAction("Запустить сервер", this);
    connect(start, &QAction::triggered, this, &MainWindow::changeStatus);
    QAction* closeServ = new QAction("Закрыть сервер", this);
    connect(closeServ, &QAction::triggered, this, &MainWindow::changeStatus);
    QAction* quitWin = new QAction("Выход", this);
    connect(quitWin, &QAction::triggered, this, &MainWindow::close);
    menu->addAction(viewWin);
    menu->addAction(start);
    menu->addAction(closeServ);
    menu->addAction(quitWin);
    trayIcon->setContextMenu(menu);
}

void MainWindow::serverStart(){
    if (ui->status->currentText() == "ON"){
        server = new Server();
        connect(server, &Server::info, this, &MainWindow::getInfo);
    } else {
        delete server;
    }
}

void MainWindow::changeStatus(){
    if(ui->status->currentText() == "ON"){
        ui->status->setCurrentIndex(0);
    } else{
        ui->status->setCurrentIndex(1);
    }
}

void MainWindow::getInfo(QString info){
    ui->textEdit->append(info);
}

void MainWindow::setSettings()
{
    server->setSettings(ui->port->displayText(), ui->host->displayText().toUInt());
}