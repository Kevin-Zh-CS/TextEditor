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
#include <QDateTime>
#include <QTimer>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class notebook; }
QT_END_NAMESPACE

class notebook : public QMainWindow
{
    Q_OBJECT

public:
    notebook(QWidget *parent = nullptr);
    ~notebook();

private slots:
    void isChanged();//检测文本是否改动
    void NewFile();//新建文件
    void OpenFile();//打开文件
    void SaveFile();//保存文件
    void SaveAsFile();//另存为
    void Exit();//退出
    void UnDo();//撤销
    void ReDo();//重做
    void Cut();//剪切
    void Copy();//复制
    void Paste();//粘贴
    void SelectAll();//全选
    void Find();//查找
    void Replace();//替换
    void Font();//字体
    void Size();//字体大小
    void Color();//颜色
    void Bold();//加粗
    void Italic();//斜体
    void Underline();//下划线
    void ClearFormat();//清除格式
    void AlignLeft();//左对齐
    void AlignCenter();//居中
    void AlignRight();//右对齐
    void About();//关于
    void ZoomIn();//放大
    void ZoomOut();//缩小
    void Fullscreen();//是否全屏
    void ShowTools();//是否显示工具栏
    void LineNum();//行数统计
    void TimeUpdate();//更新时间

private:
    Ui::notebook *ui;
    QToolBar *toolBar = addToolBar(tr("toolBar"));
    QLabel *LineLabel = new QLabel();
    QLabel *TimeLabel = new QLabel();

    QString filename = "";//文本名
    bool isTextChanged = false;//文本是否改动

    void createUI();//初始化界面
    void highLight();//高亮
    void closeEvent(QCloseEvent *event);//重载关闭事件
};

#endif // NOTEBOOK_H
