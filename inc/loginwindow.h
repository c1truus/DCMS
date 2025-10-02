#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <QTcpSocket>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include "mainwindow.h"
#include "registerdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void readServerResponse();
    void on_registerButton_clicked();

private:
    Ui::LoginWindow *ui;
    MainWindow *mainWindow;
    RegisterDialog *registerDialog;
    QTcpSocket *socket;
};
#endif // LOGINWINDOW_H
