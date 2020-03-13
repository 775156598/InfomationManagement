#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include  <QMainWindow>
#include    <QLabel>
#include    <QString>
#include    <QtSql>
#include    <QDataWidgetMapper>
#include    <QComboBox>
#include    <QFileDialog>
#include    <QDialog>
#include    <searchdialog.h>
#include    <showinfo.h>
#include    <addinfo.h>
#include    <QSqlQueryModel>
#include    <QSqlQuery>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();\
    QSqlTableModel  *tabModel=NULL;  //数据模型
    QSqlTableModel  *tabModel2=NULL;  //数据模型
    QSqlQueryModel  *tabModel3;
    void InputFormer();//(界面右的输入格式，使用正则表达式)
    void getFieldNames(QSqlTableModel*& tabModel);//获取字段名称,填充“排序字段”的comboBox

private slots:
    void on_actOpenDB_triggered();
    void on_actSearch_triggered();
    void on_actSave_triggered();
    void on_actDelete_triggered();
    void on_actAdd_triggered();
    void on_actCancel_triggered();
    void on_actShow_triggered();

    //界面左选项卡改变的槽函数
    void on_tabWidget_currentChanged(int index);
    // QTableView的SelectionModel的行发生了变化，进行处理
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_currentRowChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_currentRowChanged2(const QModelIndex &current, const QModelIndex &previous);
    void on_currentRowChanged3(const QModelIndex &current, const QModelIndex &previous);

    //排序和筛选
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_radioButton_5_clicked();

    //界面右的槽函数
    void on_StuNo_textEdited(const QString &arg1);
    void on_Name_textEdited(const QString &arg1);
    void on_Gender_currentTextChanged(const QString &arg1);
    void on_StuNo2_textEdited(const QString &arg1);
    void on_Name2_textEdited(const QString &arg1);
    void on_Gender2_currentTextChanged(const QString &arg1);
    void on_PhoneNumber_textChanged(const QString &arg1);   

private:
    Ui::MainWindow *ui;
    QSqlDatabase  DB;//数据库连接
    QItemSelectionModel *theSelection; //选择模型1
    QItemSelectionModel *theSelection2; //选择模型2
    QItemSelectionModel *theSelection3; //选择模型3
    QDataWidgetMapper   *dataMapper; //数据映射1
    QDataWidgetMapper   *dataMapper2; //数据映射2
    QDataWidgetMapper   *dataMapper3; //数据映射3

    void    openTable();//打开数据表

    //子对话框
    SearchDialog *sd;
    addinfo *info;
    showinfo *showAll;
};

#endif // MAINWINDOW_H
