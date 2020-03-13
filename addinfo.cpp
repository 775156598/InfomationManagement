#include "addinfo.h"
#include "ui_addinfo.h"
#include <QMainWindow>
#include <mainwindow.h>
#include <QMessageBox>

addinfo::addinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addinfo)
{
    ui->setupUi(this);
    QRegExp regExp("[1-9][0-9]{5}");
    ui->StuNoEdit_2->setValidator(new QRegExpValidator(regExp,this));
    QRegExp regExp2("[1-9][0-9]{10}");
    ui->PhoneNumberEdit_2->setValidator(new QRegExpValidator(regExp2,this));
    ui->add->setEnabled(false);
}

addinfo::~addinfo()
{
    delete ui;
}


void addinfo::on_add_clicked()
{
    MainWindow *p = (MainWindow*)parentWidget();

    int row=p->tabModel->rowCount(),i;
    for(i=0;i<row;i++)
        if(ui->StuNoEdit_2->text()==p->tabModel->data(p->tabModel->index(i,0,QModelIndex()),Qt::EditRole).toString())
            break;
    if(i<row)
        QMessageBox::warning(NULL, "warning", "学号重复，添加失败", QMessageBox::Yes, QMessageBox::Yes);
    else{
        p->tabModel->insertRow(row); //添加一行
        p->tabModel2->insertRow(row); //添加一行

        p->tabModel->setData(p->tabModel->index(row,0,QModelIndex()),ui->StuNoEdit_2->text(),Qt::EditRole);
        p->tabModel->setData(p->tabModel->index(row,1,QModelIndex()),ui->NameEdit_2->text(),Qt::EditRole);
        p->tabModel->setData(p->tabModel->index(row,2,QModelIndex()),ui->GenderEdit_2->currentText(),Qt::EditRole);
        p->tabModel->setData(p->tabModel->index(row,3,QModelIndex()),ui->AgeEdit_2->text(),Qt::EditRole);
        p->tabModel->setData(p->tabModel->index(row,4,QModelIndex()),ui->CollegeEdit_2->currentText(),Qt::EditRole);
        p->tabModel->setData(p->tabModel->index(row,5,QModelIndex()),ui->MajorEdit_2->text(),Qt::EditRole);
        p->tabModel->setData(p->tabModel->index(row,6,QModelIndex()),ui->ClassEdit_2->text(),Qt::EditRole);
        p->tabModel->setData(p->tabModel->index(row,7,QModelIndex()),ui->PhoneNumberEdit_2->text(),Qt::EditRole);

        p->tabModel2->setData(p->tabModel2->index(row,0,QModelIndex()),ui->StuNoEdit_2->text(),Qt::EditRole);
        p->tabModel2->setData(p->tabModel2->index(row,1,QModelIndex()),ui->NameEdit_2->text(),Qt::EditRole);
        p->tabModel2->setData(p->tabModel2->index(row,2,QModelIndex()),ui->GenderEdit_2->currentText(),Qt::EditRole);
        p->tabModel2->setData(p->tabModel2->index(row,3,QModelIndex()),ui->AwardEdit_2->text(),Qt::EditRole);
        p->tabModel2->setData(p->tabModel2->index(row,4,QModelIndex()),ui->PunishEdit_2->text(),Qt::EditRole);
        p->tabModel2->setData(p->tabModel2->index(row,5,QModelIndex()),ui->NativePlaceEdit_2->text(),Qt::EditRole);
        p->tabModel2->setData(p->tabModel2->index(row,6,QModelIndex()),ui->ParentsInfoEdit_2->text(),Qt::EditRole);
        QMessageBox::StandardButton rb =QMessageBox::information(NULL, "information", "添加成功", QMessageBox::Ok, QMessageBox::Ok);
        if(rb==QMessageBox::Ok)
            close();
    }

}

bool addinfo::addSuccess()
{
    if(ui->StuNoEdit_2->hasAcceptableInput()&&ui->PhoneNumberEdit_2->hasAcceptableInput()
            &&!ui->NameEdit_2->text().isEmpty()&&!ui->MajorEdit_2->text().isEmpty())
    {
        return true;
    }
    else{
        return false;
    }
}



void addinfo::on_StuNoEdit_2_textChanged(const QString &arg1)
{
    ui->add->setEnabled(addSuccess());
}

void addinfo::on_NameEdit_2_textChanged(const QString &arg1)
{
    ui->add->setEnabled(addSuccess());
}

void addinfo::on_MajorEdit_2_textChanged(const QString &arg1)
{
    ui->add->setEnabled(addSuccess());
}

void addinfo::on_PhoneNumberEdit_2_textChanged(const QString &arg1)
{
    ui->add->setEnabled(addSuccess());
}

void addinfo::on_cancel_clicked()
{
    close();
}
