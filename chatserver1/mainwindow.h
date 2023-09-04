#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatserver.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
             class chatserver;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addMessage(QString Msg);
    chatserver* m_pBoxServer;

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
