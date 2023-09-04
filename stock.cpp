#include "stock.h"
#include "ui_stock.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QSystemTrayIcon>
#include <QtCharts/QValueAxis>
#include <QtCharts>
#include "QCalendarWidget"
#include "aide.h"

stock::stock(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stock)
{
    ui->setupUi(this);
}

stock::~stock()
{
    delete ui;
}

void stock::on_pushButton_10_clicked()
{
    close();
    MainWindow* mainWin = new MainWindow();
    mainWin->show();
}

void stock::on_pushButton_ajouter_clicked()
{
    int NUM_AIDE=ui->lineEdit_NUM_AIDE->text().toInt();
    QString TYPE=ui->lineEdit_TYPE->text();
    int QUANTITE=ui->lineEdit_QUANTITE->text().toInt();
    QString DATE_ARRIVE=ui->lineEdit_DATE_ARRIVE->text();
    QString VALIDITE_DU_AIDE=ui->lineEdit_VALIDITE_DU_AIDE->text();

    aide a(NUM_AIDE,TYPE,QUANTITE,DATE_ARRIVE,VALIDITE_DU_AIDE);
    bool test=a.ajouter();
    if(test)
    {
        ui->lineEdit_NUM_AIDE->clear();
        ui->lineEdit_TYPE->clear();
        ui->lineEdit_QUANTITE->clear();
        ui->lineEdit_DATE_ARRIVE->clear();
        ui->lineEdit_VALIDITE_DU_AIDE->clear();
    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Ajout effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    a.notification_dajout_aide();

}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Ajout non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}


void stock::on_pushButton_trier_clicked()
{
    ui->tableView->setModel(a.trie());
}

void stock::on_pushButton_rechercher_clicked()
{
    aide r;
                   QSqlQueryModel *model =r. search(ui->lineEdit_TYPE->text());
                   ui->tableView->setModel(model);
}


void stock::showStockExpiredNotification() {
        QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
        trayIcon->setIcon(QIcon(":/images/icon.png"));
        trayIcon->setVisible(true);
        trayIcon->showMessage("Stock expiré", "La validité du stock est expirée.");
    }



void stock::on_pushButton_pdf_clicked()
{
    a.pdf();
}


void stock::on_pushButton_annuler_clicked()
{
    ui->lineEdit_NUM_AIDE->clear();
    ui->lineEdit_TYPE->clear();
    //ui->lineEdit_TYPE->text().toInt();
    ui->lineEdit_QUANTITE->clear();
    ui->lineEdit_DATE_ARRIVE->clear();
    ui->lineEdit_VALIDITE_DU_AIDE->clear();
}


void stock::on_pushButton_afficher_clicked()
{
    ui->tableView->setModel(a.afficher());
}


void stock::on_pushButton_supprimer_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    int id = selectedIndexes.at(0).data().toInt();
    bool test=a.supprimer(id);
    if(test)
    {
        ui->tableView->setModel(a.afficher());
        ui->lineEdit_TYPE->clear();
        ui->lineEdit_QUANTITE->clear();
        ui->lineEdit_DATE_ARRIVE->clear();
        ui->lineEdit_VALIDITE_DU_AIDE->clear();
    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Suppression effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Suppression non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}




void stock::on_pushButton_modifier_clicked()
{
    //QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    //int id = selectedIndexes.at(0).data().toInt();
    int NUM_AIDE=ui->lineEdit_NUM_AIDE->text().toInt();
    QString TYPE=ui->lineEdit_TYPE->text();
    int QUANTITE=ui->lineEdit_QUANTITE->text().toInt();
    QString DATE_ARRIVE=ui->lineEdit_DATE_ARRIVE->text();
    QString VALIDITE_DU_AIDE=ui->lineEdit_VALIDITE_DU_AIDE->text();

    bool test=a.modifier(NUM_AIDE,TYPE,QUANTITE,DATE_ARRIVE,VALIDITE_DU_AIDE);
    if(test)
    {
        ui->tableView->setModel(a.afficher());

    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Modification effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui->lineEdit_TYPE->clear();
    ui->lineEdit_QUANTITE->clear();
    ui->lineEdit_DATE_ARRIVE->clear();
    ui->lineEdit_VALIDITE_DU_AIDE->clear();
}
else{
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Modification non effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
}


void stock::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from Aides where NUM_AIDE='"+val+"' or TYPE='"+val+"' ");
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->lineEdit_TYPE->setText(qry.value(1).toString());
            ui->lineEdit_QUANTITE->setText(qry.value(2).toString());
            ui->lineEdit_DATE_ARRIVE->setText(qry.value(3).toString());
            ui->lineEdit_VALIDITE_DU_AIDE->setText(qry.value(4).toString());



        }
    }

}



void stock::on_pushButton_statistique_clicked()
{
    QSqlQuery query("SELECT COUNT(*), TYPE FROM AIDE GROUP BY TYPE");

        QVector<QBarSet*> barSets;
        QBarSeries *series = new QBarSeries();

        while (query.next()) {
            QString type = query.value(1).toString();
            int count = query.value(0).toInt();
            QBarSet *barSet = new QBarSet(type);
            *barSet << count;
            barSets.append(barSet);
        }

        // Ajouter les barres au graphique
        for (auto barSet : barSets) {
            series->append(barSet);
        }

        // Définition de l'espacement entre les barres

        // Créer le graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Nombre de RDV par type");
        chart->setAnimationOptions(QChart::AllAnimations);

        // Créer l'axe horizontal
        QStringList categories;
        for (auto barSet : barSets) {
            categories << barSet->label();
        }

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        //axisX->setLabelsAngle(45);
        axisX->setLabelsFont(QFont("Arial", 8));

        for (int i = 0; i < categories.size(); i+=2)
        {
            axisX->append(categories[i]);
        }

        // Créer l'axe vertical
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,10);
        //axisY->setTickInterval(1);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        // Afficher le graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setGeometry(100, 100, 800, 600);
        chartView->show();
}





/*******************************************************************************************************************/



void stock::on_pushButton_ajout_image_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();
    QString id = selectedIndexes.at(0).data().toString();
    a.ajout_image(id);
}

void stock::on_pushButton_notification_clicked()
{

    // dans le constructeur de votre fenêtre principale (MainWindow)
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/images/icon.png"); // chemin vers votre image d'icône
    trayIcon->setIcon(icon);
    trayIcon->setVisible(true);


}



void stock::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    aide B;
                QString inputValue,filterChecked;
                inputValue=ui->lineEdit->text();
                ui->tableView->setModel(a.search(inputValue));
}

