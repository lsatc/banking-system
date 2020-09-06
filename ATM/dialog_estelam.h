#ifndef DIALOG_ESTELAM_H
#define DIALOG_ESTELAM_H

#include <QDialog>

namespace Ui {
class Dialog_Estelam;
}

class Dialog_Estelam : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Estelam(QWidget *parent = nullptr);
    ~Dialog_Estelam();

private slots:
    void on_buttonBox_accepted();
    void on_Discard_btn_clicked();

private:
    Ui::Dialog_Estelam *ui;
};

#endif // DIALOG_ESTELAM_H
