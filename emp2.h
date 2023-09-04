#ifndef EMP2_H
#define EMP2_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QComboBox>
#include "arduino.h"
class emp2
{
private:
    int identifiant;
    int cin ;
    QString nom;
    QString prenom;
    QString fonctionnalites;
    QString grade ;
    QString acces;

public:
    emp2();
    emp2(int,int,QString,QString,QString,QString,QString);

    /*int getidentifiant();
    int getcin();
    QString getnom();
    QString getprenom();
    QString getfonctionnalites();
    QString getgrade();
    void setidentifiant(int);
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setfonctionnalites(QString);
    void setgrade(QString);
    */


    int getidentifiant(){return identifiant;}
    int getcin(){return cin;}
    QString getnom(){return nom;}
    QString getprenom(){return prenom;}
    QString getfonctionnalites(){return fonctionnalites;}
    QString getgrade(){return grade;}
    QString getacces(){return acces;}



    void setidentifiant(int identifiant){this->identifiant=identifiant;}
    void setcin(int cin){this->cin=cin;}
    void setnom(QString nom){this->nom=nom;}
    void setprenom(QString prenom){this->prenom=prenom;}
    void setfonctionnalites(QString fonctionnalites){this->fonctionnalites=fonctionnalites;}
    void setgrade(QString grade){this->grade=grade;}
    void setacces(QString acces){this->acces=acces;}




    //crud
        bool modifier(int identifiant,int cin,QString nom,QString prenom,QString fonctionnalites, QString grade, QString acces);
        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(int);
        //bool  modifier(int);
        void searchEmployee(QSqlTableModel *model, QComboBox *comboBox, QLineEdit *lineEdit);
        void sortEmployee(QSqlTableModel *model, QComboBox *comboBox, QComboBox *comboBox_2);
};

#endif // EMP2_H
