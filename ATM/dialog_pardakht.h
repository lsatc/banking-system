#ifndef DIALOG_PARDAKHT_H
#define DIALOG_PARDAKHT_H

#include <QDialog>

namespace Ui {
class Dialog_pardakht;
}

class Dialog_pardakht : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_pardakht(QWidget *parent = nullptr);
    ~Dialog_pardakht();

private slots:

    void on_Discard_btn_clicked();

private:
    Ui::Dialog_pardakht *ui;
};

#endif // DIALOG_PARDAKHT_H
