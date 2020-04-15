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
#include <QSqlDatabase>

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
    /**
     * @brief settings
     */
    QSettings *settings;
    /**
     * @brief database
     */
    QSqlDatabase db;

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
     * @brief getPort
     * @return port
     */
    QString getPort();
    /**
     * @brief getHost
     * @return host
     */
    QString getHost();

private:
    /**
     * @brief Send message for all users
     * @param message
     */
    void sender(QString message);
    /**
     * @brief connect database
     */
    void connectDatabase();
    /**
     * @brief record message
     * @param nick
     * @param message
     */
    void recordMessage(QString nick, QString message);

public slots:
    /**
     * @brief set settings for server
     * @param host
     * @param port
     */
    void setSettings(QString host, quint16 port);

private slots:
    /**
     * @brief read settings
     * @return port
     */
    quint16 readSettings();
    /**
     * @brief connect User
     */
    void connectUser();
    /**
     * @brief message from client
     */
    void runClientAction(QString message);
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
     * @brief information
     * @param info - message with information
     */
    void info(QString info);
};

#endif // SERVER_H
