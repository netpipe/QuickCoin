#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fetchPrice(const QString &cryptoId, const QString &currency);
    void handleNetworkReply();
    void calculateFinalValues();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_coin_activated(const QString &arg1);

    void on_country_activated(const QString &arg1);

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
};

#endif // MAINWINDOW_H
