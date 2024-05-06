#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>     //专用于连接、创建数据库
#include <QSqlQuery>        //专用于DML(数据操作语言)、DDL(数据定义语言)
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTextEdit>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();





private slots:
    void on_pushButtonSort_clicked();

    void on_pushButton_FIND_clicked();

    void on_pushButton_INSERT_clicked();

    void on_pushButton_DELETE_clicked();

    void on_pushButton_UPDATE_clicked();


private: //自定义函数
    void CreateDatabaseFunc();   //创建SQLite数据库
    void CreateTableFunc();      //创建SQLite数据库
    void QueryTableFunc();       //执行查询操作

    QSqlDatabase sqldb;          //创建Qt和数据库链接
    QSqlQueryModel sqlmodel;     //存储结果集
    QSqlTableModel *m;           //创建表格模型
    QTextEdit *debugTextEdit;    //创建文本框
    QComboBox *comboBoxValue_sort;      //创建下拉框
    QComboBox *comboBoxOrder_sort;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
