#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTcpSocket>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initWindow(const QString sessionUser, const QString sessionToken);
    void fillInfoTable(const QStringList dentistInfo);

    void setupShortcuts();
    void closeNewestWindow();
    void openSettings();
    void loadStylesheet();
protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void readServerResponse();
    void on_logoutButton_clicked();
    void on_logoutButton_2_clicked();
    void on_editInfoButton_clicked();
    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
