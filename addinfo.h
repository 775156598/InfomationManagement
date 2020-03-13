#ifndef ADDINFO_H
#define ADDINFO_H

#include <QDialog>

namespace Ui {
class addinfo;
}

class addinfo : public QDialog
{
    Q_OBJECT

public:
    explicit addinfo(QWidget *parent = 0);
    ~addinfo();
    bool addSuccess();

private slots:
    void on_add_clicked();

    void on_StuNoEdit_2_textChanged(const QString &arg1);

    void on_NameEdit_2_textChanged(const QString &arg1);

    void on_MajorEdit_2_textChanged(const QString &arg1);

    void on_PhoneNumberEdit_2_textChanged(const QString &arg1);

    void on_cancel_clicked();

private:
    Ui::addinfo *ui;
};

#endif // ADDINFO_H
