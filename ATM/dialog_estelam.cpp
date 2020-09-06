#include "dialog_estelam.h"
#include "ui_dialog_estelam.h"
#include "dialog_pardakht.h"

Dialog_Estelam::Dialog_Estelam(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Estelam)
{
    ui->setupUi(this);
    ui->buttonBox->setStyleSheet("background-color: #00ffff");
     ui->Discard_btn->setStyleSheet("background-color: #212121");
   // ui->buttonBox->setStyleSheet("background-color: #212121");
}

Dialog_Estelam::~Dialog_Estelam()
{
    delete ui;
}

void Dialog_Estelam::on_buttonBox_accepted()
{
    Dialog_pardakht * p=new Dialog_pardakht();
    p->show();
    this->close();

}



void Dialog_Estelam::on_Discard_btn_clicked()
{
      this->close();
}
