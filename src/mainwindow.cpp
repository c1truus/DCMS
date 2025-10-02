#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sessionmanager.h"
#include "debugutils.h"
#include "config.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QShortcut>
#include <QKeySequence>
#include <QListWidget>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readServerResponse);
    setupShortcuts();
    loadStylesheet();
    QString user = SessionManager::instance().getUsername();
    QString token = SessionManager::instance().getSessionToken();
    bich("Current user: " + user);
    bich("Session Token: " + token);
    // Ensure the ToolButton resizes dynamically based on the username
    ui->toolButton->setText(user);
    ui->toolButton->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    QDockWidget *sidebar = new QDockWidget("Menu", this);
    sidebar->setWidget(new QListWidget);
    addDockWidget(Qt::LeftDockWidgetArea, sidebar);
}

MainWindow::~MainWindow() {
    delete ui;
}

// QString IPAddress = "10.7.132.172";

void MainWindow::initWindow(QString sessionUser, QString sessionToken) {
    if (socket->state() != QAbstractSocket::ConnectedState) {
        QMap<QString, QString> config = loadConfig("/home/ubuntu/Documents/DCMS-versions/DCMS-v0b/configs/config.txt");
        QString ip = config.value("host", "127.0.0.1");
        QString portStr = config.value("port", "12345");
        quint16 port = portStr.toUShort();

        socket->connectToHost(ip, port);
        // socket->connectToHost(IPAddress, 12345);
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
    bich("main window initiliazed");
}

void MainWindow::readServerResponse() {
    QString response = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
    QJsonObject obj = doc.object();

    if (obj.contains("status") && obj["status"] == "success") {
        QStringList dentistInfo = obj["dentist_info"].toVariant().toStringList();

        if (!dentistInfo.isEmpty()) {
            ui->toolButton->setText(dentistInfo.at(2)); // Name as button text
            bich("Dentist info: " + dentistInfo.join(", "));
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

void MainWindow::loadStylesheet() {
    QFile file(":/styles/styles.qss");
    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(styleSheet);
        bich("QSS opened");
    }
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

    QShortcut *reloadShortcut = new QShortcut(QKeySequence("Ctrl+R"), this);
    connect(reloadShortcut, &QShortcut::activated, this, &MainWindow::loadStylesheet);
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
