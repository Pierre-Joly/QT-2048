#include "windialog.h"
#include "ui_windialog.h"

WinDialog::WinDialog(QWidget *parent) : QDialog(parent), ui(new Ui::WinDialog)
{
    ui->setupUi(this);
    connect(ui->okWinButton, &QPushButton::clicked, this, &WinDialog::accept);
}

WinDialog::~WinDialog()
{
    delete ui;
}

void WinDialog::accept()
{
    QDialog::accept();
    emit accepted();
}
