#include "notebook.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QFont>
#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QValidator>

notebook::notebook(QWidget *parent)
    : QMainWindow(parent)
{
    createUI();//默认创建初始化界面
}

notebook::~notebook()
{
}

void notebook::createUI(){

    textEdit = new QTextEdit;
    setCentralWidget(textEdit);//创建文本编辑区
    QFont f("Microsoft YaHei",12);
    textEdit->setFont(f);
    QAction* action = nullptr;//初始化动作
    menuBar = new QMenuBar;//创建菜单栏

    //文件菜单，后注释不赘述
    fileMenu = new QMenu("File(&F)", menuBar);//ALT+F 可打开
    createAction(action, fileMenu, "New", Qt::CTRL + Qt::Key_N, ":imgs/Image/new.png");
    connect(action, SIGNAL(triggered()), this, SLOT(NewFile()));//创建连接，点击触发事件，调用对应函数
    fileMenu->addAction(action);
    createAction(action, fileMenu, "Open", Qt::CTRL + Qt::Key_O, ":imgs/Image/open.png");
    connect(action, SIGNAL(triggered()), this, SLOT(OpenFile()));
    fileMenu->addAction(action);
    createAction(action, fileMenu, "Save", Qt::CTRL + Qt::Key_S, ":imgs/Image/save.png");
    connect(action, SIGNAL(triggered()), this, SLOT(SaveFile()));
    fileMenu->addAction(action);
    createAction(action, fileMenu, "Save As", Qt::CTRL + Qt::SHIFT + Qt::Key_S, ":imgs/Image/save-as.png");
    connect(action, SIGNAL(triggered()), this, SLOT(SaveAsFile()));
    fileMenu->addAction(action);


    editMenu = new QMenu("Edit(&E)", menuBar);
    createAction(action, editMenu, "Cut", Qt::CTRL + Qt::Key_X, ":imgs/Image/cut.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Cut()));
    editMenu->addAction(action);
    createAction(action, editMenu, "Copy", Qt::CTRL + Qt::Key_C, ":imgs/Image/copy.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Copy()));
    editMenu->addAction(action);
    createAction(action, editMenu, "Paste", Qt::CTRL + Qt::Key_V, ":imgs/Image/paste.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Paste()));
    editMenu->addAction(action);
    createAction(action, editMenu, "Find", Qt::CTRL + Qt::Key_F, ":imgs/Image/find.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Find()));
    editMenu->addAction(action);
    createAction(action, editMenu, "Replace", Qt::CTRL + Qt::Key_H, ":imgs/Image/replace.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Replace()));
    editMenu->addAction(action);
    createAction(action, editMenu, "Undo", Qt::CTRL + Qt::Key_Z, ":imgs/Image/undo.png");
    connect(action, SIGNAL(triggered()), this, SLOT(UnDo()));
    editMenu->addAction(action);
    createAction(action, editMenu, "Redo", Qt::CTRL + Qt::Key_Y, ":imgs/Image/redo.png");
    connect(action, SIGNAL(triggered()), this, SLOT(ReDo()));
    editMenu->addAction(action);


    formatMenu = new QMenu("Format(&M)", menuBar);
    createAction(action, formatMenu, "Color", Qt::CTRL + Qt::ALT + Qt::Key_C, ":imgs/Image/color.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Color()));
    formatMenu->addAction(action);
    createAction(action, formatMenu, "Size", Qt::CTRL + Qt::ALT + Qt::Key_S,":imgs/Image/size.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Size()));
    formatMenu->addAction(action);
    createAction(action, formatMenu, "Font", Qt::CTRL + Qt::ALT + Qt::Key_F, ":imgs/Image/font.png");
    connect(action, SIGNAL(triggered()), this, SLOT(Font()));
    formatMenu->addAction(action);


    paragraphMenu = new QMenu("Paragraph(&P)", menuBar);
    createAction(action, paragraphMenu, "Align right", Qt::CTRL + Qt::Key_R, ":imgs/Image/right.png");
    connect(action, SIGNAL(triggered()), this, SLOT(AlignRight()));
    paragraphMenu->addAction(action);
    createAction(action, paragraphMenu, "Align left", Qt::CTRL + Qt::Key_L, ":imgs/Image/left.png");
    connect(action, SIGNAL(triggered()), this, SLOT(AlignLeft()));
    paragraphMenu->addAction(action);
    createAction(action, paragraphMenu, "Align center", Qt::CTRL + Qt::Key_E, ":imgs/Image/center.png");
    connect(action, SIGNAL(triggered()), this, SLOT(AlignCenter()));
    paragraphMenu->addAction(action);


    helpMenu = new QMenu("Help(&F)", menuBar);
    createAction(action, helpMenu, "About", Qt::CTRL + Qt::Key_A, ":imgs/Image/about.png");
    connect(action, SIGNAL(triggered()), this, SLOT(About()));
    helpMenu->addAction(action);

    //将菜单加入菜单栏
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(formatMenu);
    menuBar->addMenu(paragraphMenu);
    menuBar->addMenu(helpMenu);

    this->setMenuBar(menuBar);
    resize(1000,800);//初始窗口大小，也可全屏

}

void notebook::createAction(QAction*& action, QWidget* parent, QString instance, int shortCut, QString iconPath){
    action = new QAction(instance, parent);//动作
    action->setShortcut(QKeySequence(shortCut));//快捷键
    action->setIcon(QIcon(iconPath));//图片路径
}

void notebook::highLight(){//查找高亮
    QPalette palette = textEdit->palette();
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    textEdit->setPalette(palette);
}

void notebook::NewFile(){

}

void notebook::OpenFile(){

}

void notebook::SaveFile(){

}

void notebook::SaveAsFile(){

}

void notebook::UnDo(){

}

void notebook::ReDo(){

}

void notebook::Copy(){

}

void notebook::Cut(){

}

void notebook::Paste(){

}

void notebook::Find(){

    QHBoxLayout *layout = new QHBoxLayout;
    QDialog *findDialog = new QDialog(this);
    QLabel *label = new QLabel("Content");
    QLineEdit *findEdit = new QLineEdit;
    QPushButton *buttonl = new QPushButton("Previous");
    QPushButton *buttonn = new QPushButton("Next");
    layout->addWidget(label);
    layout->addWidget(findEdit);
    layout->addWidget(buttonl);
    layout->addWidget(buttonn);
    findDialog->setLayout(layout);
    findDialog->setWindowTitle("Find");
    findDialog->show();
    connect(buttonl,
            &QPushButton::clicked,
            this,
            [=]{
                QString fd_str=findEdit->text();
                if(fd_str=="") QMessageBox::warning(NULL,"WARNING","Content can not be empty",QMessageBox::Ok);
                if(textEdit->find(fd_str,QTextDocument::FindBackward))
                    highLight();
                else if(textEdit->find(fd_str))
                {
                    textEdit->find(fd_str,QTextDocument::FindBackward);
                    QMessageBox::warning(NULL,"WARNING","It's the first found word",QMessageBox::Ok);
                }
                else
                    QMessageBox::warning(NULL,"WARNING","Content \""+ fd_str + "\" not found",QMessageBox::Ok);
                }
            );
    connect(buttonn,
            &QPushButton::clicked,
            this,
            [=]{
                QString fd_str=findEdit->text();
                if(fd_str=="") QMessageBox::warning(NULL,"WARNING","Content can not be empty",QMessageBox::Ok);
                if(textEdit->find(fd_str))
                    highLight();
                else if(textEdit->find(fd_str,QTextDocument::FindBackward))
                {
                    textEdit->find(fd_str);
                    QMessageBox::warning(NULL,"WARNING","It's the first found word",QMessageBox::Ok);
                }
                else
                    QMessageBox::warning(NULL,"WARNING","Content \""+ fd_str + "\" not found",QMessageBox::Ok);
                }
            );
}

void notebook::Replace(){
    QHBoxLayout *layout = new QHBoxLayout;
    QDialog *ReplaceDialog = new QDialog(this);
    QLabel *Rlabel = new QLabel("Replace");
    QLabel *Wlabel = new QLabel("with");
    QLineEdit *findEdit = new QLineEdit;
    QLineEdit *ReplaceEdit = new QLineEdit;
    QPushButton *button = new QPushButton("Replace");
    layout->addWidget(Rlabel);
    layout->addWidget(findEdit);
    layout->addWidget(Wlabel);
    layout->addWidget(ReplaceEdit);
    layout->addWidget(button);
    ReplaceDialog->setLayout(layout);
    ReplaceDialog->show();
    connect(button,
            &QPushButton::clicked,
            this,
            [=]{
                QString fd_str=findEdit->text();
                QString rp_str=ReplaceEdit->text();
                QString doc = textEdit->toPlainText();
                if(doc.indexOf(fd_str)==-1) QMessageBox::warning(NULL,"WARNING","Content \""+ fd_str + "\" not found",QMessageBox::Ok);
                else
                    {
                        doc = doc.replace(fd_str,rp_str);
                        textEdit->setPlainText(doc);
                    }
                }
            );
}

void notebook::Color(){
    QTextCharFormat fmt;
    QColor clr = QColorDialog::getColor();
    textEdit->setTextColor(clr);
}

void notebook::Size(){
    QHBoxLayout *layout = new QHBoxLayout;
    QDialog *SizeDialog = new QDialog(this);
    QLabel *Slabel = new QLabel("Size");
    QLineEdit *sizeEdit = new QLineEdit;
    QDoubleValidator* val = new QDoubleValidator;
    val->setRange(0, 1000);//限定范围，且只能输入浮点数
    sizeEdit->setValidator(val);
    QPushButton *button = new QPushButton("Set");
    layout->addWidget(Slabel);
    layout->addWidget(sizeEdit);
    layout->addWidget(button);
    SizeDialog->setLayout(layout);
    SizeDialog->show();
    connect(button,
            &QPushButton::clicked,
            this,
            [=]{
                QTextCharFormat fmt;
                QString fd_str=sizeEdit->text();
                fmt.setFontPointSize(fd_str.toDouble());
                textEdit->mergeCurrentCharFormat(fmt);
                }
            );
}

void notebook::Font(){
    bool flag;
    QTextCharFormat fmt;
    QFont font = QFontDialog::getFont(&flag, this);
    if(flag){
        fmt.setFont(font);
        textEdit->mergeCurrentCharFormat(fmt);//修改选中字体修改日后输入字体
    }
}

void notebook::AlignRight(){
    textEdit->setAlignment(Qt::AlignRight);
}

void notebook::AlignLeft(){
    textEdit->setAlignment(Qt::AlignLeft);
}

void notebook::AlignCenter(){
    textEdit->setAlignment(Qt::AlignCenter);
}

void notebook::About(){
    QMessageBox::about(this, tr("About Application"), tr("The <b>Notebook</b> is created by <br>"
                                                         "<br>EleanoreEos"
                                                         "<br>Kevin-Zh-CS"
                                                         "<br>SJoJoK"
                                                         "<br>tjc1411"));
}
