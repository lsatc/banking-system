#include "dialog_pardakht.h"
#include "ui_dialog_pardakht.h"

Dialog_pardakht::Dialog_pardakht(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_pardakht)
{
    ui->setupUi(this);
     ui->buttonBox->setStyleSheet("background-color: #00ffff");
     ui->Discard_btn->setStyleSheet("background-color: #212121");
    //ui->buttonBox->setStyleSheet("background-color: #212121");
}

Dialog_pardakht::~Dialog_pardakht()
{
    delete ui;
}


void Dialog_pardakht::on_Discard_btn_clicked()
{
     this->close();
}
