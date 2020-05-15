#include "notebook.h"
#include <QFontDialog>
#include <QFont>
#include <QHBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

notebook::notebook(QWidget *parent)
    : QMainWindow(parent)
{
    createUI();//默认创建初始化界面
}

notebook::~notebook()
{
}

void notebook::createUI(){

    setCentralWidget(new QTextEdit);//创建文本编辑区
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
    findEdit = new QLineEdit;
    QPushButton *button = new QPushButton("Find");
    connect(button, &QPushButton::clicked, this, &notebook::highLight);
    layout->addWidget(label);
    layout->addWidget(findEdit);
    layout->addWidget(button);
    findDialog->setLayout(layout);
    findDialog->show();
}

void notebook::Replace(){

}

void notebook::Color(){

}

void notebook::Size(){

}

void notebook::Font(){
    bool flag;
    QFont font = QFontDialog::getFont(&flag, this);
    if(flag){
        textEdit->setFont(font);
    }
}

void notebook::AlignRight(){

}

void notebook::AlignLeft(){

}

void notebook::AlignCenter(){

}

void notebook::About(){

}
