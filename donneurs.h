#ifndef DONNEURS_H
#define DONNEURS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include "connection.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <qrcodegen.hpp>
class donneurs1
{
    QString nom_donneur, adresse_donneur, mail,QR;
    int id_donneur;
    int telephone;

public:
    donneurs1();
    donneurs1(QString,QString,QString,int,QString);
    QString get_nom();
    QString get_adresse();
    QString get_mail() ;
    int get_tlph();
    int get_id();
    void setnom(QString n);
    void setadresse(QString n);
    void setdate(QString n);
    void setmail(QString n);
    void settlph(int telephone);
    void setid(int id_donneur);
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int id);
    bool modifier(int,QString,QString,QString,int,QString);
    bool existenceM(QString value);
    bool mailvalide(const QString& chaine);
    int chiffres(int nombre);
    bool existenceN(QString value);
    bool existenceTL(int val);
    bool nonvide(QString i);
    void pdf();
    QSqlQueryModel * odreascendantid();
    QSqlQueryModel * odredescendantid();
    QSqlQueryModel * odreAlphabetiqueAZ();
    QSqlQueryModel * odreAlphabetiqueZA();
    QSqlQueryModel * chercherElementParNom(QString nom);
    QSqlQueryModel * email();
    QSqlQueryModel * region();


};
void supprimerFichier(QString nomFichier);
void statistiques2();
bool verifierAdresse(QString adresse);
void statistiques();
void sentmail(QString to,QString,QString,QString,QString);
void sentmail2(QString to,QString,QString,QString,QString);
void sentmail3(QString to);
void generateQRCode(QString nom_donneur,QString adresse_donneur,QString mail,int telephone);
#endif // DONNEURS_H
//
