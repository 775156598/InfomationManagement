#include "searchdialog.h"
#include "ui_searchdialog.h"
#include<iostream>
#include<qdebug.h>
SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}
QString SearchDialog::GetStuNo()  //这个函数有点问题，明天问一下老师，如%1%2%3%4%5%6%为什么就不行而1%2%3%4%5%6%就可以？
{
    if(ui->StuNo3_->isChecked())
    {
        int len=ui->StuNo3->text().length();
        QString q="%";
        for(int i=0;i<len;i++)
        {
            qDebug()<<ui->StuNo3->text().mid(i,1)<<"第"<<i<<"个";
            q.append(ui->StuNo3->text().mid(i,1));
            if(i!=5) q.append("%");
        }
        q.append("%");
        qDebug()<<q<<"this is q";
        return q;
        //return ui->StuNo3->text();
    }

    else return NULL;
}
QString SearchDialog::GetName()
{
    if(ui->Name3_->isChecked())
        return ui->Name3->text();
    else return NULL;
}
QString SearchDialog::GetAge()
{
    if(ui->Age3_->isChecked())
        return ui->Age3->text();
    else return NULL;
}
QString SearchDialog::GetAge2()
{
    if(ui->Age32_->isChecked())
    {
        qDebug()<<ui->Age32->text();
        return ui->Age32->text();
    }

    else return NULL;
}
QString SearchDialog::GetCollege()
{
    if(ui->College3_->isChecked())
        return ui->College3->text();
    else return NULL;
}
QString SearchDialog::GetMajor()
{
    if(ui->Major3_->isChecked())
        return ui->Major3->text();
    else return NULL;
}

QString SearchDialog::GetPhoneNumber()
{
    if(ui->PhoneNumber3_->isChecked())
        return ui->PhoneNumber3->text();
    else return NULL;
}

QString SearchDialog::GetAward()
{
    if(ui->Award3_->isChecked())
        return ui->Award3->text();
    else return NULL;
}
QString SearchDialog::GetPunish()
{
    if(ui->Punish3_->isChecked())
        return ui->Punish3->text();
    else return NULL;
}
QString SearchDialog::GetNativePlace()
{
    if(ui->NativePlace3_->isChecked())
        return ui->NativePlace3->text();
    else return NULL;
}
QString SearchDialog::GetParentsInfo()
{
    if(ui->ParentsInfo3_->isChecked())
        return ui->ParentsInfo3->text();
    else return NULL;
}
bool SearchDialog::GetIfMiddleSearch()
{
    if(ui->middle_search->isChecked())
    {
        return true;
    }
    else return false;
}
bool SearchDialog::GetIfDistinct()
{
    if(ui->distinct->isChecked()) return true;
    else return false;
}
