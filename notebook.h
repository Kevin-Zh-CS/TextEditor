#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QLabel>
#include <QLineEdit>
#include <QFontDialog>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QToolBar>
#include <QWaitCondition>

QT_BEGIN_NAMESPACE
namespace Ui { class notebook; }
QT_END_NAMESPACE

class notebook : public QMainWindow
{
    Q_OBJECT

public:
    notebook(QWidget *parent = nullptr);
    ~notebook();
    void createUI();//初始化界面
    void highLight();
    QLabel *label = new QLabel();
    QLabel  *label1 = new QLabel();
private slots:
    void NewFile();//新建文件
    void OpenFile();//打开文件
    void SaveFile();//保存文件
    void SaveAsFile();//另存为
    void UnDo();//撤销
    void ReDo();//重做
    void Copy();//复制
    void Cut();//剪切
    void Paste();//粘贴
    void Find();//查找
    void Replace();//替换
    void Color();//颜色
    void Size();//字体大小
    void Font();//字体
    void AlignRight();//右对齐
    void AlignLeft();//左对齐
    void AlignCenter();//居中
    void About();//关于
    void Bold();//加粗
    void Italic();//斜体
    void Underline();//下划线
    void linenum();//行数统计
    void timeUpdate();//更新时间

private:
    Ui::notebook *ui;
};

#endif // NOTEBOOK_H
