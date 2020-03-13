#include "showinfo.h"
#include "ui_showinfo.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQueryModel>
showinfo::showinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showinfo)
{
    ui->setupUi(this);

}

void showinfo::openTable()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT StudentInfo.StuNo,StudentInfo.Name,StudentInfo.Gender,StudentInfo.Age,"
    "StudentInfo.College,StudentInfo.Major,StudentInfo.Class,StudentInfo.PhoneNumber,StuArchive.Award,"
    "StuArchive.Punish,StuArchive.NativePlace,StuArchive.ParentsInfo from StudentInfo,StuArchive"
    " where StudentInfo.StuNo=StuArchive.StuNo");
    ui->tableView->setModel(model);//设置数据模型
}

showinfo::~showinfo()
{
    delete ui;
}
