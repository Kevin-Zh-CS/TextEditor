#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTextEdit>
#include <QString>
#include <QDialog>
#include <QLineEdit>

class notebook : public QMainWindow
{
    Q_OBJECT

public:
    notebook(QWidget *parent = nullptr);
    ~notebook();
    void createUI();//初始化界面
    void createAction(QAction*& action, QWidget* parent, QString instance, int shortCut,QString iconPath);
    void highLight();

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

private:
    QMenuBar *menuBar;//菜单栏

    QTextEdit *textEdit;//文本框
    QLineEdit *findEdit;//查找文本框

    QMenu *fileMenu;//文件菜单
    QMenu *editMenu;//编辑菜单
    QMenu *formatMenu;//格式菜单
    QMenu *paragraphMenu;//段落菜单
    QMenu *helpMenu;//帮助菜单
};
#endif // NOTEBOOK_H
