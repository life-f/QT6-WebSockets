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
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->hideEl();
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

void MainWindow::hideEl()
{
    ui->host->hide();
    ui->port->hide();
    ui->settings->hide();
    ui->label_port->hide();
    ui->label_host->hide();
}

void MainWindow::showEl()
{

    ui->host->show();
    ui->port->show();
    ui->settings->show();
    ui->label_host->show();
    ui->label_port->show();
}

void MainWindow::serverStart(){
    if (ui->status->currentText() == "ON"){
        server = new Server();
        connect(server, &Server::info, this, &MainWindow::getInfo);
        this->showEl();
        ui->host->setText(server->getHost());
        ui->port->setText(server->getPort());
    } else {
        delete server;
        this->hideEl();
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
    QString host;
    quint16 port;
    if(ui->host->displayText() == "")
        host = "127.0.0.1";
    else
        host = ui->host->displayText();
    if(ui->port->displayText() == "")
        port = 1337;
    else
        port = ui->port->displayText().toUInt();
    server->setSettings(host, port);
}
