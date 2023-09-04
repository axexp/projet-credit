#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool validateEmployee(QString name, int id);
private slots:
    void on_login_clicked();
    void uid();
    void onClose();
private:
    Ui::MainWindow *ui;
    Arduino a;
    QByteArray data;
};
#endif // MAINWINDOW_H
