#ifndef DONNEUR_H
#define DONNEUR_H

#include <QDialog>
#include "donneurs.h"
#include <QMainWindow>
#include "connection.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Donneur; }
QT_END_NAMESPACE

class Donneur : public QDialog
{
    Q_OBJECT

public:
    Donneur(QWidget *parent = nullptr);
    ~Donneur();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_annuler_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_supprimer_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_pushButton_pdf_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_lineEdit_chercher_textEdited(const QString &arg1);
    void on_pushButton_stat_clicked();

    void on_pushButton_11_clicked();

private:
    donneurs1 Etmp;
    Connection d;
    Ui::Donneur *ui;
};
#endif // DONNEUR_H
