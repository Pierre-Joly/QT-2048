#include "losedialog.h"
#include "ui_losedialog.h"

LoseDialog::LoseDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LoseDialog)
{
    ui->setupUi(this);
    connect(ui->okLoseButton, &QPushButton::clicked, this, &LoseDialog::accept);
}

LoseDialog::~LoseDialog()
{
    delete ui;
}

void LoseDialog::accept()
{
    QDialog::accept();
    emit accepted();
}
