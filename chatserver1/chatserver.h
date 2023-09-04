#ifndef CHATSERVER_H
#define CHATSERVER_H
#include <QTcpServer>
#include "mainwindow.h"

class MainWindow;

class chatserver : public QTcpServer
{
public:
    chatserver();

    Q_OBJECT

public:
    chatserver(MainWindow* pserver , QObject *parent=0);
    MainWindow* m_pWindow;

private slots:
    void readyRead();
    //void disconnected();

protected:
    void incomingConnection(int socketfd);

private:
    QSet<QTcpSocket*> employees;
};

#endif // CHATSERVER_H
