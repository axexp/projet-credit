#include "beneficiaire.h"

Beneficiaire::Beneficiaire()
{

}
Beneficiaire::Beneficiaire(int id,QString nom,QString num,QString adresse) //,int besoin
{
    this->id=id;
    this->nom=nom;
    this->numtel=num;
    this->adresse=adresse;
    //this->besoin=besoin;
}

bool Beneficiaire::ajouter_Beneficiaire()
{

    QSqlQuery query;
         query.prepare("INSERT INTO beneficiaire ( id,nom, numtel,adresse,besoin) "
                       "VALUES (:id,:nom, :numtel, :adresse,:besoin)");
         query.bindValue(":id",id);
         query.bindValue(":nom",nom);
         query.bindValue(":numtel", numtel);
         query.bindValue(":adresse", adresse);
         query.bindValue(":besoin", besoin);
        return query.exec();
}
bool Beneficiaire::supprimer_Beneficiaire(int id)
{
    QSqlQuery query;
         query.prepare(" Delete from beneficiaire where id=:id");
         query.bindValue(0, id);

        return query.exec();


}
bool Beneficiaire::modifier_Beneficiaire()
{

        QSqlQuery query;

        query.prepare("update beneficiaire set nom=:nom,numtel=:numtel,adresse=:adresse,besoin=:besoin where id=:id");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":numtel",numtel);
        query.bindValue(":adresse", adresse);
        query.bindValue(":besoin", besoin);
        return    query.exec();

}
QSqlQueryModel* Beneficiaire::afficher_Beneficiaire()
{
  QSqlQueryModel* model=new QSqlQueryModel();


   model->setQuery("SELECT * FROM beneficiaire ");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMERO DE TELEPHONE"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
   //model->setHeaderData(4, Qt::Horizontal, QObject::tr("BESOIN"));
   return  model;
}

QSqlQueryModel* Beneficiaire::rechercherdynamique(QString input,QString filter)
{
    QSqlQueryModel * model= new QSqlQueryModel ();
       QSqlQuery query;
       query.prepare("SELECT * FROM beneficiaire WHERE "+filter+" LIKE '%' || :inputValue || '%' ");
       query.bindValue(":inputValue",input);
       query.exec();
       model->setQuery(query);
       return model;
}


