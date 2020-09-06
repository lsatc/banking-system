#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QIcon icon(":/lending .png");
    this->setWindowIcon(icon);

    this->setStyleSheet("background-color: #1f1f1f");
    ui->pushButton_sendMessage->setStyleSheet("QPushButton {  border: 2px solid #1e8465;}\n"
                                              "QPushButton{ border-radius: 6px;}\n"
                                              "QPushButton{background-color: #1e8465;}\n"
                                              "QPushButton{min-width: 50px;}\n");

    ui->lineEdit->setStyleSheet("QLineEdit {  border: 1px solid #1e8465;}\n"
                                "QLineEdit{ border-radius: 2px;}\n"
                                "QLineEdit{background-color: black;}\n"
                                "QLineEdit{min-width: 50px;}\n");
    ui->lineEdit_2->setStyleSheet("QLineEdit {  border: 1px solid #1e8465;}\n"
                                  "QLineEdit{ border-radius: 2px;}\n"
                                  "QLineEdit{background-color: black;}\n"
                                  "QLineEdit{min-width: 50px;}\n");
    ui->lineEdit_message->setStyleSheet("QLineEdit {  border: 1px solid #1e8465;}\n"
                                        "QLineEdit{ border-radius: 2px;}\n"
                                        "QLineEdit{background-color: black;}\n"
                                        "QLineEdit{min-width: 50px;}\n");
    ui->textBrowser_receivedMessages->setStyleSheet("QLineEdit {  border: 1px solid #1e8465;}\n"
                                                    "QLineEdit{ border-radius: 2px;}\n"
                                                    "QLineEdit{background-color: black;}\n"
                                                    "QLineEdit{min-width: 50px;}\n");


    socket = new QTcpSocket(this);
    connect(this,SIGNAL(newMessage(QString)),this,SLOT(displayMessage(QString)));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readSocket()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(discardSocket()));
    socket->connectToHost(QHostAddress::LocalHost,8080);
    if(socket->waitForConnected())
        this->ui->statusbar->showMessage("Connected to Server");
    else{
        QMessageBox::critical(this,"","not connected");
        exit(EXIT_FAILURE);
    }
}

MainWindow::~MainWindow()
{
    if(socket->isOpen())
        socket->close();
    delete ui;
}

void MainWindow::readSocket()
{
    QByteArray block = socket->readAll();

    QDataStream in(&block, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_5_12);

    while (!in.atEnd())
    {
        QString receiveString;
        in >> receiveString;
        emit newMessage(receiveString);
    }
}

void MainWindow::discardSocket()
{
    socket->deleteLater();
    socket=nullptr;

    this->ui->statusbar->showMessage("Disconnected!");
}

void MainWindow::on_pushButton_sendMessage_clicked()
{
    if(socket)
    {
        if(socket->isOpen())
        {

            QFile f(":/loginTest.json");
            f.open(QIODevice::ReadOnly);
            QByteArray b = f.readAll();
            QJsonDocument first = QJsonDocument::fromJson(b);
            QJsonObject userpaass;
            userpaass = first.object();
            f.close();

            if(userpaass.contains(ui->lineEdit->text())){
                QJsonObject ans = userpaass[(ui->lineEdit->text())].toObject();
                if((ans["password"].toString()) == ui->lineEdit_2->text()){

                    QString str = this->ui->lineEdit_message->text();
                    if(str.isEmpty()){
                        QMessageBox::information(this,"empty field","fill all the items.");
                        return ;
                    }else {
                        QFile f(":/json.json");
                        f.open(QIODevice::ReadOnly);
                        QByteArray b=f.readAll();
                        QJsonDocument d=QJsonDocument::fromJson(b);
                        QJsonObject o=d.object();
                        QJsonArray users=o["users"].toArray();
                        QJsonObject user;
                        QJsonObject cards;
                        int i=0;
                        f.close();

                        for (;i<users.size();i++) {
                            user=users[i].toObject();
                            cards=user["card"].toObject();
                            if(cards["cardNumber"].toString()==ui->lineEdit_message->text())
                                break;

                        }
                        if(i==users.size())

                        {
                            QMessageBox::information(this,"","card not found");
                            return; }
                    }
                    QByteArray block;
                    QDataStream out(&block, QIODevice::WriteOnly);

                    out.setVersion(QDataStream::Qt_5_12);
                    out << str;


                    socket->write(block);

                    return;


                }
                else{
                    QMessageBox::information(this,"pass","wrong password! please try again.");
                    return ;
                }
            }
            else{
                QMessageBox::information(this,"username","user not found!");
                return ;
            }


        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

void MainWindow::displayMessage(const QString& str)
{
    this->ui->textBrowser_receivedMessages->setText(str);
}
int counterkey4=0;

void MainWindow::keyPressEvent(QKeyEvent *q)
{

    switch (counterkey4)
    {
    case 0:
    {
        if(q->key()==Qt::Key_Down)
        {
            ui->lineEdit_2->setFocus();
            counterkey4++;
        }
        if(q->key()==Qt::Key_Up)
        {
            ui->lineEdit_message->setFocus();
            ui->lineEdit_message->setCursorPosition(0);
            counterkey4=2;
        }
        break;
    }
    case 1:
    {
        if(q->key()==Qt::Key_Down)
        {
            ui->lineEdit_message->setFocus();
            counterkey4++;
        }
        if(q->key()==Qt::Key_Up)
        {
            ui->lineEdit->setFocus();
            counterkey4--;
        }
        break;
    }
    case 2:
    {
        if(q->key()==Qt::Key_Down)
        {
            ui->lineEdit->setFocus();
            counterkey4=0;
        }
        if(q->key()==Qt::Key_Up)
        {
            ui->lineEdit_2->setFocus();
            counterkey4--;
        }
        break;
    }    }

}

void MainWindow::on_lineEdit_message_textChanged(const QString &arg1)
{
    if(ui->lineEdit_message->text().isEmpty())
    {
        ui->error_lbl->clear();
    }
    else if(arg1.contains(QChar(' ')))
    {
        ui->lineEdit_message->backspace();
        ui->error_lbl->setText("Wrong!!!");
    }
    else if(((arg1.back()>=QChar('0'))&&(arg1.back()<=QChar('9'))))
    {
        ui->error_lbl->clear();
    }
    else
    {

        ui->lineEdit_message->backspace();
        ui->error_lbl->setText("Wrong!!!");

    }
}
