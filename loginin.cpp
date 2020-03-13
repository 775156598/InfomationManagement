#include "loginin.h"
#include "ui_loginin.h"
#include <QString>
#include <QMessageBox>
loginin::loginin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginin)
{
    ui->setupUi(this);
    setWindowTitle("登陆界面");      //标题
    connect(ui->buttonin,SIGNAL(clicked(bool)),this,SLOT(on_buttonin_clicked(bool)));  //槽函数
}

loginin::~loginin()
{
    //delete ui;
}



void loginin::on_buttonin_clicked()    //登陆按钮的实现
{
    QString YHM = ui->lineEditYHM->text();
    QString MM = ui->lineEditMM->text();
    if(YHM.trimmed()=="A20a"&&MM.trimmed()=="123456")    //人为定义账户和密码
    {
        MW = new MainWindow(this);
        MW->show();
        this->destroy();
    }
    else
    {
        QMessageBox::warning(this,"警告","密码输入错误");
        ui->lineEditMM->setText("");
    }
}
