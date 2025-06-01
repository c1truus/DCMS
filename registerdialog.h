#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "debugutils.h"
#include <QDialog>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
