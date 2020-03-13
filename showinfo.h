#ifndef SHOWINFO_H
#define SHOWINFO_H

#include <QDialog>
#include <QtSql>
#include <QDataWidgetMapper>
namespace Ui {
class showinfo;
}

class showinfo : public QDialog
{
    Q_OBJECT
public:
    explicit showinfo(QWidget *parent = 0);
    void openTable();
    ~showinfo();

private:
    Ui::showinfo *ui;
};

#endif // SHOWINFO_H
