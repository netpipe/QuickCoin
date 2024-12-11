#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), manager(new QNetworkAccessManager(this)) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fetchPrice(const QString &cryptoId, const QString &currency) {

    QString cryptoId2 = ui->cointxt->text().toLatin1();
QString currency2 = ui->countrytxt->text().toLatin1();
    QString url = QString("https://api.coingecko.com/api/v3/simple/price?ids=%1&vs_currencies=%2")
                      .arg(cryptoId2, currency2);
    qDebug() << "Requesting URL:" << url;

    QNetworkRequest request(QUrl(url.toLatin1()));
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, &MainWindow::handleNetworkReply);
}

void MainWindow::handleNetworkReply() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        qDebug() << "Raw Response:" << response;

        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();

            for (const QString &key : jsonObj.keys()) {
                QJsonObject cryptoData = jsonObj.value(key).toObject();
                for (const QString &currency : cryptoData.keys()) {
                    double price = cryptoData.value(currency).toDouble();
                    qDebug() << "Price of" << key << "in" << currency << ":" << price;

                    // Update the newprice field in the UI
                    ui->newprice->setText(QString::number(price, 'f', 10 ));

                    // Recalculate values based on the new price
                    calculateFinalValues();
                }
            }
        } else {
            qDebug() << "Failed to parse JSON response.";
        }
    } else {
        qDebug() << "Network Error:" << reply->errorString();
    }

    reply->deleteLater();
}

void MainWindow::calculateFinalValues() {
    // Calculate ammount
    float total = ui->total->text().toFloat();
    float newPrice = ui->newprice->text().toFloat();
    float oldPrice = ui->oldprice->text().toFloat();

    float ammount = total * newPrice;
    float profit = ammount - (oldPrice * total);

    // Update the UI
    ui->ammount->setText(QString::number(ammount));
    ui->profit->setText(QString::number(profit));

    qDebug() << "Ammount:" << ammount << "Profit:" << profit;
}

void MainWindow::on_pushButton_clicked()
{

    // Fetch prices of cryptocurrencies
    fetchPrice("bitcoin", "usd");
}


void MainWindow::on_pushButton_2_clicked()
{
    calculateFinalValues();
}


void MainWindow::on_coin_activated(const QString &arg1)
{
    ui->cointxt->setText( ui->coin->currentText().toLatin1());
//QString currency2
}


void MainWindow::on_country_activated(const QString &arg1)
{
     ui->countrytxt->setText( ui->country->currentText().toLatin1());
}

