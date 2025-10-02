#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "debugutils.h"
SettingsWindow::SettingsWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
    bich("Hello, your're in Settings");
}
