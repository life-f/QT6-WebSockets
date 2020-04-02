/**
 * @file authorisation.h
 * @brief authorisation
 * @author Bagrova Polina
 */
#ifndef AUTHORISATION_H
#define AUTHORISATION_H

#include <QDialog>

namespace Ui {class Authorisation;}

class Authorisation : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor
     * @param parent
     */
    explicit Authorisation(QWidget *parent = nullptr);
    /**
     * @brief Destructor
     */
    ~Authorisation();
    /**
     * @brief get Nickname
     * @return nickname
     */
    QString getNick();

private:
    Ui::Authorisation *ui;
    QString nick;

private slots:
    /**
     * @brief push button "Ok"
     */
    void pushOk();

signals:
    /**
     * @brief send Nickname
     * @param nick
     */
    void sendNick(QString nick);
};

#endif // AUTHORISATION_H
