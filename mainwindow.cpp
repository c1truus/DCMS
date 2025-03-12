#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "sessionmanager.h"
#include <QMouseEvent>
#include <QShortcut>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readServerResponse);
    setupShortcuts();
    QString user = SessionManager::instance().getUsername();
    QString token = SessionManager::instance().getSessionToken();
    qDebug() << "Current User:" << user;
    qDebug() << "Session Token:" << token;

    // Ensure the ToolButton resizes dynamically based on the username
    ui->toolButton->setText(user);
    ui->toolButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initWindow(QString sessionUser, QString sessionToken) {
    if (socket->state() != QAbstractSocket::ConnectedState) {
        socket->connectToHost("10.194.50.223", 12345); // BIT
        // socket->connectToHost("192.168.1.96", 12345); // USTB

    }

    if (socket->waitForConnected(3000)) {
        QString command = "FETCH";
        QString data = command + "," + sessionUser + "," + sessionToken;

        socket->write(data.toUtf8());
        socket->flush();
    } else {
        QMessageBox::critical(this, "Error", "Failed to connect to server!");
    }
    ui->userInfoPopup->hide();
    qDebug() << "Main window initialized";
}

void MainWindow::readServerResponse() {
    QString response = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject obj = doc.object();

    if (obj.contains("status") && obj["status"] == "success") {
        QStringList dentistInfo = obj["dentist_info"].toVariant().toStringList();

        if (!dentistInfo.isEmpty()) {
            ui->toolButton->setText(dentistInfo.at(2)); // Name as button text
            qDebug() << "Dentist Info: " << dentistInfo.join(", ");
            fillInfoTable(dentistInfo);
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to fetch data: " + obj["message"].toString());
    }
}

void MainWindow::fillInfoTable(QStringList dentistInfo) {
    ui->nameLabel->setText(dentistInfo.at(2));
    ui->birthdateLabel->setText(dentistInfo.at(3));
    ui->genderLabel->setText(dentistInfo.at(4));
    ui->phoneLabel->setText(dentistInfo.at(5));
    ui->emailLabel->setText(dentistInfo.at(6));
    ui->roleLabel->setText(dentistInfo.at(7));
}

void MainWindow::on_logoutButton_clicked() {
    SessionManager::instance().clearSession();
    this->close();
}
void MainWindow::on_logoutButton_2_clicked() {
    SessionManager::instance().clearSession();
    this->close();
}
void MainWindow::on_toolButton_clicked() {
    if (ui->userInfoPopup->isVisible()) {
        ui->userInfoPopup->hide();
        return;
    }
    ui->userInfoPopup->show();
}


void MainWindow::on_editInfoButton_clicked(){
    this->close();

}
void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (ui->userInfoPopup->isVisible()) {
        QRect popupRect = ui->userInfoPopup->geometry();
        popupRect.moveTo(ui->userInfoPopup->mapToGlobal(QPoint(0, 0)));
        if (!popupRect.contains(event->globalPos())) {
            ui->userInfoPopup->hide();
        }
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::setupShortcuts() {
    // Ctrl + W to close the newest window
    QShortcut *closeWindowShortcut = new QShortcut(QKeySequence("Ctrl+W"), this);
    connect(closeWindowShortcut, &QShortcut::activated, this, &MainWindow::closeNewestWindow);

    // Ctrl + Q to quit the application
    QShortcut *quitAppShortcut = new QShortcut(QKeySequence("Ctrl+Q"), this);
    connect(quitAppShortcut, &QShortcut::activated, qApp, &QApplication::quit);

    // Ctrl + , to open Settings
    QShortcut *openSettingsShortcut = new QShortcut(QKeySequence("Ctrl+,"), this);
    connect(openSettingsShortcut, &QShortcut::activated, this, &MainWindow::openSettings);
}

// Function to close the newest (topmost) window
void MainWindow::closeNewestWindow() {
    QMessageBox::question(this,"Warning!","Quit application?");
    if (!QApplication::topLevelWidgets().isEmpty()) {
        QWidget *topWindow = QApplication::topLevelWidgets().last();
        if (topWindow != this) { // Don't close the main window
            topWindow->close();

        }
    }
}

// Function to open settings window
void MainWindow::openSettings() {
    
    QMessageBox::information(this, "Settings", "Settings window will be opened here.");
     

    // Replace with actual settings window logic when available
}
