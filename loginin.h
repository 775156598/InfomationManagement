#ifndef LOGININ_H
#define LOGININ_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class loginin;
}

class loginin : public QDialog
{
    Q_OBJECT

public:
    explicit loginin(QWidget *parent = 0);
    ~loginin();

private slots:
    void on_buttonin_clicked();

private:
    Ui::loginin *ui;
    MainWindow* MW;
};

#endif // LOGININ_H
