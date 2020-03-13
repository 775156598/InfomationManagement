#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include<qstring.h>
namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();
    QString GetStuNo();
    QString GetName();
    QString GetAge();
    QString GetAge2();
    QString GetCollege();
    QString GetMajor();
    QString GetPhoneNumber();
    QString GetAward();
    QString GetPunish();
    QString GetNativePlace();
    QString GetParentsInfo();
    bool GetIfMiddleSearch();
    bool GetIfDistinct();
//private slots:
    //void on_buttonBox_accepted();

private:
    Ui::SearchDialog *ui;
};

#endif // SEARCHDIALOG_H
