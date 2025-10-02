#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

// class SplashScreen
// {
// public:
//     SplashScreen();
// };

// SplashScreen.h
#pragma once

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>

class SplashScreen : public QWidget {
    Q_OBJECT
public:
    SplashScreen(QWidget* parent = nullptr);
    void startAnimation();
    void stopAnimation();

private:
    QLabel* logoLabel;
    QLabel* loadingLabel;
    QMovie* loadingMovie;
};


#endif // SPLASHSCREEN_H
