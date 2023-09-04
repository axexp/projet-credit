#ifndef F_NECESS_H
#define F_NECESS_H

#include <QDialog>
#include "beneficiaire.h"

namespace Ui {
class f_necess;
}

class f_necess : public QDialog
{
    Q_OBJECT

public:
    explicit f_necess(QWidget *parent = nullptr);
    ~f_necess();

private slots:
    void on_pushButton_9_clicked();
    void on_pushButtonsupprimerclient_clicked();
    void on_pushButtonajouter_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButtonrefresh_clicked();

    void on_pushButtonimprimer_clicked();

    void on_pushButtonexportpdf_clicked();

    void on_lineeditnomrech_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_4_clicked();

    void on_pushButtonexportpdf_2_clicked();
    void on_pushButton_10_clicked();
private:
    Ui::f_necess *ui;
    Beneficiaire b;
    QVector<double> Statistique_besoin();
    void makePlot_besoin();
};
#endif // F_NECESS_H
