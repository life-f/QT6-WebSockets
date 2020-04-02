/**
 * @file mainwindow.h
 * @brief client
 * @author Bagrova Polina
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocket>
#include "authorisation.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QWebSocket *socketClient;
    QString nick = " ";
    Authorisation* dialog;

public:
    /**
     * @brief Client constructor
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
      * @brief Client destructor
      */
    ~MainWindow();

private slots:
    /**
     * @brief send messages
     */
    void execButtonAction();
    /**
     * @brief read Socket
     */
    void readSocket(QString message);
    /**
     * @brief connected
     */
    void connected();
    /**
     * @brief set nickname of user
     * @param nickname
     */
    void setNick(QString nickname);
    /**
     * @brief authorisation
     */
    void authorisation();
    /**
     * @brief server disconnected
     */
    void serverDisconnected();

signals:
    void auth();
};
#endif // MAINWINDOW_H
