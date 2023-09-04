#ifndef BENEFICIAIRE_H
#define BENEFICIAIRE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Beneficiaire
{
    QString nom,numtel,adresse;
    int  id,besoin;
public:
    //constructeurs
    Beneficiaire();
    Beneficiaire(int,QString,QString,QString);//,int
    //getters
    QString getnom(){return nom;}
    QString getnumtel(){return numtel;}
    QString getadresse(){return adresse;}
    int getid(){return id;}
    //int getbesoin(){return besoin;}
    //setters
    void setnom(QString n){nom=n;}
    void setnumtel(QString n){numtel=n;}
    void setadresse(QString n){adresse=n;}
    //void setbesoin(int n){besoin=n;}
    void setid(int n){id=n;}

    bool ajouter_Beneficiaire();
    QSqlQueryModel* afficher_Beneficiaire();
    bool supprimer_Beneficiaire(int);
    bool modifier_Beneficiaire();
    QSqlQueryModel * rechercherdynamique(QString input,QString filter);

};

#endif // BENEFICIAIRE_H
