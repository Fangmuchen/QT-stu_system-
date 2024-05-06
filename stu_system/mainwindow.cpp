#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //调用函数创建数据库
    CreateDatabaseFunc();
    //调用函数创建数据表
    //CreateTableFunc();

    debugTextEdit = new QTextEdit;
    // 关联debugTextEdit与Qt Designer中的TextEdit
    debugTextEdit = ui->TextEdit;


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateDatabaseFunc()  //创建SQLite数据库
{
    // 1、添加数据库驱动
    sqldb=QSqlDatabase::addDatabase("QSQLITE");

    // 2、设置数据库名称
    sqldb.setDatabaseName("studentmis.db");

    // 3、打开此数据库是否成功
    if(sqldb.open()==true)
    {
        QMessageBox::information(0,"正确","恭喜你，数据库打开成功！",QMessageBox::Ok);
        //将数据库和tableview联系起来
        m = new QSqlTableModel;
        m->setTable("student");
        ui->tableView->setModel(m);

    }
    else
    {
        QMessageBox::critical(0,"错误","数据库打开失败，请重新检测！",QMessageBox::Ok);
    }
}

void MainWindow::CreateTableFunc()     //创建SQLite数据表
{
    QSqlQuery createquery;
    //创建SQL语句
    QString strsql=QString("create table student("
                           "id int primary key not null,"
                            "name text not null,"
                           "score real not null)");
    //执行SQL语句
    if(createquery.exec(strsql)==false)
    {
        QMessageBox::critical(0,"失败","数据表创建失败，请重新检测！",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(0,"成功","恭喜你，数据表创建成功！",QMessageBox::Ok);

    }
}
void MainWindow::QueryTableFunc()      //执行排序操作
{
    debugTextEdit->append(QString("改功能还未完成！"));
}

//排序
void MainWindow::on_pushButtonSort_clicked()
{
    QueryTableFunc();
}

//插入
void MainWindow::on_pushButton_INSERT_clicked()
{
    QSqlQuery sqlquery;

    int id=ui->lineEdit_ID->text().toInt();
    if(id==0)
    {
        QMessageBox::critical(this,"错误","提示：输入错误？学号不能为0?",QMessageBox::Ok);
        return ;
    }

    QString name=ui->lineEdit_NAME->text();
    if(name=="")
    {
        QMessageBox::critical(this,"错误","提示：输入错误？姓名不能为空?",QMessageBox::Ok);
        return ;
    }

    double score=ui->lineEdit_SCORE->text().toDouble();
    if(score<0||score>100)
    {
        QMessageBox::critical(this,"错误","提示：输入错误？分数（0-100）?",QMessageBox::Ok);
        return ;
    }

    QString strs=QString("insert into student "
                         "values(%1,'%2',%3)").arg(id).arg(name).arg(score);
    if(sqlquery.exec(strs)==false)
    {
        QMessageBox::critical(0,"失败","向数据库插入记录失败，请重新操作！",QMessageBox::Ok);
    }
    else
    {
        QMessageBox::information(0,"成功","恭喜你，向数据库插入记录成功！",QMessageBox::Ok);
        ui->lineEdit_ID->clear(); // 清除学号输入框
        ui->lineEdit_NAME->clear(); // 清除姓名输入框
        ui->lineEdit_SCORE->clear(); // 清除成绩输入框
    }


}

//删除
void MainWindow::on_pushButton_DELETE_clicked()
{
    // 假设 ui->lineEdit_ID 是用户输入学号的 QLineEdit 控件
    int studentId = ui->lineEdit_ID->text().toInt();

    // 准备SQL删除语句，使用参数化查询
    QString deleteSql = QString("DELETE FROM student WHERE id = %1").arg(studentId);

    QSqlQuery deleteQuery;
    if (deleteQuery.exec(deleteSql)) {
        // 如果删除成功，可以在这里更新UI，如清除输入框或刷新表格显示
        ui->lineEdit_ID->clear(); // 清除学号输入框
        // 刷新表格显示或其他相关UI更新
        QMessageBox::information(this, "成功", "学生记录删除成功！");
    } else {
        // 如果删除失败，显示错误信息
        QMessageBox::critical(this, "失败", "学生记录删除失败: " + deleteQuery.lastError().text());
    }
}

//查询
void MainWindow::on_pushButton_FIND_clicked()
{

    QSqlQuery sqlquery;

    // 从UI组件获取学号并检查是否为0
    int id = ui->lineEdit_ID->text().toInt();
    if(id == 0) {
        QMessageBox::critical(this, "错误", "提示：学号不能为0。", QMessageBox::Ok);
        return;
    }

    // 假设 ui->lineEdit_ID 是一个 QLineEdit 控件，用户在其中输入了学号
    int studentId = ui->lineEdit_ID->text().toInt();

    // 使用参数化查询来防止SQL注入
    QString sqlqueryString = QString("SELECT name,id,score FROM student WHERE id = %1");

    sqlquery.prepare(sqlqueryString.arg(studentId));

    if(sqlquery.exec())
     {
        // 遍历查询结果
        if (sqlquery.next()) {

            // 获取数据库的数据

            int ID = sqlquery.value("id").toInt();
            QString name = sqlquery.value("name").toString();
            float score = sqlquery.value("score").toFloat();

            // 在这里处理结果，例如显示在UI上或存储在变量中
            qDebug() << "ID:" << ID;
            qDebug() << "Name:" << name;
            qDebug() << "Score:" << score;

            //在文本框中输出
            debugTextEdit->append(QString("ID:%2\tName:%3\tscore:%4").arg(ID).arg(name).arg(score));
            ui->lineEdit_ID->clear(); // 清除学号输入框

        }

        else {
               // 如果没有找到匹配的记录，可以给用户相应的提示
               qDebug() << "No student found with ID" << studentId;
               debugTextEdit->append(QString("No student found with ID!"));
             }
    }
        else
        {
           // 查询执行失败，可以给用户相应的错误提示
           qDebug() << "Error executing query:" << sqlquery.lastError();
           debugTextEdit->append(QString("Error executing query!"));
        }

}

//更新
void MainWindow::on_pushButton_UPDATE_clicked()
{
    m->select();
}