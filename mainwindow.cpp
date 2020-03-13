#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QSqlRecord>
#include <iostream>
#include <string>
#include <QDebug>
#include <searchdialog.h>
#include <ui_searchdialog.h>
using namespace std;
using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //setWindowTitle("学生信息管理系统");
    ui->setupUi(this);
    ui->actAdd->setEnabled(false);
    ui->actSearch->setEnabled(false);
    ui->actDelete->setEnabled(false);
    ui->actShow->setEnabled(false);
    ui->actSave->setEnabled(false);
    ui->actCancel->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow:: openTable(){
    //StuBase
    tabModel=new QSqlTableModel(this,DB);//数据表
    tabModel->setTable("StudentInfo"); //设置数据表
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，OnManualSubmit , OnRowChange
    tabModel->setSort(tabModel->fieldIndex("StuNo"),Qt::AscendingOrder); //排序
    if (!(tabModel->select()))//查询数据
    {
       QMessageBox::critical(this, "错误信息",
              "打开数据表错误,错误信息\n"+tabModel->lastError().text(),
                 QMessageBox::Ok,QMessageBox::NoButton);
       return;
    }

    //StuArchive
    tabModel2=new QSqlTableModel(this,DB);//数据表
    tabModel2->setTable("StuArchive"); //设置数据表
    tabModel2->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，OnManualSubmit , OnRowChange
    tabModel2->setSort(tabModel2->fieldIndex("StuNo"),Qt::AscendingOrder); //排序
    if (!(tabModel2->select()))//查询数据
    {
       QMessageBox::critical(this, "错误信息",
              "打开数据表错误,错误信息\n"+tabModel2->lastError().text(),
                 QMessageBox::Ok,QMessageBox::NoButton);
       return;
    }


    //字段显示名
        tabModel->setHeaderData(tabModel->fieldIndex("StuNo"),Qt::Horizontal,"学号");
        tabModel->setHeaderData(tabModel->fieldIndex("Name"),Qt::Horizontal,"姓名");
        tabModel->setHeaderData(tabModel->fieldIndex("Gender"),Qt::Horizontal,"性别");
        tabModel->setHeaderData(tabModel->fieldIndex("Age"),Qt::Horizontal,"年龄");
        tabModel->setHeaderData(tabModel->fieldIndex("College"),Qt::Horizontal,"院系");
        tabModel->setHeaderData(tabModel->fieldIndex("Major"),Qt::Horizontal,"专业");
        tabModel->setHeaderData(tabModel->fieldIndex("Class"),Qt::Horizontal,"班级");
        tabModel->setHeaderData(tabModel->fieldIndex("PhoneNumber"),Qt::Horizontal,"电话");

        theSelection=new QItemSelectionModel(tabModel);//关联选择模型
        ui->tableView->setModel(tabModel);//设置数据模型
        ui->tableView->setSelectionModel(theSelection); //设置选择模型
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            connect(theSelection,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

            //创建界面组件与数据模型的字段之间的数据映射
                dataMapper= new QDataWidgetMapper();
                dataMapper->setModel(tabModel);//设置数据模型
                dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//

            //    dataMapper->setItemDelegate(new QSqlRelationalDelegate(this)); //含有外键的
            //界面组件与tabModel的具体字段之间的联系
                dataMapper->addMapping(ui->StuNo,tabModel->fieldIndex("StuNo"));
                dataMapper->addMapping(ui->Name,tabModel->fieldIndex("Name"));
                dataMapper->addMapping(ui->Gender,tabModel->fieldIndex("Gender"));

                dataMapper->addMapping(ui->Age,tabModel->fieldIndex("Age"));
                dataMapper->addMapping(ui->College,tabModel->fieldIndex("College"));
                dataMapper->addMapping(ui->Major,tabModel->fieldIndex("Major"));

                dataMapper->addMapping(ui->Class,tabModel->fieldIndex("Class"));
                dataMapper->addMapping(ui->PhoneNumber,tabModel->fieldIndex("PhoneNumber"));
                dataMapper->toFirst();//移动到首记录

        //字段显示名
                    tabModel2->setHeaderData(tabModel2->fieldIndex("StuNo"),Qt::Horizontal,"学号");
                    tabModel2->setHeaderData(tabModel2->fieldIndex("Name"),Qt::Horizontal,"姓名");
                    tabModel2->setHeaderData(tabModel2->fieldIndex("Gender"),Qt::Horizontal,"性别");
                    tabModel2->setHeaderData(tabModel2->fieldIndex("Award"),Qt::Horizontal,"奖励");
                    tabModel2->setHeaderData(tabModel2->fieldIndex("Punish"),Qt::Horizontal,"处分");
                    tabModel2->setHeaderData(tabModel2->fieldIndex("NativePlace"),Qt::Horizontal,"籍贯");
                    tabModel2->setHeaderData(tabModel2->fieldIndex("ParentsInfo"),Qt::Horizontal,"家长信息");

                    theSelection2=new QItemSelectionModel(tabModel2);//关联选择模型
                    ui->tableView_2->setModel(tabModel2);//设置数据模型
                    ui->tableView_2->setSelectionModel(theSelection2); //设置选择模型
                    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
                    connect(theSelection2,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentRowChanged2(QModelIndex,QModelIndex)));

                    //创建界面组件与数据模型的字段之间的数据映射
                        dataMapper2= new QDataWidgetMapper();
                        dataMapper2->setModel(tabModel2);//设置数据模型
                        dataMapper2->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//

                    //    dataMapper->setItemDelegate(new QSqlRelationalDelegate(this)); //含有外键的
                    //界面组件与tabModel的具体字段之间的联系
                        dataMapper2->addMapping(ui->StuNo2,tabModel2->fieldIndex("StuNo"));
                        dataMapper2->addMapping(ui->Name2,tabModel2->fieldIndex("Name"));
                        dataMapper2->addMapping(ui->Gender2,tabModel2->fieldIndex("Gender"));

                        dataMapper2->addMapping(ui->Punish,tabModel2->fieldIndex("Punish"));
                        dataMapper2->addMapping(ui->NativePlace,tabModel2->fieldIndex("NativePlace"));
                        dataMapper2->addMapping(ui->ParentsInfo,tabModel2->fieldIndex("ParentsInfo"));
                        dataMapper2->toFirst();//移动到首记录
                    ui->stackedWidget->setCurrentIndex(0);
                    getFieldNames(tabModel);
       InputFormer();
}


//界面右输入格式设置
void MainWindow::InputFormer()
{
    QRegExp regExp("[1-9][0-9]{5}");
    ui->StuNo->setValidator(new QRegExpValidator(regExp,this));
    ui->StuNo2->setValidator(new QRegExpValidator(regExp,this));
    QRegExp regExp2("[1-9][0-9]{10}");
    ui->PhoneNumber->setValidator(new QRegExpValidator(regExp2,this));
}

//打开数据库按钮
void MainWindow::on_actOpenDB_triggered()
{
    QString file=QFileDialog::getOpenFileName(this,"选择数据库","","SQL Lite数据库(*.db *.db3)");
    if(file.isEmpty())
    {
        return ;
    }
    DB=QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
    DB.setDatabaseName(file); //设置数据库名称

    if (!DB.open())   //打开数据库
    {
        QMessageBox::warning(this, "错误", "打开数据库失败",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

    //打开数据表
    openTable();
    ui->actOpenDB->setEnabled(false);
    ui->actAdd->setEnabled(true);
    ui->actSearch->setEnabled(true);
    ui->actDelete->setEnabled(true);
    ui->actShow->setEnabled(true);
    ui->actSave->setEnabled(true);
    ui->actCancel->setEnabled(true);

}


//搜索按钮
void MainWindow::on_actSearch_triggered()
{
    sd=new SearchDialog(this);
    //sd->show();
    if(sd->exec()==SearchDialog::Accepted)
    {
        QString str1=sd->GetStuNo();
        qDebug()<<"this is str1:"<<str1;
        QString str2=sd->GetName();
        qDebug()<<"this is name:"<<str2;
        QString str3=sd->GetAge();
        QString str32=sd->GetAge2();
        //qDebug()<<str32;
        QString str4=sd->GetCollege();
        QString str5=sd->GetMajor();
        QString str6=sd->GetPhoneNumber();
        QString str7=sd->GetAward();
        QString str8=sd->GetPunish();
        QString str9=sd->GetNativePlace();
        QString str10=sd->GetParentsInfo();
        bool if_distinct=sd->GetIfDistinct();
        bool if_middlesearch=sd->GetIfMiddleSearch();
        tabModel3=new QSqlQueryModel();
        //头搜索
        if(!if_middlesearch)
        {
            if(str3!=NULL&&str32!=NULL)
            {
                qDebug()<<"str3 and str32 in not NULL"<<"头搜索";
                tabModel3->setQuery(tr("select StudentInfo.StuNo,StudentInfo.Name,StudentInfo.Gender,College,Major,Class,PhoneNumber,Age,Award,Punish,NativePlace,ParentsInfo from StudentInfo,StuArchive where StudentInfo.StuNo=StuArchive.StuNo and  StudentInfo.StuNo like '%1' and  StudentInfo.Name like '%2'  and College like '%3' and Major like '%4' and PhoneNumber like '%5' and Award like '%6' and Punish like '%7' and NativePlace like '%8' and ParentsInfo like '%9' and StudentInfo.Age > '%10' and StudentInfo.Age< '%11'").arg(str1+'%').arg(str2+'%').arg(str4+'%').arg(str5+'%').arg(str6+'%').arg(str7+'%').arg(str8+'%').arg(str9+'%').arg(str10+'%').arg(str3).arg(str32));
            }
            else
                tabModel3->setQuery(tr("select StudentInfo.StuNo,StudentInfo.Name,StudentInfo.Gender,College,Major,Class,PhoneNumber,Age,Award,Punish,NativePlace,ParentsInfo from StudentInfo,StuArchive where StudentInfo.StuNo=StuArchive.StuNo and  StudentInfo.StuNo like '%1' and  StudentInfo.Name like '%2' and StudentInfo.Age like '%3' and College like '%4' and Major like '%5' and PhoneNumber like '%6' and Award like '%7' and Punish like '%8' and NativePlace like '%9' and ParentsInfo like '%10'").arg(str1).arg(str2+'%').arg(str3+'%').arg(str4+'%').arg(str5+'%').arg(str6+'%').arg(str7+'%').arg(str8+'%').arg(str9+'%').arg(str10+'%'));
        }
        else//
        {
            qDebug()<<"中间搜索";
            //tabModel3->setQuery(tr("select StudentInfo.StuNo,StudentInfo.Name,StudentInfo.Gender,College,Major,Class,PhoneNumber,Age,Award,Punish,NativePlace,ParentsInfo from StudentInfo,StuArchive where StudentInfo.StuNo=StuArchive.StuNo and  StudentInfo.StuNo like '%1' and  StudentInfo.Name like '%2' and StudentInfo.Age like '%3' and College like '%4' and Major like '%5' and PhoneNumber like '%6' and Award like '%7' and Punish like '%8' and NativePlace like '%9' and ParentsInfo like '%10'").arg(str1+'%').arg(str2+'%').arg(str3+'%').arg(str4+'%').arg(str5+'%').arg(str6+'%').arg(str7+'%').arg(str8+'%').arg(str9+'%').arg(str10+'%'));

        }
            // tr("Major like '%5' and PhoneNum like '%6' and Award like '%7' and Punish like '%8' and NativePlace like '%9' and ParentsInfo like '%10'").arg(str6+'%').arg(str7+'%').arg(str8+'%').arg(str9+'%').arg(str10+'%')
             theSelection3=new QItemSelectionModel(tabModel3);//关联选择模型
            //tableview就是显示表的组件
             ui->tableView_3->setModel(tabModel3);//设置数据模型
             ui->tableView_3->setSelectionModel(theSelection3); //设置选择模型

                 connect(theSelection3,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(on_currentRowChanged3(QModelIndex,QModelIndex)));

                 //创建界面组件与数据模型的字段之间的数据映射
                     dataMapper3= new QDataWidgetMapper();
                     dataMapper3->setModel(tabModel3);//设置数据模型
                     dataMapper3->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//

                 //    dataMapper->setItemDelegate(new QSqlRelationalDelegate(this)); //含有外键的
                 //界面组件与tabModel的具体字段之间的联系,如ui->StuNo为界面组件  tabModel->fieldIndex("StuNo")为Tabmodel的具体字段
                     dataMapper3->addMapping(ui->lineEdit,0);

//                     dataMapper3->addMapping(ui->StuNo2,0);  //这里是：一个model对应多个视图，这样一个试图改另一个视图也会变
//                     dataMapper3->addMapping(ui->StuNo,0);
                     dataMapper3->addMapping(ui->lineEdit_2,1);
//                     dataMapper3->addMapping(ui->Name2,1);
//                     dataMapper3->addMapping(ui->Name,1);
                     dataMapper3->addMapping(ui->comboBox_2,2);
//                     dataMapper3->addMapping(ui->Gender2,2);
//                     dataMapper3->addMapping(ui->Gender,2);

                     dataMapper3->addMapping(ui->lineEdit_4,3);
                     dataMapper3->addMapping(ui->lineEdit_3,4);
                     dataMapper3->addMapping(ui->lineEdit_5,5);

                     dataMapper3->addMapping(ui->lineEdit_6,6);
                     dataMapper3->addMapping(ui->lineEdit_7,7);
                     dataMapper3->addMapping(ui->textEdit,8);
                     dataMapper3->addMapping(ui->textEdit_2,9);
                     dataMapper3->addMapping(ui->lineEdit_8,10);
                     dataMapper3->addMapping(ui->textEdit_3,11);
                     dataMapper3->toFirst();//移动到首记录

    }
}

//添加按钮
void MainWindow::on_actAdd_triggered()
{
    info = new addinfo(this);
    info->show();
}


//取消按钮
void MainWindow::on_actCancel_triggered()
{
    tabModel->revertAll();
    tabModel2->revertAll();
}

//显示按钮
void MainWindow::on_actShow_triggered()
{
    showAll = new showinfo(this);
    showAll->show();
    showAll->openTable();
}

//删除按钮
void MainWindow::on_actDelete_triggered()
{
    if(ui->tabWidget->currentIndex()==0){
        QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", "删除学生信息同时将删除该学生的档案，是否继续？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb==QMessageBox::Yes)
        {
            QModelIndex curIndex=theSelection->currentIndex();//获取当前选择单元格的模型索引
            tabModel->removeRow(curIndex.row());//删除最后一行
            QModelIndex indexA=tabModel->index(curIndex.row(),0,QModelIndex());
            QString StuNo_index=tabModel->data(indexA,Qt::EditRole).toString();
            cout<<StuNo_index.toStdString();
            int row=tabModel2->rowCount();
            for(int i=0;i<row;i++)
                if(StuNo_index==tabModel2->data(tabModel2->index(i,0,QModelIndex()),Qt::EditRole).toString())
                    tabModel2->removeRow(i);
        }
        else
        {}
    }
    else if(ui->tabWidget->currentIndex()==1)
    {
        QMessageBox::StandardButton rb =QMessageBox::warning(NULL, "warning", "将删除该学生的档案与学生信息，是否继续？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb==QMessageBox::Yes)
        {
            QModelIndex curIndex=theSelection->currentIndex();//获取当前选择单元格的模型索引
            tabModel2->removeRow(curIndex.row());//删除最后一行
            QModelIndex indexA=tabModel2->index(curIndex.row(),0,QModelIndex());
            QString StuNo_index=tabModel2->data(indexA,Qt::EditRole).toString();
            cout<<StuNo_index.toStdString();
            int row=tabModel->rowCount();
            for(int i=0;i<row;i++)
                if(StuNo_index==tabModel->data(tabModel->index(i,0,QModelIndex()),Qt::EditRole).toString())
                    tabModel->removeRow(i);
        }
        else
        {}
    }

}


//保存按钮
void MainWindow::on_actSave_triggered()
{
    bool res=tabModel->submitAll();
    bool res2=tabModel2->submitAll();
    if (!res||!res2)
        QMessageBox::information(this, "消息", "数据保存错误,错误信息\n"+tabModel->lastError().text()+tabModel2->lastError().text(),
                                 QMessageBox::Ok,QMessageBox::NoButton);
    else
    {
        QMessageBox::information(NULL, "information", "保存成功", QMessageBox::Ok, QMessageBox::Ok);
    }

}

//选项卡切换函数
void MainWindow::on_tabWidget_currentChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
    if(tabModel!=NULL&&tabModel2!=NULL){
    if(index==0)
        getFieldNames(tabModel);
    else if(index==1)
        getFieldNames(tabModel2);
    }
}

//当前行单元格的变换
void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    //更新actPost和actCancel 的状态
    Q_UNUSED(current);
    Q_UNUSED(previous);
    ui->actSave->setEnabled(tabModel->isDirty()||tabModel2->isDirty()); //有未保存修改时可用;
}

//model1的行切换
void MainWindow::on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    dataMapper->setCurrentIndex(current.row()); //更细数据映射的行号
    int curRecNo=current.row();//获取行号
    QSqlRecord  curRec=tabModel->record(curRecNo); //获取当前记录
}

//model2的行切换
void MainWindow::on_currentRowChanged2(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    dataMapper2->setCurrentIndex(current.row()); //更细数据映射的行号
    int curRecNo=current.row();//获取行号
    QSqlRecord  curRec=tabModel2->record(curRecNo); //获取当前记录
}

//model3的行切换
void MainWindow::on_currentRowChanged3(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);
    dataMapper3->setCurrentIndex(current.row()); //更细数据映射的行号
    int curRecNo=current.row();//获取行号
    QSqlRecord  curRec=tabModel3->record(curRecNo); //获取当前记录
}


//获取排序字段
void MainWindow::getFieldNames(QSqlTableModel*& tabModel)
{
    //获取所有字段名称
    QSqlRecord  emptyRec=tabModel->record();//获取空记录，只有字段名
    ui->comboBox->clear();
    for (int i=0;i<emptyRec.count();i++)
        ui->comboBox->addItem(emptyRec.fieldName(i));
}

//升序按钮
void MainWindow::on_radioButton_clicked()
{
    if(ui->tabWidget->currentIndex()==0){
    tabModel->setSort(ui->comboBox->currentIndex(),Qt::AscendingOrder);
    tabModel->select();
    }
    else if(ui->tabWidget->currentIndex()==1){
        tabModel2->setSort(ui->comboBox->currentIndex(),Qt::AscendingOrder);
        tabModel2->select();
    }
}

//降序按钮
void MainWindow::on_radioButton_2_clicked()
{
    if(ui->tabWidget->currentIndex()==0){
    tabModel->setSort(ui->comboBox->currentIndex(),Qt::DescendingOrder);
    tabModel->select();
    }
    else if(ui->tabWidget->currentIndex()==1){
        tabModel2->setSort(ui->comboBox->currentIndex(),Qt::DescendingOrder);
        tabModel2->select();
    }
}

//筛选按钮
void MainWindow::on_radioButton_3_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
            tabModel->setFilter(" Gender='男' ");
    else if(ui->tabWidget->currentIndex()==1)
        tabModel2->setFilter(" Gender='男' ");
}

void MainWindow::on_radioButton_4_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
            tabModel->setFilter(" Gender='女' ");
    else if(ui->tabWidget->currentIndex()==1)
        tabModel2->setFilter(" Gender='女' ");
}

void MainWindow::on_radioButton_5_clicked()
{
    if(ui->tabWidget->currentIndex()==0)
            tabModel->setFilter("");
    else if(ui->tabWidget->currentIndex()==1)
        tabModel2->setFilter("");
}



//界面右槽函数
void MainWindow::on_StuNo_textEdited(const QString &arg1)
{
    int row=tabModel->rowCount(),i;
    QModelIndex curIndex=theSelection->currentIndex();//获取当前选择单元格的模型索引
    QModelIndex indexA=tabModel->index(curIndex.row(),0,QModelIndex());
    for(i=0;i<row;i++)
        if(arg1!=tabModel->data(indexA,Qt::EditRole).toString()&&arg1==tabModel->data(tabModel->index(i,0,QModelIndex()),Qt::EditRole).toString())
            break;
    if(i<row)
        ui->tipNo->setText("学号已存在");
    else if(arg1.length()<6)
        ui->tipNo->setText("学号应为6位");
    else{
        ui->tipNo->setText("");
        for(i=0;i<row;i++)
            if(tabModel->data(indexA,Qt::EditRole).toString()==tabModel2->data(tabModel2->index(i,0,QModelIndex()),Qt::EditRole).toString())
                break;
        tabModel2->setData(tabModel2->index(i,0,QModelIndex()),arg1,Qt::EditRole);
    }
}

void MainWindow::on_Name_textEdited(const QString &arg1)
{
    int row=tabModel->rowCount(),i;
    QModelIndex curIndex=theSelection->currentIndex();//获取当前选择单元格的模型索引
    QModelIndex indexA=tabModel->index(curIndex.row(),0,QModelIndex());
    for(i=0;i<row;i++)
        if(tabModel->data(indexA,Qt::EditRole).toString()==tabModel2->data(tabModel2->index(i,0,QModelIndex()),Qt::EditRole).toString())
            break;
    tabModel2->setData(tabModel2->index(i,1,QModelIndex()),arg1,Qt::EditRole);
    if(arg1=="")
        ui->tipName->setText("姓名不能为空/不超过5个字");
    else
        ui->tipName->setText("");
}

void MainWindow::on_Gender_currentTextChanged(const QString &arg1)
{
    int row=tabModel->rowCount(),i;
    QModelIndex curIndex=theSelection->currentIndex();//获取当前选择单元格的模型索引
    QModelIndex indexA=tabModel->index(curIndex.row(),0,QModelIndex());
    for(i=0;i<row;i++)
        if(tabModel->data(indexA,Qt::EditRole).toString()==tabModel2->data(tabModel2->index(i,0,QModelIndex()),Qt::EditRole).toString())
            break;
    tabModel2->setData(tabModel2->index(i,2,QModelIndex()),arg1,Qt::EditRole);
}


void MainWindow::on_StuNo2_textEdited(const QString &arg1)
{
    int row=tabModel2->rowCount(),i;
    QModelIndex curIndex=theSelection2->currentIndex();//获取当前选择单元格的模型索引
    QModelIndex indexA=tabModel2->index(curIndex.row(),0,QModelIndex());
    for(i=0;i<row;i++)
        if(arg1!=tabModel2->data(indexA,Qt::EditRole).toString()&&arg1==tabModel2->data(tabModel2->index(i,0,QModelIndex()),Qt::EditRole).toString())
            break;
    if(i<row)
        ui->tipNo2->setText("学号已存在");
    else if(arg1.length()<6)
        ui->tipNo2->setText("学号应为6位");
    else{
        ui->tipNo2->setText("");
        for(i=0;i<row;i++)
            if(tabModel2->data(indexA,Qt::EditRole).toString()==tabModel->data(tabModel->index(i,0,QModelIndex()),Qt::EditRole).toString())
                break;
        tabModel->setData(tabModel->index(i,0,QModelIndex()),arg1,Qt::EditRole);
    }
}

void MainWindow::on_Name2_textEdited(const QString &arg1)
{
    int row=tabModel2->rowCount(),i;
    QModelIndex curIndex=theSelection2->currentIndex();//获取当前选择单元格的模型索引
    QModelIndex indexA=tabModel2->index(curIndex.row(),0,QModelIndex());
    for(i=0;i<row;i++)
        if(tabModel2->data(indexA,Qt::EditRole).toString()==tabModel->data(tabModel->index(i,0,QModelIndex()),Qt::EditRole).toString())
            break;
    tabModel->setData(tabModel->index(i,1,QModelIndex()),arg1,Qt::EditRole);
    if(arg1=="")
        ui->tipName2->setText("姓名不能为空");
    else
        ui->tipName2->setText("");
}

void MainWindow::on_Gender2_currentTextChanged(const QString &arg1)
{
    int row=tabModel2->rowCount(),i;
    QModelIndex curIndex=theSelection2->currentIndex();//获取当前选择单元格的模型索引
    QModelIndex indexA=tabModel2->index(curIndex.row(),0,QModelIndex());
    for(i=0;i<row;i++)
        if(tabModel2->data(indexA,Qt::EditRole).toString()==tabModel->data(tabModel->index(i,0,QModelIndex()),Qt::EditRole).toString())
            break;
    tabModel->setData(tabModel->index(i,2,QModelIndex()),arg1,Qt::EditRole);
}

void MainWindow::on_PhoneNumber_textChanged(const QString &arg1)
{
    if(arg1.length()<11)
        ui->tipPhone->setText("电话号码不正确");
    else
        ui->tipPhone->setText("");
}

