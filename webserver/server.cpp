/**
 * @file server.cpp
 * @brief server
 * @author Bagrova Polina
 */
#include "server.h"
#include <QtWebSockets>
#include <QDebug>
#include <QMessageBox>

Server::Server(QObject *parent) : QObject(parent),
    webServer (new QWebSocketServer(QStringLiteral("Chat Server"),
                                    QWebSocketServer::NonSecureMode,
                                    this))
{
//    readSettings();
    if (webServer->listen(QHostAddress::Any, readSettings())){
        qInfo() << webServer->serverUrl();
        qInfo() << "Server started";
        QMessageBox::information(NULL,QObject::tr("Информация"),tr("Server started"));

        connect (webServer, &QWebSocketServer::newConnection,
                 this, &Server::connectUser);
    } else {
        qWarning() << "Unable to start server";
        QMessageBox::information(NULL,QObject::tr("Информация"),tr("Unable to start server"));
    }
    clients.clear();
//    list.clear();
    QSettings settings("ORGANIZATION_NAME", "APPLICATION_NAME");
}

Server::~Server(){
    clients.clear();
    qInfo() << "Server close";
    emit info("Server close");
    webServer->close();
}

void Server::sender(QString message){
    foreach (client, clients) {
        QWebSocket* clientSock = (QWebSocket*) client;
        clientSock->sendTextMessage(message);
//      QTextStream str (clientSock);
//      str << message;
    }
}

void Server::setSettings(QString host, quint16 port)
{
    settings = new QSettings("/:setting.ini", QSettings::IniFormat);
    settings->beginGroup("Settings");
    settings->setValue( "host", host);
    settings->setValue("port", port);
    settings->endGroup();
    emit settingsChanged();
    QMessageBox::information(NULL,QObject::tr("Информация"),tr("Настройки сервера изменены. Перезапустите сервер"));
}

quint16 Server::readSettings()
{
    settings = new QSettings(":/setting.ini", QSettings::IniFormat);
    settings->beginGroup("Settings");
    QString host = settings->value("host").toString();
    quint16 port = settings->value("port").toUInt();
    settings->endGroup();
    return port;
}

void Server::connectUser()
{
    qInfo() << "We have new user!";
    emit info("We have new user!");
    client = webServer->nextPendingConnection();
    sender("1 new user");
//    foreach (client, clients) {
//        QWebSocket* clientSock = (QWebSocket*) client;
//        QTextStream str (clientSock);
//        str << " 1 new user";
//        }

//    client = tcpServer->nextPendingConnection();
    clients.push_back(client);
    this->send10Message();

//    connect(client, &QTcpSocket::readyRead,
//            this, &Server::runClientAction);
    connect(client, &QWebSocket::disconnected,
                this, &Server::disconnectUser);
}

void Server::runClientAction()
{
    k++;
//    QTcpSocket* clientSocket = (QTcpSocket*) sender();
//    QTextStream stream (clientSocket);
    QString nickname;
    QString message;
//    for (int i = 0;i < 2;i++){
//        if (i == 0) stream >> nickname;
//        if (i == 1) stream >> message;
//    }
    qInfo() << "Get message from "<< nickname << ": " << message;
    sender(nickname + ": " + message);
//    foreach (client, clients){
//        QTcpSocket* clSock = (QTcpSocket*) client;
//        QTextStream str (clSock);
//        str << nickname + ": " + message;
//    }

//    f.setFileName("file.txt");
//    list.push_back(nickname + " " + message);

//    if(!f.open(QIODevice::WriteOnly)){
//        qInfo() << "File isn't open.";
//    }

//    if (k > 10){
//        list.removeFirst();
//    }

//    QTextStream _stream(&f);
//    foreach(QString str, list){
//        if (str != ""){
//           _stream << str << endl;
//       }
//    }
//    f.close();
}

void Server::disconnectUser() {
    qInfo() << "We lost user!";
    emit info("We lost user!");
    sender("1 user left");
//    foreach (client, clients) {
//        QWebSocket* clientSock = (QWebSocket*) client;
//        QTextStream str (clientSock);
//        str << "    1 user left.";
//    }
    clients.removeOne(client);
    client->disconnect();
}

void Server::send10Message() {
//    f.setFileName("messages.txt");
//    if(!f.open(QIODevice::ReadOnly)){
//        qInfo() << "File isn't open.";
//    }

//    QTcpSocket* clSock = (QTcpSocket*) client;
//    QTextStream str (clSock);
//    QTextStream _stream(&f);
//    int i = 0;
//    while(!_stream.atEnd()){
//        QString st;
//        i++;
//        _stream >> st;
//        if (((i % 2) == 1)&&(st != ""))
//            str << st + ": ";
//        else {
//            str << st;
//            if(!_stream.atEnd())
//                str<<endl;
//        }
//    }
//    if(k == 0)
//        k += i/2;
//    f.close();
}
