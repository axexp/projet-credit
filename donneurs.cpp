#include "donneurs.h"
#include "connection.h"
#include <QStandardItemModel>
#include <QtDebug>
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QtSql>
#include <QSqlRecord>
#include <QSqlField>
#include <QPdfWriter>
#include <QPainter>
#include <QTableWidget>
#include <QTableView>
#include<QTextDocument>
#include <fstream>
#include <iostream>
#include<QDesktopServices>
#include <QtNetwork>
#include <QCoreApplication>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QUrl>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtCore>
#include <QApplication>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkReply>
//C:\Users\ahmed\OneDrive\Desktop\projetint
#include "C:/Users/ahmed/OneDrive/Desktop/projetint/SmtpClient-for-Qt-2.0/src/SmtpMime"
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "qrcodegen.hpp"
#include <QImage>
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <iostream>
#include <QSqlError>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include<QtCharts/QChart>
#include<QtCharts/QPieSeries>
#include<QtCharts/QPieSlice>
#include<QGradient>
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QImage>
#include <QRectF>
using namespace std;
QString donneurs1::get_nom() {return nom_donneur;}
QString donneurs1::get_adresse() {return adresse_donneur;}
QString donneurs1::get_mail() {return mail;}
int donneurs1::get_tlph() {return telephone;}
int donneurs1::get_id() {return id_donneur;}

void donneurs1::setnom(QString n) {nom_donneur=n;}
void donneurs1::setadresse(QString n) {adresse_donneur=n;}
void donneurs1::setmail(QString n) {mail=n;}
void donneurs1::settlph(int n) {this->telephone=n;}
void donneurs1::setid(int n) {this->telephone=n;}

donneurs1::donneurs1()
{
    id_donneur=0;
    nom_donneur="";
    adresse_donneur="";
    mail="";
    telephone=0;
}
donneurs1::donneurs1(QString nom_donneur ,QString adresse_donneur ,QString mail ,int telephone,QString QR)
{
    this->nom_donneur=nom_donneur;
    this->adresse_donneur=adresse_donneur;
    this->mail=mail;
    this->telephone=telephone;
    this->QR=QR;
}
bool donneurs1::ajouter()
{
    QSqlQuery query1;
    QString res1 = QString::number(telephone);
    query1.prepare("INSERT INTO donneurs (nom_donneur, adresse_donneur, mail, telephone,QR)"
                   "VALUES(:nom_donneur, :adresse_donneur, :mail, :telephone,:QR)");
    query1.bindValue(":nom_donneur", nom_donneur);
    query1.bindValue(":adresse_donneur", adresse_donneur);
    query1.bindValue(":mail", mail);
    query1.bindValue(":telephone", res1);
    query1.bindValue(":QR", QR);

    return query1.exec();
}
QSqlQueryModel * donneurs1::afficher()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("select * from donneurs");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

return model;
}
bool donneurs1::supprimer(int id)
{
QSqlQuery query;
QString res=QString::number(id);
query.prepare("Delete from donneurs where id_donneur= :id_donneur");
query.bindValue(":id_donneur",res);
return query.exec();
}
bool donneurs1::modifier(int id,QString n,QString ad,QString ma,int tlp,QString QR)
{
    QSqlQuery query;
    QString res1=QString::number(id);
    QString res2=QString::number(tlp);
    query.prepare("update donneurs set nom_donneur='"+n+"', adresse_donneur='"+ad+"', mail='"+ma+"', telephone='"+res2+"',QR = '"+QR+"' where id_donneur='"+res1+"'");
    return query.exec();
}
void deleteqrcode(QString nom)
{
    const QString fileName = "C:/Users/ahmed/OneDrive/Desktop/projetint/QR/" + nom + ".png";
    QFile file(fileName);
    file.remove();
}
QSqlQueryModel * donneurs1::odreascendantid()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("SELECT * FROM donneurs ORDER BY id_donneur ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

return model;
}
QSqlQueryModel * donneurs1::odredescendantid()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("SELECT * FROM donneurs ORDER BY id_donneur DESC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

return model;
}
QSqlQueryModel * donneurs1::odreAlphabetiqueAZ()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("SELECT * FROM donneurs ORDER BY LOWER(nom_donneur) ASC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

return model;
}
QSqlQueryModel * donneurs1::odreAlphabetiqueZA()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("SELECT * FROM donneurs ORDER BY LOWER(nom_donneur) DESC");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

return model;
}
QSqlQueryModel * donneurs1::email()
{
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("SELECT * FROM donneurs ORDER BY CASE "
                "WHEN mail LIKE '%gmail%' THEN 1 "
                "WHEN mail LIKE '%esprit%' THEN 2"
                "WHEN mail LIKE '%hotmail%' THEN 3 "
                "WHEN mail LIKE '%outlook%' THEN 4 "
                "WHEN mail LIKE '%yahoo%' THEN 5 "
                "ELSE 6 END");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

return model;
}
QSqlQueryModel * donneurs1::region()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM donneurs ORDER BY CASE "
                                                           "WHEN lower(adresse_donneur) LIKE '%ariana' THEN 1 "
                                                           "WHEN lower(adresse_donneur) LIKE '%beja' THEN 2"
                                                           "WHEN lower(adresse_donneur) LIKE '%ben arous' THEN 3 "
                                                           "WHEN lower(adresse_donneur) LIKE '%bizerte' THEN 4 "
                                                           "WHEN lower(adresse_donneur) LIKE '%gabes' THEN 5 "
                                                           "WHEN lower(adresse_donneur) LIKE '%gafsa' THEN 6 "
                                                           "WHEN lower(adresse_donneur) LIKE '%jendouba' THEN 7 "
                                                           "WHEN lower(adresse_donneur) LIKE '%kairaouan' THEN 8 "
                                                           "WHEN lower(adresse_donneur) LIKE '%kasserine' THEN 9 "
                                                           "WHEN lower(adresse_donneur) LIKE '%kelibia' THEN 10 "
                                                           "WHEN lower(adresse_donneur) LIKE '%kef' THEN 11 "
                                                           "WHEN lower(adresse_donneur) LIKE '%mahdia' THEN 12 "
                                                           "WHEN lower(adresse_donneur) LIKE '%manouba' THEN 13 "
                                                           "WHEN lower(adresse_donneur) LIKE '%medenine' THEN 14 "
                                                           "WHEN lower(adresse_donneur) LIKE '%monastir' THEN 15 "
                                                           "WHEN lower(adresse_donneur) LIKE '%nabeul' THEN 16 "
                                                           "WHEN lower(adresse_donneur) LIKE '%sfax' THEN 17 "
                                                           "WHEN lower(adresse_donneur) LIKE '%sidi bouzid' THEN 18 "
                                                           "WHEN lower(adresse_donneur) LIKE '%siliana' THEN 19 "
                                                           "WHEN lower(adresse_donneur) LIKE '%sousse' THEN 20 "
                                                           "WHEN lower(adresse_donneur) LIKE '%tataouine' THEN 21 "
                                                           "WHEN lower(adresse_donneur) LIKE '%tozeur' THEN 22 "
                                                           "WHEN lower(adresse_donneur) LIKE '%tunis' THEN 23 "
                                                           "WHEN lower(adresse_donneur) LIKE '%zaghouan' THEN 24 END");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

    return model;
}
bool donneurs1::mailvalide(const QString& chaine) {
    QRegularExpression regex("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    QRegularExpressionMatch match = regex.match(chaine);
    return match.hasMatch();
}
int donneurs1::chiffres(int nombre) {
    int compteur = 0;
    if (nombre == 0) {
        return 1;
    }
    while (nombre != 0) {
        nombre /= 10;
        compteur++;
    }
    return compteur;
}
bool donneurs1::existenceM(QString value)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM donneurs WHERE mail= :value");
    query.bindValue(":value", value);

    if (!query.exec()) {
        qWarning() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }
    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}
bool donneurs1::existenceN(QString value)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM donneurs WHERE nom_donneur= :value");
    query.bindValue(":value", value);

    if (!query.exec()) {
        qWarning() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }
    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}
bool donneurs1::existenceTL(int val)
{
    QSqlQuery query;
    QString res=QString::number(val);
    query.prepare("SELECT COUNT(*) FROM donneurs WHERE telephone= :value");
    query.bindValue(":value", val);
    if (!query.exec()) {
        qWarning() << "Erreur lors de l'exécution de la requête :" << query.lastError().text();
        return false;
    }
    query.next();
    int count = query.value(0).toInt();
    return count > 0;
}
bool donneurs1::nonvide(QString i)
{
    if (i.isEmpty()) {
        return false;
    }
    QChar premierCaractere = i.at(0);
    if (premierCaractere.isSpace()) {
        return false;
    }
    return true;
}
bool verifierAdresse(QString adresse) {
    QStringList etatsTunisie = {"Ariana", "Beja", "Ben Arous", "Bizerte", "Gabes", "Gafsa", "Jendouba", "Kairouan", "Kasserine", "Kelibia", "Kef", "Mahdia", "Manouba", "Medenine", "Monastir", "Nabeul", "Sfax", "Sidi Bouzid", "Siliana", "Sousse", "Tataouine", "Tozeur", "Tunis", "Zaghouan"};
    QString etat;
    foreach(etat, etatsTunisie) {
        if(adresse.toLower().endsWith(etat.toLower())) {
            return true;
        }
    }
    return false;
}
void donneurs1::pdf()
{
    QSqlQuery query;
    query.exec("SELECT id_donneur, nom_donneur, adresse_donneur, mail, telephone, QR FROM donneurs");
    QPdfWriter writer("C:/Users/ahmed/OneDrive/Desktop/projetint/Donneurs.pdf");
    QTextDocument document;
    QString path = "C:/Users/ahmed/OneDrive/Desktop/projetint/logo noir.png";
    QString logo = "<div style='text-align:right;'><a href='file:///" + path + "'><img src='file:///" + path + "' width='150' height='150'></a></div>";
    QString title = "<div style='text-align:center;'><h1 style='color:#00BFFF'>HESTIA Tunisie</h1></div>"; //Ajout du titre
    QString title2 = "<h2 style='color:black; text-align:center;'>Liste des donneurs</h2>"; //Ajout du titre
    QString table = "<table border='1'><tr><th>Identifiant</th><th>Nom</th><th>Adresse</th><th>Adresse Mail</th><th>Téléphone</th><th>QR Code</th></tr>";
    while (query.next()) {
        int id_donneur = query.value(0).toInt();
        QString nom_donneur = query.value(1).toString();
        QString adresse_donneur = query.value(2).toString();
        QString mail = query.value(3).toString();
        int telephone = query.value(4).toInt();
        QString QR_path = query.value(5).toString();
        QString QR = "<a href='file:///" + QR_path + "'><img src='file:///" + QR_path + "' width='100' height='100'></a>";
        table += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td></tr>").arg(id_donneur).arg(nom_donneur).arg(adresse_donneur).arg(mail).arg(telephone).arg(QR);
    }
    table += "</table>";
    document.setHtml(logo + title + title2 + table);
    document.setDefaultStyleSheet("div { margin-top: 50px; }"); // Ajouter une marge supérieure pour le logo
    document.print(&writer);
    QString file_path = "C:/Users/ahmed/OneDrive/Desktop/projetint/Donneurs.pdf";
    QDesktopServices::openUrl(QUrl::fromLocalFile(file_path));
}
QSqlQueryModel * donneurs1::chercherElementParNom(QString nom)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString query = "SELECT * FROM donneurs WHERE UPPER(nom_donneur) LIKE UPPER('" + nom + "%') OR UPPER(id_donneur) LIKE UPPER('" + nom + "%')";
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Adresse mail"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Numéro du téléphone"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Code QR"));

    return model;
}
void generateQRCode(QString nom_donneur,QString adresse_donneur,QString mail,int telephone)
{
    const QString data = QString("%1\n%2\n%3\n%4\n").arg(nom_donneur).arg(adresse_donneur).arg(mail).arg(telephone);
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(data.toUtf8().constData(), qrcodegen::QrCode::Ecc::HIGH);
      const int border = 10;
         const int scale = 15;
         int s = qr.getSize() * scale + border * 2;
         QImage img(s, s, QImage::Format_ARGB32_Premultiplied);
         img.fill(Qt::white);
         QPainter painter(&img);
         painter.setPen(Qt::NoPen);
         painter.setBrush(Qt::black);
         for (int x = 0; x < qr.getSize(); x++) {
             for (int y = 0; y < qr.getSize(); y++) {
                 if (qr.getModule(x, y)) {
                     QRectF r((x * scale) + border, (y * scale) + border, scale, scale);
                     painter.drawRects(&r, 1);
                 }
             }
         }
         const QString fileName = "C:/Users/ahmed/OneDrive/Desktop/projetint/QR/" + nom_donneur + ".png";
    img.save(fileName, "PNG");
}
void statistiques()
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE mail LIKE '%@gmail.com'");
       query.exec();
       query.next();
       int gmailCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE mail LIKE '%@yahoo.fr'");
       query.exec();
       query.next();
       int yahooCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE mail LIKE '%@hotmail.com'");
       query.exec();
       query.next();
       int hotmailCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE mail LIKE '%@esprit.tn'");
       query.exec();
       query.next();
       int espritCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE mail NOT LIKE '%@gmail.com' AND mail NOT LIKE '%@yahoo.fr' AND mail NOT LIKE '%@hotmail.com' AND mail NOT LIKE '%@esprit.tn'");
           query.exec();
           query.next();
           int autresCount = query.value(0).toInt();
       QtCharts::QBarSet *set = new  QtCharts::QBarSet("Adresses email");
       *set << gmailCount << yahooCount << hotmailCount << espritCount <<autresCount;
        QtCharts::QBarSeries *series = new  QtCharts::QBarSeries();
       series->append(set);
        QtCharts::QChart *chart = new  QtCharts::QChart();
       chart->addSeries(series);
       chart->setTitle("Statistiques des adresses email");
       chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
       QStringList categories;
       categories << "@gmail.com" << "@yahoo.fr" << "@hotmail.com" << "@esprit.tn"<<"autres";
        QtCharts::QBarCategoryAxis *axis = new  QtCharts::QBarCategoryAxis();
       axis->append(categories);
       chart->createDefaultAxes();
       chart->setAxisX(axis, series);
       QtCharts::QChartView *chartView = new  QtCharts::QChartView(chart);
       chart->setTheme(QtCharts::QChart::ChartThemeBlueCerulean);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->resize(800, 600);
       chartView->show();
}
void statistiques2()
{
    QSqlQuery query;
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%ariana'");
       query.exec();
       query.next();
       int arianaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%beja'");
       query.exec();
       query.next();
       int bejaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%bizerte'");
       query.exec();
       query.next();
       int bizerteCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%ben arous'");
       query.exec();
       query.next();
       int benarousCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%gabes'");
       query.exec();
       query.next();
       int gabesCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%gafsa'");
       query.exec();
       query.next();
       int gafsaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%jendouba'");
       query.exec();
       query.next();
       int jendoubaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%kairouan'");
       query.exec();
       query.next();
       int kairouanCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%kasserine'");
       query.exec();
       query.next();
       int kasserineCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%kelibia'");
       query.exec();
       query.next();
       int kelibiaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%kef'");
       query.exec();
       query.next();
       int kefCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%mahdia'");
       query.exec();
       query.next();
       int mahdiaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%medenine'");
       query.exec();
       query.next();
       int medenineCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%manouba'");
       query.exec();
       query.next();
       int manoubaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%monastir'");
       query.exec();
       query.next();
       int monastirCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%nabeul'");
       query.exec();
       query.next();
       int nabeulCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%sfax'");
       query.exec();
       query.next();
       int sfaxCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%sidi bouzid'");
       query.exec();
       query.next();
       int sidibouzidCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%siliana'");
       query.exec();
       query.next();
       int silianaCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%sousse'");
       query.exec();
       query.next();
       int sousseCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%tataouine'");
       query.exec();
       query.next();
       int tataouineCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%tozeur'");
       query.exec();
       query.next();
       int tozeurCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%tunis'");
       query.exec();
       query.next();
       int tunisCount = query.value(0).toInt();
       query.prepare("SELECT COUNT(*) FROM donneurs WHERE lower(adresse_donneur) LIKE '%zaghouan'");
       query.exec();
       query.next();
       int zaghouanCount = query.value(0).toInt();
       QtCharts::QBarSet *set = new  QtCharts::QBarSet("Régions");
       *set << arianaCount<< bejaCount << bizerteCount << benarousCount <<gabesCount<<gafsaCount<<jendoubaCount<<kairouanCount<<kasserineCount<< kelibiaCount << kefCount << mahdiaCount <<manoubaCount<<medenineCount<<monastirCount<<nabeulCount<<sfaxCount<<sidibouzidCount<<silianaCount<<sousseCount<<tataouineCount<<tozeurCount<<tunisCount<<zaghouanCount;
        QtCharts::QBarSeries *series = new  QtCharts::QBarSeries();
       series->append(set);
        QtCharts::QChart *chart = new  QtCharts::QChart();
       chart->addSeries(series);
       chart->setTitle("Nombre des donneurs par région");
       chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
       QStringList categories;
       categories << "Ariana" << "Beja" << "Ben Arous" << "Bizerte"<<"Gabès"<<"Gafsa"<<"Jendouba"<<"Kairouan"<<"Kasserinr"<<"Kelibia"<<"Kef"<<"Mahdia"<<"Manouba"<<"Medenine"<<"Monastir"<<"Nabeul"<<"Sfax"<<"Sidi Bouzid"<<"Siliana"<<"Sousse"<<"Tataouine"<<"Tozeur"<<"Tunis"<<"Zaghouan";
        QtCharts::QBarCategoryAxis *axis = new  QtCharts::QBarCategoryAxis();
       axis->append(categories);
       chart->createDefaultAxes();
       chart->setAxisX(axis, series);
       QtCharts::QChartView *chartView = new  QtCharts::QChartView(chart);
       chart->setTheme(QtCharts::QChart::ChartThemeBlueCerulean);
       chartView->setRenderHint(QPainter::Antialiasing);
       chartView->resize(1500, 1000);
       chartView->show();
}
void supprimerFichier(QString nomFichier) {
    QFile fichier(nomFichier);

    if (fichier.remove()) {
        qDebug() << "Le fichier a été supprimé avec succès";
    } else {
        qDebug() << "Une erreur s'est produite lors de la suppression du fichier";
    }
}
