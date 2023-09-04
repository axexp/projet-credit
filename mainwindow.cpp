#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include <QSqlQuery>
#include "QMessageBox"
#include <QString>
#include "global.h"
#include <QByteArray>
#include "arduino.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ret=a.connect_arduino();
    switch(ret)
    {
    case(0):qDebug()<<"arduino is available and connected to : "<<a.getarduino_port_name();
        qDebug()<<"arduino is available and connected to : "<<a.getarduino_port_name();
        break;
    case(1):qDebug()<<"arduino is available but not connected to : "<<a.getarduino_port_name();
        break;
case(-1):qDebug()<<"arduino is not available";
    break;

}
    QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(uid()));
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::uid()
{
    QByteArray d=a.read_from_arduino();
          QString uid = QString::fromLatin1(d.trimmed());
          qDebug()<<"uid2="<<d;

qDebug()<<"uid="<<uid;
          QSqlQuery query;
          query.prepare("SELECT IDENTIFIANT, NOM, PRENOM FROM EMPLOYE WHERE ACCES = ?");
          query.addBindValue(uid);
          query.exec();
          if (query.next()) {
              QString identifiant = query.value(0).toString();
              QString nom = query.value(1).toString();
              QString prenom = query.value(2).toString();
              ui->lineEdit_nom->setText(nom);
              ui->lineEdit_mdp->setText(identifiant);
              qDebug() << "Employé trouvé : " << nom << " (ID : " << identifiant << ")";
              QByteArray bytes;
              bytes.append(prenom.toUtf8());
              bytes.append(" ");
              bytes.append(nom.toUtf8());
              a.write_to_arduino(bytes+ "\n");
              qDebug()<<"bytes = "<<bytes;
          } else {
              qDebug() << "UID non trouvé dans la base de données";
              ui->lineEdit_nom->clear();
              ui->lineEdit_mdp->clear();
              a.write_to_arduino("1");
          }
      }
bool MainWindow::validateEmployee(QString nom, int id) {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE  NOM = ? AND IDENTIFIANT = ?");
        query.addBindValue(nom);
        query.addBindValue(id);
        query.exec();

        if (query.next()) {
            int count = query.value(0).toInt();
            if (count == 1) {
                return true;
            }
        }
        return false;
}
void MainWindow::on_login_clicked()
{
        QString name = ui->lineEdit_nom->text();
        int password = ui->lineEdit_mdp->text().toInt();
        g_loginInfo.username = ui->lineEdit_nom->text();
        g_loginInfo.id = ui->lineEdit_mdp->text().toInt();

         if (validateEmployee(name, password))
         {
             hide();
             menu m;
             m.setModal(true);
             m.exec();
             onClose();
         } else
         {
              QMessageBox::warning(this, "Error", "Invalid name or password.");
         }

}
void MainWindow::onClose()
{
    MainWindow m;
    m.setEnabled(true);
    m.show();
}
