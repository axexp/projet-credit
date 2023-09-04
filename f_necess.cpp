#include "f_necess.h"
#include "ui_f_necess.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include  <QDebug>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include<QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include <QMessageBox>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QSqlError>
#include "qcustomplot.h"
#include "exportexcelobject.h"
#include "beneficiaire.h"
f_necess::f_necess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::f_necess)
{
    ui->setupUi(this);
    ui->tableView->setModel(b.afficher_Beneficiaire());

}

f_necess::~f_necess()
{
    delete ui;
}

void f_necess::on_pushButton_9_clicked()
{
    close();
    MainWindow* mainWin = new MainWindow();
    mainWin->show();
}

void f_necess::on_pushButtonsupprimerclient_clicked()
{
    Beneficiaire b;
    if(ui->lineditid->text()!="")
    {    b.setid(ui->lineditid->text().toInt());
    bool test=b.supprimer_Beneficiaire(b.getid());
    QMessageBox msgBox;

    if(test)
       { msgBox.setText("Suppression avec succes.");
        ui->tableView->setModel(b.afficher_Beneficiaire());

    }
    else
        msgBox.setText("Echec de suppression");
    msgBox.exec();
}
}

void f_necess::on_pushButton_10_clicked()
{
    bool test; QMessageBox msgBox;
        if(ui->lineditid->text()!=""){
        int id=ui->lineditid->text().toInt();
        QString nom=ui->lineeditnom->text();
        QString adresse=ui->linededitadresse->text();
        QString numtel=ui->lineeditnum->text();
        //int besoin=ui->lineeditbesoin->text().toInt();



        Beneficiaire b(id,nom,numtel,adresse); //,besoin
         test=b.modifier_Beneficiaire();

         if(test)
           {  msgBox.setText("Modifier avec succes.");
             ui->tableView->setModel(b.afficher_Beneficiaire());
         }
         else
             msgBox.setText("Echec de modification");}
        else
        msgBox.setText("s'il vous plait remplir les champs à modifier");
         msgBox.exec();
}

void f_necess::on_pushButtonajouter_clicked()
{
    QMessageBox msgBox;
        int id;
        id=ui->lineditid->text().toInt();
        QString nom=ui->lineeditnom->text();
        QString adresse=ui->linededitadresse->text();
        //int  besoin=ui->lineeditbesoin->text().toInt();
        QString numtel=ui->lineeditnum->text();

        Beneficiaire b(id,nom,numtel,adresse); //,besoin

        if(numtel.size()==8)
        {

     bool test=b.ajouter_Beneficiaire();
    if(test)
       {  msgBox.setText("Ajout avec succes.");
         ui->tableView->setModel(b.afficher_Beneficiaire());
     }
     else
         msgBox.setText("Echec d'ajout");
    }
        else msgBox.setText("svp verifier votre numero de telephone");
         msgBox.exec();
}

void f_necess::on_tableView_activated(const QModelIndex &index)
{
    QString val;QSqlQuery query;


        val=ui->tableView->model()->data(index).toString();
       int  x=ui->tableView->model()->data(index).toInt();

         query.prepare("select * from beneficiaire where id=:x or nom =:val or adresse=:val or numtel=:val or besoin=:x  ");
         query.bindValue(":val",val);
         query.bindValue(":x",x);

         if (query.exec())
         {
             while (query.next())
             {
                 ui->lineditid->setText(query.value(0).toString());
                 ui->lineeditnom->setText(query.value(1).toString());
                 ui->lineeditnum->setText(query.value(2).toString());
                 ui->linededitadresse->setText(query.value(3).toString());
                 //ui->lineeditbesoin->setText(query.value(4).toString());



             }
         }
         else
         {
             QMessageBox::critical(this ,tr("error::"),query.lastError().text());
         }
}

void f_necess::on_pushButtonrefresh_clicked()
{
    ui->tableView->setModel(b.afficher_Beneficiaire());
}

void f_necess::on_pushButtonimprimer_clicked()
{

    QPrinter printer;

        printer.setPrinterName("desiered printer name");

      QPrintDialog dialog(&printer,this);

        if(dialog.exec()== QDialog::Rejected)
            return;
}

void f_necess::on_pushButtonexportpdf_clicked()
{
    QString strStream;
                     QTextStream out(&strStream);

                     const int rowCount = ui->tableView->model()->rowCount();
                     const int columnCount = ui->tableView->model()->columnCount();

                     out <<  "<html>\n"
                         "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                         "<center> <H1>Liste des Beneficiares </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableView->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView->isColumnHidden(column)) {
                                 QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);
                 printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
               printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);
                 doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                 doc.print(&printer);

}

void f_necess::on_lineeditnomrech_cursorPositionChanged(int arg1, int arg2)
{

    Beneficiaire B;
                QString inputValue,filterChecked;
                inputValue=ui->lineeditnomrech->text();
                ui->tableView->setModel(B.rechercherdynamique(inputValue,"nom"));
}
QVector<double> f_necess::Statistique_besoin()
{
    QSqlQuery q;
    QVector<double> stat(5);
    stat[0]=0;
    stat[1]=0;
    stat[2]=0;
    stat[3]=0;
    stat[4]=0;
    q.prepare("SELECT besoin FROM beneficiaire WHERE besoin<=100");
    q.exec();
    while (q.next())
    {
        stat[0]++;
    }
    q.prepare("SELECT besoin FROM beneficiaire WHERE 100<besoin and besoin<=200");
    q.exec();
    while (q.next())
    {
        stat[1]++;
    }
    q.prepare("SELECT besoin FROM beneficiaire WHERE 200<besoin and besoin<=300");
    q.exec();
    while (q.next())
    {
        stat[2]++;
    }
    q.prepare("SELECT besoin FROM beneficiaire WHERE 300<besoin and besoin<=400");
    q.exec();
    while (q.next())
    {
        stat[3]++;
    }
    q.prepare("SELECT besoin FROM beneficiaire WHERE 400<besoin ");
    q.exec();
    while (q.next())
    {
        stat[4]++;
    }
    return stat;
}
void f_necess::makePlot_besoin()
{
    // prepare data:
    QVector<double> x3(5), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, f_necess::Statistique_besoin());
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(200, 40, 60, 170));
    ui->customPlot->replot();


    // move bars above graphs and grid below bars:
    ui->customPlot->addLayer("abovemain", ui->customPlot->layer("main"), QCustomPlot::limAbove);
    ui->customPlot->addLayer("belowmain", ui->customPlot->layer("main"), QCustomPlot::limBelow);
    ui->customPlot->xAxis->grid()->setLayer("belowmain");
    ui->customPlot->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
    Ticks<<1<<2<<3<<4<<5<<6;
    QVector<QString> labels;
    labels<<"0-100"<<"100-200"<<"200-300"<<"300-400"<<"400-500";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0,4);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(10, 50, 80));
    plotGradient.setColorAt(1, QColor(10, 20, 50));
    ui->customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 80));
    axisRectGradient.setColorAt(1, QColor(0, 0, 30));
    ui->customPlot->axisRect()->setBackground(axisRectGradient);

    ui->customPlot->rescaleAxes();
    ui->customPlot->xAxis->setRange(0, 7);
    ui->customPlot->yAxis->setRange(0, 10);


}
void f_necess::on_pushButton_4_clicked()
{
    f_necess::makePlot_besoin();

}

void f_necess::on_pushButtonexportpdf_2_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                           tr("Excel Files (*.xls)"));
           if (fileName.isEmpty())
               return;

           ExportExcelObject obj(fileName, "mydata", ui->tableView);

           //colums to export
           obj.addField(0, "IDENTIFIANT", "char(20)");
            obj.addField(1, "Nom", "char(20)");
             obj.addField(2, "NUMERO_DE_TELEPHONE", "char(20)");
           obj.addField(3, "ADRESSE", "char(20)");
           //obj.addField(4, "BESOIN", "char(20)");



           int retVal = obj.export2Excel();
           if( retVal > 0)
           {
               QMessageBox::information(this, tr("Done"),
                                        QString(tr("%1 records exported!")).arg(retVal)
                                        );
   }
}

