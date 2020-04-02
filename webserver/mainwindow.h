/**
 * @file mainwindow.h
 * @brief server
 * @author Bagrova Polina
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebSocketServer>
#include <QSystemTrayIcon>
#include <QAction>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QIcon icon;
    QSystemTrayIcon* trayIcon;
    Server* server;

public:
    /**
     * @brief Constructor
     * @param parent
     */
    MainWindow(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     * @param parent
     */
    ~MainWindow();

private:
    /**
     * @brief set menu of tray
     */
    void setMenu();
    /**
     * @brief Send message for all users
     * @param message
     */
    void sender(QString message);

private slots:
    /**
     * @brief collapse to tray
     */
    void tray();
    /**
     * @brief Start or close server
     */
    void serverStart();
    /**
     * @brief change status of server
     */
    void changeStatus();
    /**
     * @brief iconActivated
     * @param reason
     */
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    /**
     * @brief getInfo
     * @param info
     */
    void getInfo(QString info);
    void setSettings();
};
#endif // MAINWINDOW_H
