#include "emp2.h"
#include <QDebug>
#include <QSqlQuery>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

emp2::emp2()
{
        identifiant=0;
        cin=0;
        nom=" ";
        prenom=" ";
        fonctionnalites=" ";
        grade=" ";
        acces="";
}

emp2::emp2(int identifiant,int cin,QString nom,QString prenom,QString fonctionnalites,QString grade,QString acces)
{
    this->identifiant=identifiant;
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->fonctionnalites=fonctionnalites;
    this->grade=grade;
    this->acces=acces;
}
bool emp2::ajouter()
{
        QSqlQuery query;
        QString res = QString::number(identifiant);
            query.prepare("INSERT INTO EMPLOYE(IDENTIFIANT,NOM,PRENOM,CIN,FONCTIONNALITES,GRADE,ACCES) "
                          "VALUES (:identifiant,:nom,:prenom,:cin,:fonctionnalites,:grade,:acces)");
            query.bindValue(":identifiant",res);
            query.bindValue(":nom",nom);
            query.bindValue(":prenom",prenom);
            query.bindValue(":cin",cin);
            query.bindValue(":fonctionnalites",fonctionnalites);
            query.bindValue(":grade",grade);
            query.bindValue(":acces",acces);
             return query.exec();

            //qDebug() <<query.lastError();
}
QSqlQueryModel* emp2::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

            model->setQuery("SELECT* FROM EMPLOYE ");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDENTIFIANT"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("FONCTIONNALITES"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("GRADE"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("ACCESS CODE"));
        return  model;

}


bool emp2::supprimer(int id)
{
    QSqlQuery query;
    QString c=QString::number(id);
    query.prepare("Delete from EMPLOYE where IDENTIFIANT= :id");
    query.bindValue(":id",c);
    return  query.exec();
}



/*bool emp2::modifier(int id)
{
    QSqlQuery query;
        QString c = QString::number(id);
        query.prepare("SELECT * FROM EMPLOYE WHERE IDENTIFIANT=:id");
        query.bindValue(":id", c);
        bool test = query.exec();
        if (test)
        {
            if (query.next())
            {
                int cin = query.value(3).toInt();
                QString nom = query.value(1).toString();
                QString prenom = query.value(2).toString();
                QString fonctionnalite = query.value(4).toString();
                QString grade = query.value(5).toString();
                emp2 e(id, cin, nom, prenom, fonctionnalite, grade);

                // Utilisez un formulaire pour modifier les données de l'employé
                QDialog* form = new QDialog();

                QFormLayout* layout = new QFormLayout(form);
                QLineEdit* nomEdit = new QLineEdit(nom);
                layout->addRow("Nom:", nomEdit);
                QLineEdit* prenomEdit = new QLineEdit(prenom);
                layout->addRow("Prénom:", prenomEdit);
                QLineEdit* cinEdit = new QLineEdit(QString::number(cin));
                layout->addRow("Numéro de téléphone:", cinEdit);
                QLineEdit* fonctionEdit = new QLineEdit(fonctionnalite);
                layout->addRow("Fonctionnalité:", fonctionEdit);
                QLineEdit* gradeEdit = new QLineEdit(grade);
                layout->addRow("grade:", gradeEdit);
                QPushButton* okButton = new QPushButton("OK", form);
                layout->addWidget(okButton);
                QObject::connect(okButton, &QPushButton::clicked, form, &QDialog::accept);
                QPushButton* cancelButton = new QPushButton("Annuler", form);
                layout->addWidget(cancelButton);
                QObject::connect(cancelButton, &QPushButton::clicked, form, &QDialog::reject);

                if (form->exec() == QDialog::Accepted)
                {
                    // Retrieve the modified data from the input fields
                    e.setnom(nomEdit->text());
                    e.setprenom(prenomEdit->text());
                    e.setcin(cinEdit->text().toInt());
                    e.setfonctionnalites(fonctionEdit->text());
                    e.setgrade(gradeEdit->text());


                // Exécuter une requête de mise à jour pour mettre à jour les données dans la base de données
                QSqlQuery updateQuery;
                updateQuery.prepare("UPDATE EMPLOYEE SET IDENTIFIANT=:id, CIN=:cin, NOM=:nom, PRENOM=:prenom, FONCTIONNALITES=:fonctionnalite, GRADE=:grade WHERE IDENTIFIANT=:id");
                updateQuery.bindValue(":nom", e.getnom());
                updateQuery.bindValue(":prenom", e.getprenom());
                updateQuery.bindValue(":cin", e.getcin());
                updateQuery.bindValue(":fonctionnalite", e.getfonctionnalites());
                updateQuery.bindValue(":grade", e.getgrade());
                updateQuery.bindValue(":id", id);



                return updateQuery.exec();
            }
            }
        }
        return false;
}*/

bool emp2::modifier(int identifiant,int cin,QString nom,QString prenom,QString fonctionnalites, QString grade, QString acces) {

    QSqlQuery query;

    query.prepare("UPDATE EMPLOYE SET NOM=:NOM , PRENOM=:PRENOM, CIN=:CIN, FONCTIONNALITES=:FONCTIONNALITES, GRADE=:GRADE, ACCES= :ACCES WHERE IDENTIFIANT=:IDENTIFIANT");
     query.bindValue(":IDENTIFIANT", identifiant);

    query.bindValue(":NOM", nom);

    query.bindValue(":PRENOM", prenom);

    query.bindValue(":CIN", cin);

    query.bindValue(":FONCTIONNALITES", fonctionnalites);

    query.bindValue(":GRADE", grade);
    query.bindValue(":ACCES", acces);
    return query.exec();

}

void emp2::searchEmployee(QSqlTableModel *model, QComboBox *comboBox, QLineEdit *lineEdit)

{

        QString searchTerm = lineEdit->text().trimmed();

        QString searchFilter = comboBox->currentText();



        QString queryText = "1=1";

        if (!searchTerm.isEmpty()) {

            if (searchFilter == "nom") {

                queryText += QString(" AND nom LIKE '%%1%' ").arg(searchTerm);

            } else if (searchFilter == "prénom") {

                queryText += QString(" AND prenom LIKE '%%1%'").arg(searchTerm);

            }

        }



        model->setFilter(queryText);

        model->select();

}



void emp2::sortEmployee(QSqlTableModel *model, QComboBox *comboBox, QComboBox *comboBox_2)

{

    QString sortField = comboBox->currentText();

        QString sortOrder = comboBox_2->currentText();



        QString sortText = "";

        if (sortField == "nom") {

            sortText += "nom";

        } else if (sortField == "prénom") {

            sortText += "prenom";

        }



        if (sortOrder == "croissant") {

            sortText += " ASC";

        } else if (sortOrder == "décroissant") {

            sortText += " DESC";

        }


        model->setSort(model->fieldIndex(sortField), sortOrder == "croissant" ? Qt::AscendingOrder : Qt::DescendingOrder);

        model->select();

}
