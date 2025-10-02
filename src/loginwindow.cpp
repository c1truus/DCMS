#include "loginwindow.h"
#include "sessionmanager.h"
#include "ui_loginwindow.h"
#include "QMessageBox"
#include "config.h"
LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    socket = new QTcpSocket(this);
    connect(socket,&QTcpSocket::readyRead,this, &LoginWindow::readServerResponse);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
// QString IPAddr = "10.7.132.172";
QString sessionToken;
QString sessionUser;

void LoginWindow::readServerResponse() {
    QString response = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject obj = doc.object();
    if (obj["status"].toString() == "success") {
        QMessageBox::information(this, "Success", "Login successful!");
        sessionToken = obj["token"].toString();
        sessionUser = obj["user"].toString();
        SessionManager::instance().setSession(sessionUser, sessionToken);
        mainWindow = new MainWindow(); // TODO: how to pass the session token and user's info to mainwindow?
        mainWindow->initWindow(sessionUser,sessionToken);
        mainWindow->show();
        this->close(); // Close login window (you can open another window here)
        // qDebug() << "Session token received:" << sessionToken;
    } else {
        QMessageBox::critical(this, "Error", "Invalid credentials!");
        bich("Login failed: " + obj["message"].toString());
    }
}


void LoginWindow::on_loginButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString command = "LOGIN";
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Username and password cannot be empty!");
        return;
    }
    QMap<QString, QString> config = loadConfig("/home/ubuntu/Documents/DCMS-versions/DCMS-v0b/configs/config.txt");
    QString ip = config.value("host", "127.0.0.1");
    QString portStr = config.value("port", "12345");
    quint16 port = portStr.toUShort();

    socket->connectToHost(ip, port);
    // socket->connectToHost(IPAddr,12345); //
    if (socket->waitForConnected(3000)) {
        QString data = command + "," + username + "," + password;
        socket->write(data.toUtf8());
        socket->flush();
    } else {
        QMessageBox::critical(this, "Error", "Failed to connect to server!");
    }
}

void LoginWindow::on_registerButton_clicked()
{
    bich("New user detected");
    registerDialog = new RegisterDialog();
    registerDialog->show();
    this->close();
}
