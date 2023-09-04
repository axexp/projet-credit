#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <QAbstractSocket>
#include <QTcpSocket>





namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat( QWidget *parent = nullptr);
    ~chat();
    QTcpSocket *m_pEmployeeSocket;

    /*void setRecipient(QString recipient);
    void sendMessage();
    void receiveMessage();
    void connectToServer();
    void disconnectFromServer();
    void displayError(QAbstractSocket::SocketError socketError);
    void displayNewMessage(QString sender, QString message);*/

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_send_clicked();

    void displayError(QAbstractSocket::SocketError socketError);

private:
    Ui::chat *ui;
    QString m_recipient;
    QTcpSocket *m_socket;


};

#endif // CHAT_H
