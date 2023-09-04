#ifndef EVENEMENT_H
#define EVENEMENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>
class evenement
{
private:
    QString Nom,Date_evenement,Lieu,Actions;
    int Numero,nombre_des_participants;

public:
    evenement();
    evenement(int,QString,QString,QString,int,QString);
    int getNumero();
    QString getNom();
    QString getDate_evenement();
    QString getLieu();
    int getnombre_des_participants();
    QString getActions();
    void setNumero(int);
    void setNom(QString);
    void setDate_evenement(QString);
    void setLieu(QString);
    void setnombre_des_participants(int);
    void setActions(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer (int Numero);
    bool modifier(int num, int NUMERO,QString  NOM ,QString DATE_EVENEMENT,QString LIEU ,int NOMBRE_DES_PARTICIPANTS ,QString ACTIONS );
    void pdf();
    QSqlQueryModel* tri();
    QSqlQueryModel* chercherElementParNom(QString nom);
};

#endif // EVENEMENT_H
