#ifndef AIDE_H
#define AIDE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QByteArray>
#include<QImage>


class aide
{
    int NUM_AIDE;
    int QUANTITE;
    QString TYPE,DATE_ARRIVE,VALIDITE_DU_AIDE;
    QString img;

public:
    aide();
    aide(int NUM_AIDE,QString TYPE,int QUANTITE,QString DATE_ARRIVE,QString VALIDITE_DU_AIDE);

    QString get_TYPE();
    QString get_DATE_ARRIVE();
    QString get_VALIDITE_DU_AIDE() ;
    int get_NUM_AIDE();
    int get_QUANTITE();

    void set_TYPE(QString n);
    void set_DATE_ARRIVE(QString n);
    void set_VALIDITE_DU_AIDE(QString n);
    void set_NUM_AIDE(int n);
    void set_QUANTITE(int n);




    void notification_dajout_aide();
    void ajout_image(QString image);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int NUM_AIDE);
    bool modifier(int NUM_AIDE, QString TYPE,int QUANTITE,QString DATE_ARRIVE,QString VALIDITE_DU_AIDE);
    void pdf();
    QSqlQueryModel *trie();
    QSqlQueryModel *search(QString type);

};
#endif // AIDE_H
