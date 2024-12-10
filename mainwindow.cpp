#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

QString tester;

class CryptoPriceFetcher {
public:
    CryptoPriceFetcher() {
        manager = new QNetworkAccessManager();
    }

    ~CryptoPriceFetcher() {
        delete manager;
    }

    float fetchPrice(const QString &cryptoId, const QString &currency) {
        QString url = QString("https://api.coingecko.com/api/v3/simple/price?ids=%1&vs_currencies=%2")
                          .arg(cryptoId, currency);
        QNetworkRequest request(QUrl(url.toLatin1()));
        qDebug() << url << endl;
             //   QNetworkRequest request(QUrl("https://api.coingecko.com/api/v3/simple/price?ids=%1&vs_currencies=%2"));

        QNetworkReply *reply = manager->get(request);
        manager->connect(reply, &QNetworkReply::finished, [reply]() {
            if (reply->error() == QNetworkReply::NoError) {
                QByteArray response = reply->readAll();
                if (response.isEmpty()) {
                    qDebug() << "Empty response from server.";
                    return;
                }
                qDebug() << "Raw response:" << response;

                QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
                 qDebug() << jsonDoc;

                if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                    QJsonObject jsonObj = jsonDoc.object();

                    // Extract the cryptocurrency price
                    for (const QString &key : jsonObj.keys()) {
                        QJsonObject cryptoData = jsonObj.value(key).toObject();
                        for (const QString &currency : cryptoData.keys()) {
                            qDebug() << "Price of" << key << "in" << currency << ":" << cryptoData.value(currency).toDouble();
                            tester= QString::number(cryptoData.value(currency).toDouble()).toFloat();
                        }
                    }
                } else {
                    qDebug() << "Failed to parse JSON response.";
                }
            } else {
                qDebug() << "Error in reply:" << reply->errorString();
            }

            reply->deleteLater();
        });

    }

private:
    QNetworkAccessManager *manager;
};


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
  //  ui->total->setText(QString::number( ui->newprice->text().toFloat() * ui->ammount->text().toFloat() ));
   // ui->ammount->setText(QString::number(  ui->total->text().toFloat() /ui->newprice->text().toFloat()  ));

     CryptoPriceFetcher fetcher;

     // Fetch prices of cryptocurrencies
     fetcher.fetchPrice("bitcoin", "cad");
    ui->newprice->setText(tester );
    // fetcher.fetchPrice("ethereum", "usd");
    // fetcher.fetchPrice("dogecoin", "usd");

}

void MainWindow::on_pushButton_2_clicked()
{
            ui->ammount->setText(QString::number(  ui->total->text().toFloat() *ui->newprice->text().toFloat()  ));
          ui->profit->setText(QString::number(  ui->ammount->text().toFloat() - ( ui->oldprice->text().toFloat() * ui->total->text().toFloat() )  ));



}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}
