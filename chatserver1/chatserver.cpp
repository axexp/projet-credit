#include "chatserver.h"
#include <QTcpSocket>


chatserver::chatserver(MainWindow* pServer, QObject *parent): QTcpServer(parent)
{
    m_pWindow=pServer;
}

void chatserver::incomingConnection(int socketfd)
{
    QTcpSocket *employee= new QTcpSocket(this);
    employee->setSocketDescriptor(socketfd);
    employees.insert(employee);

    m_pWindow->addMessage("New employee from: "+employee->peerAddress().toString());

    connect(employee, SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(employee, SIGNAL(disconnected()),this,SLOT(disconnected()));
}

void chatserver::readyRead()
{
    QTcpSocket *employee =(QTcpSocket*)sender();
    while(employee->canReadLine())
    {
        QString line = QString::fromUtf8(employee->readLine()).trimmed();
        m_pWindow->addMessage(line);
    }
}
