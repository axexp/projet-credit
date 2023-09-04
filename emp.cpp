#include "emp.h"
#include "ui_emp.h"
#include <QMessageBox>
#include "emp2.h"
#include <QInputDialog>
#include <QSqlQuery>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QChartView>
#include <QChart>
#include <QString>
#include <QChart>
#include "chat.h"
#include "mainwindow.h"
emp::emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::emp)
{
    ui->setupUi(this);
    ui->tableView->setModel(Emp.afficher());
//controle de saisie
        ui->le_cin->setValidator(new QIntValidator(0,99999,this));
        ui->le_id->setValidator(new QIntValidator(0,999,this));

        QRegularExpression regExp_n("^[a-zA-Z]+$");
        QValidator *validator_n = new QRegularExpressionValidator(regExp_n, this);
        ui->le_nom->setValidator(validator_n);

        QRegularExpression regExp_p("^[a-zA-Z]+$");
        QValidator *validator_p = new QRegularExpressionValidator(regExp_p, this);
        ui->le_prenom->setValidator(validator_p);

        QRegularExpression regExp_g("^[a-zA-Z]+$");
        QValidator *validator_g = new QRegularExpressionValidator(regExp_g, this);
        ui->le_prenom->setValidator(validator_g);

        QRegularExpression regExp_f("^[a-zA-Z]+$");
        QValidator *validator_f = new QRegularExpressionValidator(regExp_f, this);
        ui->la_fonctionnalites->setValidator(validator_f);

        ui->valider->setEnabled(false);
        ui->annuler->setEnabled(false);




}

emp::~emp()
{
    delete ui;
}

void emp::on_pushButton_4_clicked()
{

       int identifiant=ui->le_id->text().toInt();
       int cin=ui->le_cin->text().toInt();
       QString nom=ui->le_nom->text();
       QString prenom=ui->le_prenom->text();
       QString fonctionnalites=ui->la_fonctionnalites->text();
       QString grade=ui->le_grade->text();
       QString acces=ui->acces->text();
       emp2 E(identifiant,cin,nom,prenom,fonctionnalites, grade, acces);
        bool test=E.ajouter();
        if (test)
        {
            ui->tableView->setModel(E.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                 QObject::tr("Ajout avec succès.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            ui->le_id->clear();
            ui->le_nom->clear();
            ui->le_prenom->clear();
            ui->le_cin->clear();
            ui->la_fonctionnalites->clear();
            ui->le_grade->clear();
            ui->acces->clear();

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                  QObject::tr("Echec d'ajout.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

        }
}

void emp::on_pushButton_3_clicked()
{
    bool ok;
       QString id = QInputDialog::getText(this, tr("Enter ID"),
                                           tr("ID of row to delete:"), QLineEdit::Normal,
                                           "", &ok);
       if (!ok || id.isEmpty())
       {
           return;
       }
       int id1 = id.toInt();


       bool test = Emp.supprimer(id1);
       if (test)
       {
           ui->tableView->setModel(Emp.afficher());
           QMessageBox::information(nullptr, tr("OK"), tr("Suppression effectuée."));
       }
       else
       {
           QMessageBox::critical(nullptr, tr("Erreur"), tr("Suppression non effectuée."));
       }
}



void emp::on_valider_clicked()
{
    //int cin= on_modifier_clicked();
        QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Validation de modification", "Êtes-vous sûr de vouloir modifier cet employé ?",
                                            QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {

                int identifiant=ui->le_id->text().toInt();
                int cin = ui->le_cin->text().toInt();
                QString nom = ui->le_nom->text();
                QString prenom = ui->le_prenom->text();
                //int num = ui->le_id->text().toInt();
                QString fonctionnalites = ui->la_fonctionnalites->text();
                QString grade = ui->le_grade->text();

                QString acces = ui->acces->text();

                if (Emp.modifier(identifiant,cin,nom,prenom,fonctionnalites, grade,acces))
                {
                    QMessageBox::information(this,"Modification réussie","Les données de l'employé ont été modifiées avec succès");
                    ui->valider->setEnabled(false);
                    ui->annuler->setEnabled(false);
                    ui->modifier->setEnabled(true);
                    ui->tableView->setModel(Emp.afficher());

                    //on_afficher_employe_clicked();
                }
                else
                {
                    QMessageBox::warning(this,"Modification échouée","Une erreur est survenue lors de la modification des données de l'employé");
                }
            } else {
                ui->valider->setEnabled(false);
                ui->annuler->setEnabled(false);
                ui->modifier->setEnabled(true);

            }
            ui->le_cin->clear();
            ui->le_nom->clear();
            ui->le_prenom->clear();
            ui->le_id->clear();
            ui->la_fonctionnalites->clear();

            ui->le_grade->clear();

}

void emp::on_modifier_clicked()
{
    bool ok;
           int id = QInputDialog::getInt(this, tr("Modifier employé"),
                                           tr("ID de l'employé:"), 0, 0, 100000, 1, &ok);
           if (ok)
           {
               ui->le_id->setText(QString::number(id));
               QSqlQuery query;
               query.prepare("SELECT  NOM, PRENOM, CIN , FONCTIONNALITES ,GRADE,ACCES  FROM EMPLOYE WHERE IDENTIFIANT = :IDENTIFIANT");
               query.bindValue(":IDENTIFIANT", id);
               if (query.exec() && query.next()) {
                  // ui->le_id->setText(query.value(0).toString());
                   ui->le_nom->setText(query.value(0).toString());
                   ui->le_prenom->setText(query.value(1).toString());
                   ui->le_cin->setText(query.value(2).toString());
                   ui->la_fonctionnalites->setText(query.value(3).toString());
                   ui->le_grade->setText(query.value(4).toString());
                   ui->acces->setText(query.value(5).toString());
                   ui->valider->setEnabled(true);
                   ui->annuler->setEnabled(true);
                   ui->modifier->setEnabled(false);
                   //ui->le_cin->setEnabled(false);
                   ui->le_id->setEnabled(false);
               }
               else {
                   QMessageBox::warning(this, tr("Modification échouée"),
                                        tr("L'employé avec CIN %1 n'existe pas.").arg(id));
               }
           }
}

void emp::on_pushButton_7_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");

            if (fileName.isEmpty())
                return;

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);

            QPainter painter(&printer);
            painter.setRenderHint(QPainter::Antialiasing, true);

            QAbstractItemModel *model = ui->tableView->model();
            int rowCount = model->rowCount();
            int columnCount = model->columnCount();

            // Loop through the rows and columns of the tableView and export the data
            for (int row = 0; row < rowCount; row++) {
                for (int column = 0; column < columnCount; column++) {
                    QModelIndex index = model->index(row, column);
                    QString text = model->data(index, Qt::DisplayRole).toString();
                    painter.drawText(50 + column * 120, 50 + row * 20, text);
                }
            }

            painter.end();

            QMessageBox::information(this, "PDF Export", "PDF exported to " + fileName);
    }


void emp::on_recherche_textChanged()
{
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("EMPLOYE");
    Emp.searchEmployee(model, ui->chercher_par, ui->recherche);
    ui->tableView->setModel(model);
}

void emp::on_ordre_tri_currentTextChanged()
{
     Emp.sortEmployee(qobject_cast<QSqlTableModel*>(ui->tableView->model()), ui->trier_par, ui->ordre_tri);
}

void emp::on_stat_clicked()
{
    QChartView *chartView = new QChartView();

       // Show the statistics in the existing widget
       showStatistics(ui->widget_4, chartView);

       // Set the chart view as the central widget of the existing widget
       QVBoxLayout *layout = new QVBoxLayout(ui->widget_4);
       layout->addWidget(chartView);

}

void emp::showStatistics(QWidget *parent, QChartView *chartView)
{
    QSqlQuery query("SELECT fonctionnalites, COUNT(*) FROM EMPLOYE GROUP BY fonctionnalites");
        QMap<QString, int> data;
        while (query.next()) {
            QString fonction = query.value(0).toString();
            int count = query.value(1).toInt();
            data[fonction] = count;
        }

        // Create a pie series with the data
        QPieSeries *series = new QPieSeries();
        for (auto it = data.begin(); it != data.end(); ++it) {
            series->append(it.key(), it.value());
        }

        // Create a chart and add the series
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistics by Function");

        // Set the chart as the central widget of the chart view
        chartView->setChart(chart);

        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedSize(350, 300); // set fixed size

        QVBoxLayout *layout = new QVBoxLayout(parent);
        layout->addWidget(chartView);



}

void emp::on_pushButton_6_clicked()
{
    chat c;
    c.setModal(true);
    c.exec();
}

void emp::on_pushButton_10_clicked()
{
    close();
    MainWindow* mainWin = new MainWindow();
    mainWin->show();
}

