#include "chat.h"
#include "ui_chat.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QSqlQuery>
#include <QDateTime>
#include <QSqlError>
#include <QMessageBox>


chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)

{
    m_pEmployeeSocket = new QTcpSocket(this);
    ui->setupUi(this);

}

chat::~chat()
{
    delete ui;
}



void chat::on_pushButton_connect_clicked()
{
    m_pEmployeeSocket->connectToHost(ui->textEdit_adress->toPlainText(),quint16(ui->textEdit_port->toPlainText().toInt()));
    connect(m_pEmployeeSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
}



void chat::displayError(QAbstractSocket::SocketError socketError)
{
    QString errorMessage;
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Fortune Employee"),
                                     tr("the host was not found. Please check the"
                                        "host name and port settings"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information( this, tr("Fortune Employee"),
                                      tr("the connection was refused by the peer."
                                         "Make sure the fortune server is running,"
                                         "and check that the host name and port"
                                         "settings are connected"));
            break;
        default:
            QMessageBox::information(this, tr("Fortune Employee"),
                                     tr("the following error occured: %1.")
                                     .arg(m_pEmployeeSocket->errorString()));
    }

}

void chat::on_pushButton_send_clicked()
{
    QString message = ui->textEdit_message->toPlainText().trimmed();
    if(!message.isEmpty())
    {
        m_pEmployeeSocket->write(QString(message + "\n").toUtf8());
        ui->textEdit_message->append(message);

    }
    ui->textEdit_message->clear();

    ui->textEdit_message->setFocus();
}
