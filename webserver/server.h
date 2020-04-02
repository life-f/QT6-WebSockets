/**
 * @file server.h
 * @brief server
 * @author Bagrova Polina
 */
#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QWebSocketServer>
#include <QSettings>

class Server : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief connecting
     */
    QWebSocketServer* webServer;
    /**
     * @brief connecting to the client
     */
    QWebSocket* client;
    /**
     * @brief list of clients
     */
    QList <QWebSocket*> clients;
    QSettings *settings;

//    QFile f;
//    QStringList list;
    int k = 0;

public:
    /**
     * @brief Server Constructor
     * @param parent
     */
    explicit Server(QObject *parent = nullptr);
    /**
      * @brief Server destructor
      */
    ~Server();
    /**
     * @brief Send message for all users
     * @param message
     */
    void sender(QString message);

public slots:
    void setSettings(QString host, quint16 port);

private slots:
    quint16 readSettings();
    /**
     * @brief connect User
     */
    void connectUser();
    /**
     * @brief message from client
     */
    void runClientAction();
    /**
     * @brief disconnect User
     */
    void disconnectUser();
    /**
     * @brief send 10 messages for new user
     */
    void send10Message();

signals:
    /**
     * @brief server close
     */
//    void serverDisconnected();
    /**
     * @brief information
     * @param info - message with information
     */
    void info(QString info);
    void settingsChanged();

};

#endif // SERVER_H
