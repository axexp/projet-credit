#include "evenement.h"
#include "QString"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QPdfWriter>
#include<QTextDocument>
#include<QDesktopServices>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <QRectF>
evenement::evenement()
{
  Numero=0;
  Nom="";
  Date_evenement="";
  Lieu="";
  nombre_des_participants=0;
  Actions="";
}
evenement::evenement(int Numero,QString Nom,QString Date_evenement,QString Lieu,int nombre_des_participants,QString Actions)
{
  this->Numero=Numero;
  this->Nom=Nom;
  this->Date_evenement=Date_evenement;
  this->Lieu=Lieu;
  this->nombre_des_participants=nombre_des_participants;
  this->Actions=Actions;
}
int evenement::getNumero(){return Numero;}
QString evenement::getNom(){return Nom;}
QString evenement::getDate_evenement(){return Date_evenement;}
QString evenement::getLieu(){return Lieu;}
int evenement::getnombre_des_participants(){return nombre_des_participants;}
QString evenement::getActions(){return Actions;}
void evenement::setNumero(int Numero){this->Numero=Numero;}
void evenement::setNom(QString Nom){this->Nom=Nom;}
void evenement::setDate_evenement(QString Date_evenement){this->Date_evenement=Date_evenement;}
void evenement::setLieu(QString Lieu){this->Lieu=Lieu;}
void evenement::setnombre_des_participants(int nombre_des_participants){this->nombre_des_participants=nombre_des_participants;}
void evenement::setActions(QString Actions){this->Actions=Actions;}
bool evenement::ajouter()
{
    QSqlQuery query;
    QString Numero_string=QString::number(Numero);
          query.prepare("insert into EVENEMENT (Numero, Nom, Date_evenement,Lieu,nombre_des_participants,Actions)""values(:Numero,:Nom,:Date_evenement,:Lieu,:nombre_des_participants,:Actions)");
          query.bindValue(":Numero",Numero_string);
          query.bindValue(":Nom",Nom);
          query.bindValue(":Date_evenement", Date_evenement);
          query.bindValue(":Lieu", Lieu);
          query.bindValue(":nombre_des_participants", nombre_des_participants);
          query.bindValue(":Actions", Actions);
          return query.exec();
}

QSqlQueryModel* evenement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM EVENEMENT ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("Numero"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_Activités"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Lieu"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("nombre_des_participants"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Actions"));
    return model;
}
bool evenement::supprimer(int Numero)
{
    QSqlQuery query;
    QString res=QString::number(Numero);
    query.prepare("Delete from EVENEMENT where Numero= :Numero");
    query.bindValue(":Numero",res);

    return query.exec();
}
void evenement::pdf()
{
    QSqlQuery query;
     query.exec("SELECT Numero, Nom, Date_evenement, Lieu, nombre_des_participants,Actions FROM EVENEMENT");
     QPdfWriter writer("C:/Users/ahmed/OneDrive/Desktop/projetint/Evenements.pdf");
     //C:\Users\ahmed\OneDrive\Desktop\projetint
     QTextDocument document;
     writer.setTitle("Liste des évènements");
     QString title = "<h1>Liste des évènements</h1>";
     QString table = "<table border='1'><tr><th>Numero evenement</th><th>Nom evenement</th><th>Date evenement</th><th>Lieu evenement</th><th>nombre des participant</th><th>Actions evenement</th></tr>";
     while (query.next()) {
         int Numero = query.value(0).toInt();
         QString Nom = query.value(1).toString();
         QString Date_evenement = query.value(2).toString();
         QString Lieu = query.value(3).toString();
         int nombre_des_participants = query.value(4).toInt();
         QString Actions = query.value(5).toString();
         table += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td></tr>").arg(Numero).arg(Nom).arg(Date_evenement).arg(Lieu).arg(nombre_des_participants).arg(Actions);
     }
     table += "</table>";
     document.setHtml(title + table);
     document.print(&writer);
     QString file_path = "C:/Users/ahmed/OneDrive/Desktop/projetint/Evenements.pdf";
     QDesktopServices::openUrl(QUrl::fromLocalFile(file_path));

}
bool evenement::modifier(int num,int NUMERO,QString  NOM ,QString DATE_EVENEMENT,QString LIEU ,int NOMBRE_DES_PARTICIPANTS ,QString ACTIONS )
{
    QSqlQuery query;
    QString res1=QString::number(NUMERO);
    QString res2=QString::number(NOMBRE_DES_PARTICIPANTS);
    QString res3=QString::number(num);
    query.prepare("UPDATE EVENEMENT SET NUMERO = '"+res1+"', NOM = '"+NOM+"', DATE_EVENEMENT = '"+DATE_EVENEMENT+"', LIEU = '"+LIEU+"', NOMBRE_DES_PARTICIPANTS = '"+res2+"', ACTIONS = '"+ACTIONS+"' WHERE NUMERO = '"+res3+"'");
    query.bindValue(":num", res3);
    query.bindValue(":numero", res1);
    query.bindValue(":nombre_des_partcicpants", res2);
    if(query.exec())
    {
        return true;
    }
    else
    {
        return false;
    }
}
QSqlQueryModel *evenement::tri()
{
    QSqlQueryModel * model=new QSqlQueryModel();


 model->setQuery("select * from EVENEMENT ORDER BY  NUMERO ASC ");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMERO"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_EVENEMENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("LIEU"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NOMBRE_DES_PARTICIPANTS"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ACTIONS"));


    return  model;
}
QSqlQueryModel * evenement::chercherElementParNom(QString nom)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString query = "SELECT * FROM EVENEMENT WHERE UPPER(NOM) LIKE UPPER('" + nom + "%')";
    model->setQuery(query);
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMERO"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DATE_EVENEMENT"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("LIEU"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NOMBRE_DES_PARTICIPANTS"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ACTIONS"));

    return model;
}
