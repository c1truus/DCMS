#include "loginwindow.h"
#include "splashscreen.h"
#include <QApplication>
#include "QFile"
#include "QTimer"
#include "QIcon"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //SplashScreen splash;
    //splash.startAnimation();
    QFile styleFile(":/styles/styles.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleFile.readAll());
    a.setStyleSheet(styleSheet);
    a.setWindowIcon(QIcon(":/resources/icon.png"));
    LoginWindow w;
    // w.show();
    QTimer::singleShot(5000, [&]() {
        //splash.stopAnimation();
        w.show();
    });
    return a.exec();
}
