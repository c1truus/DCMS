#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_buttonBox_accepted()
{
    QString dentist_name = ui->dentistNameLineEdit->text();
    QString dentist_birthdate = ui->dentistBirthdateEdit->text();
    bich("Dentist name is: " + dentist_name);
    bich("Dentist BD is: " + dentist_birthdate);
}


void RegisterDialog::on_buttonBox_rejected()
{
    this->close();
}

