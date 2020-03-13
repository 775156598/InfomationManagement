#include "add.h"
#include "ui_add.h"
#include <QMainWindow>
#include <mainwindow.h>
#include <QMessageBox>

Add::Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add)
{
    ui->setupUi(this);

}

Add::~Add()
{
    delete ui;
}

void Add::on_add_clicked()
{
    MainWindow *p = (MainWindow*)parentWidget();
    int row=p->tabModel->rowCount();
    p->tabModel->insertRow(row); //添加一行
    p->tabModel2->insertRow(row); //添加一行

    p->tabModel->setData(p->tabModel->index(row,0,QModelIndex()),ui->lineEdit->text(),Qt::EditRole);
    p->tabModel->setData(p->tabModel->index(row,1,QModelIndex()),ui->lineEdit_2->text(),Qt::EditRole);
    p->tabModel->setData(p->tabModel->index(row,2,QModelIndex()),ui->comboBox_2->currentText(),Qt::EditRole);
    p->tabModel->setData(p->tabModel->index(row,3,QModelIndex()),ui->lineEdit_4->text(),Qt::EditRole);
    p->tabModel->setData(p->tabModel->index(row,4,QModelIndex()),ui->lineEdit_3->text(),Qt::EditRole);
    p->tabModel->setData(p->tabModel->index(row,5,QModelIndex()),ui->lineEdit_5->text(),Qt::EditRole);
    p->tabModel->setData(p->tabModel->index(row,6,QModelIndex()),ui->lineEdit_6->text(),Qt::EditRole);
    p->tabModel->setData(p->tabModel->index(row,7,QModelIndex()),ui->lineEdit_7->text(),Qt::EditRole);

    p->tabModel2->setData(p->tabModel2->index(row,0,QModelIndex()),ui->lineEdit->text(),Qt::EditRole);
    p->tabModel2->setData(p->tabModel2->index(row,1,QModelIndex()),ui->lineEdit_2->text(),Qt::EditRole);
    p->tabModel2->setData(p->tabModel2->index(row,2,QModelIndex()),ui->comboBox_2->currentText(),Qt::EditRole);
    p->tabModel2->setData(p->tabModel2->index(row,3,QModelIndex()),ui->textEdit->toPlainText(),Qt::EditRole);
    p->tabModel2->setData(p->tabModel2->index(row,4,QModelIndex()),ui->textEdit_2->toPlainText(),Qt::EditRole);
    p->tabModel2->setData(p->tabModel2->index(row,5,QModelIndex()),ui->lineEdit_8->text(),Qt::EditRole);
    p->tabModel2->setData(p->tabModel2->index(row,6,QModelIndex()),ui->textEdit_3->toPlainText(),Qt::EditRole);
    QMessageBox::StandardButton rb =QMessageBox::information(NULL, "information", "添加成功", QMessageBox::Ok, QMessageBox::Ok);
    if(rb==QMessageBox::Ok)
        this->close();
}

void Add::on_cancel_clicked()
{
    close();
}
