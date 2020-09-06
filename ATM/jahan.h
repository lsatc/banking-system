#ifndef JAHAN_H
#define JAHAN_H

#include <QMainWindow>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class Jahan; }
QT_END_NAMESPACE

class Jahan : public QMainWindow
{
    Q_OBJECT

public:
    Jahan(QWidget *parent = nullptr);
    ~Jahan();
    void cashTransfer(int _cash, QString _origin, QString _destination,QString _cvv2,int _year,int _month,QString pass);
    QString nameCardchecker(QString _cardNum);
private slots:
    void on_Find_btn_clicked();

    void on_from_line_textChanged(const QString &arg1);

    void on_to_line_textChanged(const QString &arg1);

    void on_Amount_line_textChanged(const QString &arg1);

    void on_CVV2_line_textChanged(const QString &arg1);

    void on_Instantpass_line_textChanged(const QString &arg1);

private:
    Ui::Jahan *ui;
    void keyPressEvent(QKeyEvent *q);
};
#endif // JAHAN_H
