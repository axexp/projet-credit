#include "donneur.h"
#include "ui_donneur.h"
#include "donneurs.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QtSql>
#include <fstream>
#include <iostream>
//C:\Users\ahmed\OneDrive\Desktop\projetint
//#include "C:/Users/ahmed/OneDrive/Desktop/projetint/SmtpClient-for-Qt-2.0/src/SmtpMime"
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include<QDesktopServices>
#include "mainwindow.h"

Donneur::Donneur(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Donneur)
{
    ui->setupUi(this);
}

Donneur::~Donneur()
{
    delete ui;
}
void Donneur::on_pushButton_ajouter_clicked()
{

    QString nom_donneur=ui->lineEdit_nom->text();
    QString adresse_donneur=ui->lineEdit_adresse->text();
    QString mail=ui->lineEdit_mail->text();
    int telephone=ui->lineEdit_tlph->text().toInt();
    QString tlph=ui->lineEdit_tlph->text();
    generateQRCode(nom_donneur,adresse_donneur,mail,telephone);
    //C:/Users/ahmed/OneDrive/Desktop/projetint/Aides.pdf
    QString QR="C:/Users/ahmed/OneDrive/Desktop/projetint/QR/" + nom_donneur + ".png";
    donneurs1 d(nom_donneur,adresse_donneur,mail,telephone,QR);
if(verifierAdresse(adresse_donneur) && Etmp.nonvide(nom_donneur) && Etmp.nonvide(adresse_donneur) && Etmp.mailvalide(mail) && Etmp.chiffres(telephone)==8 && !Etmp.existenceM(mail) && !Etmp.existenceN(nom_donneur) && !Etmp.existenceTL(telephone))
{    bool test=d.ajouter();
    if(test)
    {
        int a=ui->comboBox->currentIndex();
        Donneur::on_comboBox_currentIndexChanged(a);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
        ui->lineEdit_nom->clear();
        ui->lineEdit_adresse->clear();
        ui->lineEdit_mail->clear();
        ui->lineEdit_tlph->clear();

        }
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Ajout non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else if(!Etmp.nonvide(nom_donneur))
{
    QMessageBox::critical(nullptr, QObject::tr("Nom du donneur vide"),
                QObject::tr("Le nom du donneur doit exister, veuillez remplir la case : Nom du donneur\n"
                            ), QMessageBox::Ok);
}
else if(!Etmp.nonvide(adresse_donneur))
{
    QMessageBox::critical(nullptr, QObject::tr("Adresse du donneur vide"),
                QObject::tr("L'adresse du donneur doit exister, veuillez remplir la case : Nom du donneur\n"
                            ), QMessageBox::Ok);
}
else if(!verifierAdresse(adresse_donneur) )
{
    QMessageBox::critical(nullptr, QObject::tr("Veuillez spécifier votre adresse"),
                QObject::tr("Veuillez spécifier votre gouvernement dans la case adresse donneur\n Tunis, Ariana, Ben Arous, Manouba, Nabeul, Zaghouan, Bizerte, Beja, Jendouba, Kef, Siliana, Kairouan, Kasserine, Sidi Bouzid, Sousse, Monastir, Mahdia, Gabes, Médenine, Tataouine, Tozeur, Kelibia, Gafsa, Sfax"
                            ), QMessageBox::Ok);
}

else if(!Etmp.mailvalide(mail))
    QMessageBox::critical(nullptr, QObject::tr("Adresse mail invalide"),
                QObject::tr("Adresse mail doit etre sous la forme suivante : xyz@exemple.com ou  xyz@exemple.fr ou  xyz@exemple.tn\n"
                            ), QMessageBox::Ok);
else if(Etmp.chiffres(telephone)!=8)
{
    QMessageBox::critical(nullptr, QObject::tr("Numéro de téléphone invalide"),
                QObject::tr("Les chiffres du numéro du téléphone doit etre =8 chiffres\n"
                            ), QMessageBox::Ok);
}
else if(Etmp.existenceM(mail))
{
    QMessageBox::critical(nullptr, QObject::tr("Adresse mail existe dejà"),
                QObject::tr("il y'a un autre donneur qui a le meme adresse mail\n"
                            ), QMessageBox::Ok);
}
else if(Etmp.existenceN(nom_donneur))
{
    QMessageBox::critical(nullptr, QObject::tr("Nom du donneur existe dejà"),
                QObject::tr("il y'a un autre donneur qui a le meme nom\n"
                            ), QMessageBox::Ok);
}
else if(Etmp.existenceTL(telephone))
{
    QMessageBox::critical(nullptr, QObject::tr("Numero du telephone existe dejà"),
                QObject::tr("il y'a un autre donneur qui a le Numero du telephone\n"
                            ), QMessageBox::Ok);
}
}
void Donneur::on_pushButton_annuler_clicked()
{
    ui->lineEdit_nom->clear();
    ui->lineEdit_adresse->clear();
    ui->lineEdit_mail->clear();
    ui->lineEdit_tlph->clear();
}
void Donneur::on_pushButton_afficher_clicked()
{
    int a=ui->comboBox->currentIndex();
    Donneur::on_comboBox_currentIndexChanged(a);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}
void Donneur::on_pushButton_supprimer_clicked(){
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    int id = selectedIndexes.at(0).data().toInt();
    QString sql = "SELECT nom_donneur FROM donneurs WHERE id_donneur = " + QString::number(id);
    QSqlQuery query;
    query.exec(sql);
    QString nom;
    if (query.next()) {
        nom = query.value(0).toString();
    }
    QString sql2= "SELECT mail FROM donneurs WHERE id_donneur = " + QString::number(id);
    QSqlQuery query2;
    query2.exec(sql2);
    QString to;
    if (query2.next()) {
        to = query2.value(0).toString();
    }
    QString filePath= "C:/Users/ahmed/OneDrive/Desktop/projetint/QR/" + nom + ".png";

    bool test=Etmp.supprimer(id);
    if(test)
    {
        supprimerFichier(filePath);
        int a=ui->comboBox->currentIndex();
        Donneur::on_comboBox_currentIndexChanged(a);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
        ui->lineEdit_nom->clear();
        ui->lineEdit_adresse->clear();
        ui->lineEdit_mail->clear();
        ui->lineEdit_tlph->clear();
}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
void Donneur::on_pushButton_modifier_clicked()
{
    int tlph;
    QString nom,ad,mail;
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    int id = selectedIndexes.at(0).data().toInt();
    nom=ui->lineEdit_nom->text();
    ad=ui->lineEdit_adresse->text();
    mail=ui->lineEdit_mail->text();
    tlph=ui->lineEdit_tlph->text().toInt();
    QString tlph1=ui->lineEdit_tlph->text();
    generateQRCode(nom,ad,mail,tlph);
    QString QR="C:/Users/ahmed/OneDrive/Desktop/projetint/QR/" + nom + ".png";
    QString sql2= "SELECT QR FROM donneurs WHERE id_donneur = " + QString::number(id);
    QSqlQuery query2;
    query2.exec(sql2);
    QString to;
    if (query2.next()) {
        to = query2.value(0).toString();
    }
    if(verifierAdresse(ad) && Etmp.nonvide(nom) && Etmp.nonvide(ad) && Etmp.mailvalide(mail) && Etmp.chiffres(tlph)==8)
    {
    bool test=Etmp.modifier(id,nom,ad,mail,tlph,QR);
    if(test)
    {
        supprimerFichier(to);
        int a=ui->comboBox->currentIndex();
        Donneur::on_comboBox_currentIndexChanged(a);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
        ui->lineEdit_nom->clear();
        ui->lineEdit_adresse->clear();
        ui->lineEdit_mail->clear();
        ui->lineEdit_tlph->clear();

}
else{
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Modification non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}}
    else if(!Etmp.mailvalide(mail))
        QMessageBox::critical(nullptr, QObject::tr("Adresse mail invalide"),
                              QObject::tr("Adresse mail doit etre sous la forme suivante : xyz@exemple.com ou  xyz@exemple.fr ou  xyz@exemple.tn\n"
                                ), QMessageBox::Ok);
    else if(!verifierAdresse(ad) )
    {
        QMessageBox::critical(nullptr, QObject::tr("Veuillez spécifier votre adresse"),
                    QObject::tr("Veuillez spécifier votre gouvernement dans la case adresse donneur\n Tunis, Ariana, Ben Arous, Manouba, Nabeul, Zaghouan, Bizerte, Beja, Jendouba, Kef, Siliana, Kairouan, Kasserine, Sidi Bouzid, Sousse, Monastir, Mahdia, Gabes, Médenine, Tataouine, Tozeur, Kelibia, Gafsa, Sfax"
                                ), QMessageBox::Ok);
    }

    else if(Etmp.chiffres(tlph)!=8)
    {
        QMessageBox::critical(nullptr, QObject::tr("Numéro de téléphone invalide"),
                    QObject::tr("Les chiffres du numéro du téléphone doit etre =8 chiffres\n"
                                ), QMessageBox::Ok);
    }
    else if(!Etmp.nonvide(nom))
    {
        QMessageBox::critical(nullptr, QObject::tr("Nom du donneur vide"),
                    QObject::tr("Le nom du donneur doit exister, veuillez remplir la case : Nom du donneur\n"
                                ), QMessageBox::Ok);
    }
    else if(!Etmp.nonvide(ad))
    {
        QMessageBox::critical(nullptr, QObject::tr("Adresse du donneur vide"),
                    QObject::tr("L'adresse du donneur doit exister, veuillez remplir la case : Nom du donneur\n"
                                ), QMessageBox::Ok);
    }
}
void Donneur::on_comboBox_currentIndexChanged(int index)
{
    if(index==0)
    {
        ui->tableView->setModel(Etmp.afficher());
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
    else if (index==1)
    {
        ui->tableView->setModel(Etmp.odreascendantid());
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
    else if(index==2)
    {
        ui->tableView->setModel(Etmp.odredescendantid());
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
    else if(index==3)
    {
        ui->tableView->setModel(Etmp.odreAlphabetiqueAZ());
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
    else if(index==4)
    {
        ui->tableView->setModel(Etmp.odreAlphabetiqueZA());
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
    else if(index==5)
    {
        ui->tableView->setModel(Etmp.region());
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
    else if(index==6)
    {
        ui->tableView->setModel(Etmp.email());
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
}
void Donneur::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from donneurs where id_donneur='"+val+"' or nom_donneur='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_nom->setText(qry.value(1).toString());
            ui->lineEdit_adresse->setText(qry.value(2).toString());
            ui->lineEdit_mail->setText(qry.value(3).toString());
            ui->lineEdit_tlph->setText(qry.value(4).toString());
        }
    }
            QString filePath = ui->tableView->model()->data(index).toString();
            QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
        }
void Donneur::on_pushButton_pdf_clicked()
{
    Etmp.pdf();

}
void Donneur::on_lineEdit_chercher_textEdited(const QString &arg1)
{
    QString nom=ui->lineEdit_chercher->text();
    ui->tableView->setModel(Etmp.chercherElementParNom(nom));
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    if(arg1 == "")
    {
        int a=ui->comboBox->currentIndex();
        Donneur::on_comboBox_currentIndexChanged(a);
        ui->tableView->resizeRowsToContents();
        ui->tableView->resizeColumnsToContents();
    }
}
void Donneur::on_pushButton_stat_clicked()
{
    statistiques2();
    statistiques();
}


void Donneur::on_pushButton_11_clicked()
{
    close();
    MainWindow* mainWin = new MainWindow();
    mainWin->show();
}

