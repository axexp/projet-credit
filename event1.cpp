#include "event1.h"
#include "ui_event1.h"
#include <QMessageBox>
#include "mainwindow.h"
event1::event1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::event1)
{
    ui->setupUi(this);
    ui->tab_evenement->setModel(e.afficher());

}

event1::~event1()
{
    delete ui;
}

void event1::on_pb_ajouter_clicked()
{
  int Numero=ui->le_Numero->text().toInt();
  QString Nom=ui->le_Nom->text();
  QString Date_evenement=ui->dateEdit->text();
  QString Lieu=ui->le_Lieu->text();
  int nombre_des_participants=ui->le_nombre_des_participants->text().toUInt();
  QString Actions=ui->le_Actions->text();
  evenement e(Numero,Nom,Date_evenement,Lieu,nombre_des_participants,Actions);
  bool test=e.ajouter();
  if(test)
{
      //refresh(actualisation)
      ui->tab_evenement->setModel(e.afficher());

      QMessageBox::information(nullptr,QObject::tr("Ok"),
                  QObject::tr("Ajouter effectué\n"
                               "Click Cancel to exit"),QMessageBox::Cancel);
}
  else
      QMessageBox::critical(nullptr, QObject::tr("not OK"),
                            QObject::tr("ajouter non effectué\n"
                            "click cancel to exit"),QMessageBox::Cancel);
}




void event1::on_pb_supprimer_clicked()
{
    int Numero=ui->lineEdit->text().toInt();
    bool test=e.supprimer(Numero);
    if(test)
    {
        //Refresh(Actualisation)
        ui->tab_evenement->setModel(e.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("suppression effectuée\n"));

    }
    else
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
                           QObject::tr("suppression non effectuée."));
}
void event1::on_tab_evenement_doubleClicked(const QModelIndex &index)
{
    QString val=ui->tab_evenement->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from evenement where numero='"+val+"' or nom='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->le_Numero->setText(qry.value(0).toString());
            ui->le_Nom->setText(qry.value(1).toString());
            ui->dateEdit->setDate(qry.value(2).toDate());
            ui->le_Lieu->setText(qry.value(3).toString());
            ui->le_nombre_des_participants->setText(qry.value(4).toString());
            ui->le_Actions->setText(qry.value(5).toString());

        }
    }
}
void event1::on_pb_modifier_clicked()
{
    QModelIndexList selectedIndexes = ui->tab_evenement->selectionModel()->selectedIndexes();
    int num = selectedIndexes.at(0).data().toInt();
    qDebug()<<num;
    int NUMERO=ui->le_Numero->text().toInt();
    QString NOM=ui->le_Nom->text();
    QString DATE_EVENEMENT=ui->dateEdit->text();
    QString LIEU=ui->le_Lieu->text();
    int NOMBRE_DES_PARTICIPANTS=ui->le_nombre_des_participants->text().toInt();
    QString ACTIONS=ui->le_Actions->text();
    bool test=e.modifier(num,NUMERO,NOM,DATE_EVENEMENT,LIEU,NOMBRE_DES_PARTICIPANTS,ACTIONS);
    if(test)
    {
        ui->tab_evenement->setModel(e.afficher());

    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Modification effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->le_Numero->clear();
    ui->le_Nom->clear();
    ui->dateEdit->clear();
    ui->le_Lieu->clear();
    ui->le_nombre_des_participants->clear();
    ui->le_Actions->clear();
}
else{
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Modification non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
}

void event1::on_pushButton_clicked()
{
    e.pdf();
}

void event1::on_pb_tri_2_clicked()
{
    ui->tab_evenement->setModel(e.tri());
}

void event1::on_le_chercher_textEdited(const QString &arg1)
{
    QString nom=ui->le_chercher->text();
        ui->tab_evenement->setModel(e.chercherElementParNom(nom));
        ui->tab_evenement->resizeRowsToContents();
        ui->tab_evenement->resizeColumnsToContents();
        if(arg1 == "")
        {
            //int a=ui->comboBox->currentIndex();
            //Dialog::on_comboBox_currentIndexChanged(a);
            ui->tab_evenement->setModel(e.afficher());

            ui->tab_evenement->resizeRowsToContents();
            ui->tab_evenement->resizeColumnsToContents();
        }
}


void event1::on_pushButton_9_clicked()
{
    close();
    MainWindow* mainWin = new MainWindow();
    mainWin->show();
}


