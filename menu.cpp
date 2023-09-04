#include "menu.h"
#include "ui_menu.h"
#include "f_necess.h"
#include "emp.h"
#include "global.h"
#include <QSqlQuery>
#include "event1.h"
#include "donneur.h"
#include "stock.h"
menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);


    QString username = g_loginInfo.username;
    int id = g_loginInfo.id;

    // Query the database for the user's information
    QSqlQuery query;
    query.prepare("SELECT FONCTIONNALITES FROM EMPLOYE WHERE nom = :username AND identifiant = :id");
    query.bindValue(":username", username);
    query.bindValue(":id", id);
    query.exec();

    if (query.next()) {

        QString fonction = query.value(0).toString();

        if(fonction=="a")
        {
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(false);

        }
        if(fonction=="b")
        {
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
        }
        if(fonction=="c")
        {
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(false);
        }
        if(fonction=="d")
        {
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_5->setEnabled(false);
        }
        if(fonction=="e")
        {
            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);
            ui->pushButton_5->setEnabled(true);
        }
        }
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    stock f;
    close();
    f.setModal(true);
    f.exec();
}

void menu::on_pushButton_2_clicked()
{
   f_necess f;
   close();
   f.setModal(true);
   f.exec();
}

void menu::on_pushButton_3_clicked()
{
    emp e;
    close();
    e.setModal(true);
    e.exec();
}

void menu::on_pushButton_4_clicked()
{
    Donneur e;
    close();
    e.setModal(true);
    e.exec();
}


void menu::on_pushButton_5_clicked()
{
    event1 e;
    close();
    e.setModal(true);
    e.exec();

}

