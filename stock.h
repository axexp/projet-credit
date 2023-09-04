#ifndef STOCK_H
#define STOCK_H

#include <QDialog>
#include "aide.h"
namespace Ui {
class stock;
}

class stock : public QDialog
{
    Q_OBJECT

public:
    explicit stock(QWidget *parent = nullptr);
    ~stock();

private slots:
    void on_pushButton_10_clicked();
    void on_pushButton_pdf_clicked();
    void on_pushButton_ajout_image_clicked();
    void on_pushButton_notification_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_rechercher_clicked();
    void on_pushButton_statistique_clicked();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_annuler_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_afficher_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    // dans votre classe MainWindow
    void showStockExpiredNotification();
    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::stock *ui;
    aide a;

};

#endif // STOCK_H
