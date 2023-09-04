#ifndef EMP_H
#define EMP_H

#include <QDialog>
#include "emp2.h"

#include <QtCharts>
#include <QPieSeries>
#include <QChartView>
#include <QChart>
#include <QtCharts/QChart>

namespace Ui {
class emp;
}

class emp : public QDialog
{
    Q_OBJECT

public:
    explicit emp(QWidget *parent = nullptr);
    ~emp();
    void showStatistics(QWidget *parent, QChartView *chartView);
    void uid();
private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_valider_clicked();

    void on_modifier_clicked();

    void on_pushButton_7_clicked();

    void on_recherche_textChanged();

    void on_ordre_tri_currentTextChanged();

    void on_stat_clicked();    

    void on_pushButton_10_clicked();

private:
    Ui::emp *ui;
    emp2 Emp;

};

#endif // EMP_H
