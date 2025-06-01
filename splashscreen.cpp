// SplashScreen.cpp
#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget* parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::SplashScreen);
    setAttribute(Qt::WA_TranslucentBackground);

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    // // Logo
    // logoLabel = new QLabel(this);
    // logoLabel->setPixmap(QPixmap(":/resources/logo.png").scaled(128, 128, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    // layout->addWidget(logoLabel);

    // Loading animation
    loadingLabel = new QLabel(this);
    loadingMovie = new QMovie(":/resources/loading.gif");
    loadingLabel->setMovie(loadingMovie);
    layout->addWidget(loadingLabel);

    setLayout(layout);
    resize(124*2, 240); // Optional
}

void SplashScreen::startAnimation() {
    loadingMovie->start();
    show();
}

void SplashScreen::stopAnimation() {
    loadingMovie->stop();
    hide();
}
