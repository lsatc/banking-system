#include "jahan.h"
#include "ui_jahan.h"
#include "dialog_estelam.h"
#include <QtGlobal>
#include <QRandomGenerator>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <random>
#include <QDateTime>
#include <QMessageBox>

Jahan::Jahan(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Jahan)
{
    ui->setupUi(this);
    ui->Find_btn->setStyleSheet("background-color: #212121");
    ui->from_line->setFocus();
    QIcon icon(":/lending .png");
    this->setWindowIcon(icon);
}



Jahan::~Jahan()
{
    delete ui;
}


void Jahan::on_Find_btn_clicked()
{




    cashTransfer(ui->Amount_line->text().toInt(),ui->from_line->text(),ui->to_line->text(),ui->CVV2_line->text(),ui->spinBox_2->text().toInt(),ui->spinBox->text().toInt(),ui->Instantpass_line->text());

  //  Dialog_Estelam * a=new Dialog_Estelam();
   // a->show();

}

QString Jahan::nameCardchecker(QString _cardNum){
    QFile accfile(":/json.json");
    QString _user;

    accfile.open(QIODevice::ReadOnly);
    QByteArray b = accfile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(b);
    QJsonObject test = doc.object();
    accfile.close();
    QJsonArray arr = test["users"].toArray();
    int sz = arr.size();
    for(int i=0; i<sz; i++){
        QJsonObject tmp = arr[i].toObject();
        QJsonObject hlp = tmp["card"].toObject();
        if((hlp["cardNumber"].toString()) == _cardNum)
            _user = tmp["username"].toString();
    }

    QFile userfile(":/main(user's info).json");
    userfile.open(QIODevice::ReadOnly);
    QByteArray tool = userfile.readAll();
    QJsonDocument d = QJsonDocument::fromJson(tool);
    QJsonObject main;
    userfile.close();
    main = d.object();
    QJsonObject user = main[_user].toObject();
    QString res;
    QString _name = user["name"].toString();
    QString _familyname = user["familyname"].toString();
    res += _name;
    res += "_";
    res += _familyname;
    //res[user["name"].toString()] = user["familyname"].toString();
    return res;
}
void Jahan::cashTransfer(int _cash, QString _origin, QString _destination,QString _cvv2,int _year,int _month,QString pass)
{


        QFile f(":/json.json");
        f.open(QIODevice::ReadOnly);
        QByteArray b=f.readAll();
        QJsonDocument d=QJsonDocument::fromJson(b);
        QJsonObject o=d.object();
        QJsonArray users=o["users"].toArray();
        QJsonArray transactions1;
        QJsonArray transactions2;
        QJsonObject cards1;
        QJsonObject user1;
        QJsonObject cards2;
        QJsonObject user2;
        f.close();
        int i=0;
        int k=0;
            for (;i<users.size();i++) {
                user1=users[i].toObject();
                cards1=user1["card"].toObject();
                if(cards1["cardNumber"].toString()==_origin){
                    if(user1["cash"].toInt()-_cash<0){
                        QMessageBox::information(this,"no money","Your account does not have enough money available to cover a payment.");
                    return;}
                   else if(_cash<=0){
                        QMessageBox::information(this,"invalid","Ammount of money is not valid.");
                        return;}
                    else if(user1["cardBlock"].toBool()==true||user1["cardPremission"].toBool()==false){
                        QMessageBox::information(this,"permission","you're not allowed to have a card.");
                        return;}
                    else{
                    for (;k<users.size();k++) {
                        user2=users[k].toObject();
                        cards2=user2["card"].toObject();
                        if(cards2["cardNumber"].toString()==_destination){                                                  //  ,cards["cvv2"].toString(),QDateTime::fromString( cards["expDate"].toString()));
                           if( cards1["cvv2"].toString()!=_cvv2)
                               {
                                QMessageBox::information(this,"cvv2","wrong cvv2! please try again");
                                return;}
                         else if(QDateTime::fromString(cards1["expDate"].toString()).date().year()!=_year||
                                QDateTime::fromString(cards1["expDate"].toString()).date().month()!=_month){
                               QMessageBox::information(this,"expire date","wrong expire date! please try again");
                           return;}
                           else if(QDateTime::fromString(cards1["expDate"].toString())<QDateTime::currentDateTime()){
                               QMessageBox::information(this,"expire","sorry; your card has been expired!");
                         return;}
                          else if(pass!=user1["dynamicPass"].toString()){
                               QMessageBox::information(this,"password","wrong password! please try again");
                                    return;
                          }
                           else if(QDateTime::fromString(user1["passTimer"].toString()).secsTo(QDateTime::currentDateTime())>120){
                            QMessageBox::information(this,"password","password has expired! please request a new password.");

                           return;}
                           else if(ui->Instantpass_line->text()=="")
                           {
                               QMessageBox::information(this,"pass","enter password!");
                               return;
                           }
                           else{
                               QString p =nameCardchecker(_destination);
                               QString str;
                               str+="Are you sure about reciver ";

                               str+=p;
                               str+="?";

                                 int ret= QMessageBox::question(nullptr," ",str,QMessageBox::Yes|QMessageBox::No);
                                 if(ret==QMessageBox::No){
                                     return;
                                 }
                                   int old_cash2=user2["cash"].toInt();
                                    user2["cash"] = old_cash2+_cash;


                                    int old_cash1=user1["cash"].toInt();
                                    user1["cash"] = old_cash1-_cash;

                                    transactions1=user1["lastTranasctions"].toArray();
                                    transactions2=user2["lastTranasctions"].toArray();
                                    break;

                                }

                            }
                    }
                    if(k==users.size()){
                        QMessageBox::information(this,"not exist","destination not found! please try another one.");
                    return;}
                    }
                break;}
            }

                if(i==users.size())
                    {
                    QMessageBox::information(this,"not exist","origin not found! please try another one.");

                     return;}
                else  {
                    for(int j=0;j<9;j++)
                            {
                                transactions1[j]=transactions1[j+1];
                            }
                            QJsonObject transaction1=transactions1[9].toObject();
                            transaction1["origin"]=_origin;
                            transaction1["destination"]=_destination;
                            transaction1["cashT"]=_cash;
                            transaction1["transactionDate"]=QDateTime::currentDateTime().toString();
                            transactions1[9]=transaction1;
                            user1["lastTranasctions"]=transactions1;

                            users[i]=user1;

                            for(int j=0;j<9;j++)
                            {
                                transactions2[j]=transactions2[j+1];
                            }
                            QJsonObject transaction2=transactions2[9].toObject();
                            transaction2["origin"]=_origin;
                            transaction2["destination"]=_destination;
                            transaction2["cashT"]=_cash;
                            transaction2["transactionDate"]=QDateTime::currentDateTime().toString();
                            transactions2[9]=transaction2;
                            user2["lastTranasctions"]=transactions2;

                            users[k]=user2;

                            o["users"]=users;

                            f.open(QIODevice::WriteOnly);

                            QJsonDocument d1(o);
                            f.write(d1.toJson());
                            f.close();
                            QMessageBox::information(this,"success","cash transfered successfully.");
                            ui->from_line->clear();
                            ui->to_line->clear();
                            ui->Instantpass_line->clear();
                            ui->CVV2_line->clear();
                            ui->Amount_line->clear();
                            ui->spinBox->setValue(1);
                            ui->spinBox_2->setValue(1990);

                            return;}


           }


void Jahan::on_from_line_textChanged(const QString &arg1)
{
    if(ui->from_line->text().isEmpty())
    {
     ui->From_lbl->setText("");
    }
    else if(arg1.contains(QChar(' ')))
    {
        ui->from_line->backspace();
        ui->From_lbl->setText("Wrong!!!");
    }
    else if(((arg1.back()>=QChar('0'))&&(arg1.back()<=QChar('9'))))
    {
         ui->From_lbl->setText("");
    }
    else
    {

        ui->from_line->backspace();
        ui->From_lbl->setText("Wrong!!!");

    }
}

void Jahan::on_to_line_textChanged(const QString &arg1)
{
    if(ui->to_line->text().isEmpty())
    {
     ui->To_lbl->setText("");
    }
    else if(arg1.contains(QChar(' ')))
    {
        ui->to_line->backspace();
        ui->To_lbl->setText("Wrong!!!");
    }
    else if(((arg1.back()>=QChar('0'))&&(arg1.back()<=QChar('9'))))
    {
         ui->To_lbl->setText("");
    }
    else
    {

        ui->to_line->backspace();
        ui->To_lbl->setText("Wrong!!!");

    }
}

void Jahan::on_Amount_line_textChanged(const QString &arg1)
{
    if(ui->Amount_line->text().isEmpty())
    {
     ui->Am_lbl->setText("");
    }
    else if(arg1.contains(QChar(' ')))
    {
        ui->Amount_line->backspace();
        ui->Am_lbl->setText("Wrong!!!");
    }
    else if(((arg1.back()>=QChar('0'))&&(arg1.back()<=QChar('9'))))
    {
         ui->Am_lbl->setText("");
    }
    else
    {

        ui->Amount_line->backspace();
        ui->Am_lbl->setText("Wrong!!!");

    }
}

void Jahan::on_CVV2_line_textChanged(const QString &arg1)
{
    if(ui->CVV2_line->text().isEmpty())
    {
     ui->cvv2_lbl->setText("");
    }
    else if(arg1.contains(QChar(' ')))
    {
        ui->CVV2_line->backspace();
        ui->cvv2_lbl->setText("Wrong!!!");
    }
    else if(((arg1.back()>=QChar('0'))&&(arg1.back()<=QChar('9'))))
    {
         ui->cvv2_lbl->setText("");
    }
    else
    {

        ui->CVV2_line->backspace();
        ui->cvv2_lbl->setText("Wrong!!!");

    }
}

void Jahan::on_Instantpass_line_textChanged(const QString &arg1)
{

    if(ui->Instantpass_line->text().isEmpty())
    {
     ui->Ins_lbl->setText("");
    }
    else if(arg1.contains(QChar(' ')))
    {
        ui->Instantpass_line->backspace();
        ui->Ins_lbl->setText("Wrong!!!");
    }
    else if(((arg1.back()>=QChar('0'))&&(arg1.back()<=QChar('9'))))
    {
         ui->Ins_lbl->setText("");
    }
    else
    {

        ui->Instantpass_line->backspace();
        ui->Ins_lbl->setText("Wrong!!!");

    }
}
int counterkey3=0;
void Jahan::keyPressEvent(QKeyEvent *q)
{
    switch (counterkey3)
    {
     case 0:
        {
            if(q->key()==Qt::Key_Down)
            {
                ui->to_line->setFocus();
                counterkey3++;
            }
            if(q->key()==Qt::Key_Up)
            {
                ui->Instantpass_line->setFocus();
                counterkey3=4;
            }
            break;
        }
    case 1:
       {
           if(q->key()==Qt::Key_Down)
           {
               ui->Amount_line->setFocus();
               counterkey3++;
           }
           if(q->key()==Qt::Key_Up)
           {
               ui->from_line->setFocus();
               counterkey3--;
           }
           break;
       }
    case 2:
       {
           if(q->key()==Qt::Key_Down)
           {

               ui->CVV2_line->setFocus();
               counterkey3++;
           }
           if(q->key()==Qt::Key_Up)
           {
               ui->to_line->setFocus();
               counterkey3--;
           }
           break;
       }
    case 3:
       {
           if(q->key()==Qt::Key_Down)
           {
               ui->Instantpass_line->setFocus();
               counterkey3++;
           }
           if(q->key()==Qt::Key_Up)
           {
               ui->Amount_line->setFocus();
               counterkey3--;
           }
           break;
       }
    case 4:
       {
           if(q->key()==Qt::Key_Down)
           {
               ui->from_line->setFocus();
               counterkey3=0;
           }
           if(q->key()==Qt::Key_Up)
           {
               ui->CVV2_line->setFocus();
               counterkey3--;
           }
           break;
       }

    }
}
