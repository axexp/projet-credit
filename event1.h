#ifndef EVENT1_H
#define EVENT1_H

#include <QDialog>
#include "evenement.h"
namespace Ui {
class event1;
}

class event1 : public QDialog
{
    Q_OBJECT

public:
    explicit event1(QWidget *parent = nullptr);
    ~event1();

private slots:
    void on_tab_evenement_doubleClicked(const QModelIndex &index);

    void on_pushButton_9_clicked();

    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_clicked();

    void on_pb_tri_2_clicked();

    void on_le_chercher_textEdited(const QString &arg1);    
private:
    Ui::event1 *ui;
    evenement e;
};

#endif // EVENT1_H
