#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include "highlighter.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QCloseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QFontDialog>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QToolBar>
#include <QDateTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class notebook; }
QT_END_NAMESPACE

class notebook : public QMainWindow  //由QMainWindow派生的文本编辑器类
{
    Q_OBJECT

public:
    notebook(QWidget *parent = nullptr);  //构造函数
    ~notebook();  //析构函数

protected:
    void closeEvent(QCloseEvent *event);  //重写关闭事件

private slots:
    void FocusCurrentLine();  //聚焦本行
    void isChanged();  //检测文本改动

    void NewTextFile();  //新建文本文件
    void NewCppFile();  //新建C++文件
    void OpenFile();  //打开文件（根据后缀名判断文件类型）
    void SaveFile();  //保存文件
    void SaveAsFile();  //另存为
    void UnDo();  //撤销
    void ReDo();  //重做
    void Cut();  //剪切
    void Copy();  //复制
    void Paste();  //粘贴
    void SelectAll();
    void Find();  //查找
    void Replace();  //替换
    void Font();  //设置字体
    void Size();  //设置字体大小
    void Color();  //设置字体颜色
    void Bold();  //加粗
    void Italic();  //斜体
    void Underline();  //下划线
    void ClearFormat();  //清除格式
    void AlignLeft();  //左对齐
    void AlignCenter();  //居中
    void AlignRight();  //右对齐
    void About();  //关于
    void ZoomIn();  //放大
    void ZoomOut();  //缩小
    void Fullscreen();  //是否全屏
    void ReadOnly();  //是否只读
    void ShowTools();  //是否显示工具栏

    void LineNumUpdate();  //行数统计（右下角）
    void TimeUpdate();  //更新时间（左下角）

private:
    Ui::notebook *ui;
    QToolBar *toolBar = addToolBar(tr("toolBar"));  //工具栏
    QLabel *LineLabel = new QLabel();  //行数
    QLabel *TimeLabel = new QLabel();  //时间
    CppHighlighter *highlighter = nullptr;  //语法高亮

    QString filename = "";  //文本名

    void createUI();  //初始化界面
    void CloseModified();  //关闭已改动的文本
    void NewFile();  //新建文件
    void ReadFromFile(const QString &filepath);  //从文件写出
    void WriteToFile(const QString &filepath);  //写入文件
    void highLight();  //查找高亮
};

#endif // NOTEBOOK_H
