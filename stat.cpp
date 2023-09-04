#include "stat.h"
#include "ui_stat.h"
#include "evenement.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

Stat::Stat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stat)
{
    ui->setupUi(this);
    QBarSet *set0= new QBarSet("nabeul");
    QBarSet *set1= new QBarSet("hammemet");
    QBarSet *set2= new QBarSet("tunis");
    QBarSet *set3= new QBarSet("ariana");
    QBarSet *set4= new QBarSet("manouba");



   QBarSeries *series = new QBarSeries();
   series->append(set0);
   series->append(set1);
   series->append(set2);
   series->append(set3);
   series->append(set4);

   QChart *chart = new QChart();
   chart->addSeries(series);
   chart->setTitle("stat de lieu de l'evenement");
   chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "nabeul"  << "hammemet" <<  "tunis"  << "ariana" << "manouba";
    QBarCategoryAxis *axis =new QBarCategoryAxis ();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);

    QChartView *chartView= new QChartView(chart);
    chartView->setParent(ui->frame);
}

Stat::~Stat()
{
    delete ui;
}
