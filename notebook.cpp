#include "notebook.h"
#include "ui_notebook.h"
#include <QDoubleValidator>
#include <QTextBlock>
#include<QLabel>
#include<QDateTime>
#include<QTimer>
#include<QString>

static bool flagI=false;
static bool flagB=false;
static bool flagU=false;

notebook::notebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::notebook)
{
    createUI();//默认创建初始化界面
}

notebook::~notebook()
{
    delete ui;
}

void notebook::createUI(){
    ui->setupUi(this);

    QFont f("Microsoft YaHei",12);
    ui->textEdit->setFont(f);
    setCentralWidget(ui->textEdit);

    //文件菜单，后注释不赘述
    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionNew->setIcon(QIcon(":imgs/Image/new.png"));
    ui->actionNew->setStatusTip(tr("New input text."));
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(NewFile()));//创建连接，点击触发事件，调用对应函数

    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionOpen->setIcon(QIcon(":imgs/Image/open.png"));
    ui->actionOpen->setStatusTip(tr("Open existed file."));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(OpenFile()));

    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSave->setIcon(QIcon(":imgs/Image/save.png"));
    ui->actionSave->setStatusTip(tr("Save file."));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(SaveFile()));

    ui->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->actionSaveAs->setIcon(QIcon(":imgs/Image/save-as.png"));
    ui->actionSaveAs->setStatusTip(tr("Save file as another."));
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(SaveAsFile()));

    ui->actionCut->setShortcut(QKeySequence::Cut);
    ui->actionCut->setIcon(QIcon(":imgs/Image/cut.png"));
    ui->actionCut->setStatusTip(tr("Cut text."));
    connect(ui->actionCut, SIGNAL(triggered(bool)), this, SLOT(Cut()));

    ui->actionCopy->setShortcut(QKeySequence::Copy);
    ui->actionCopy->setIcon(QIcon(":imgs/Image/copy.png"));
    ui->actionCopy->setStatusTip(tr("Copy text."));
    connect(ui->actionCopy, SIGNAL(triggered(bool)), this, SLOT(Copy()));

    ui->actionPaste->setShortcut(QKeySequence::Paste);
    ui->actionPaste->setIcon(QIcon(":imgs/Image/paste.png"));
    ui->actionPaste->setStatusTip(tr("Paste text."));
    connect(ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(Paste()));

    ui->actionFind->setShortcut(QKeySequence::Find);
    ui->actionFind->setIcon(QIcon(":imgs/Image/find.png"));
    ui->actionFind->setStatusTip(tr("Find text."));
    connect(ui->actionFind, SIGNAL(triggered(bool)), this, SLOT(Find()));

    ui->actionReplace->setShortcut(QKeySequence::Replace);
    ui->actionReplace->setIcon(QIcon(":imgs/Image/replace.png"));
    ui->actionReplace->setStatusTip(tr("Replace text."));
    connect(ui->actionReplace, SIGNAL(triggered(bool)), this, SLOT(Replace()));

    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionUndo->setIcon(QIcon(":imgs/Image/undo.png"));
    ui->actionUndo->setStatusTip(tr("Undo operation."));
    connect(ui->actionUndo, SIGNAL(triggered(bool)), this, SLOT(UnDo()));

    ui->actionRedo->setShortcut(QKeySequence::Redo);
    ui->actionRedo->setIcon(QIcon(":imgs/Image/redo.png"));
    ui->actionRedo->setStatusTip(tr("Redo oepration."));
    connect(ui->actionRedo, SIGNAL(triggered(bool)), this, SLOT(ReDo()));

    ui->actionColor->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_C);
    ui->actionColor->setIcon(QIcon(":imgs/Image/color.png"));
    ui->actionColor->setStatusTip(tr("Change color."));
    connect(ui->actionColor, SIGNAL(triggered(bool)), this, SLOT(Color()));

    ui->actionSize->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_S);
    ui->actionSize->setIcon(QIcon(":imgs/Image/size.png"));
    ui->actionSize->setStatusTip(tr("Change size."));
    connect(ui->actionSize, SIGNAL(triggered(bool)), this, SLOT(Size()));

    ui->actionFont->setShortcut(Qt::CTRL + Qt::ALT + Qt::Key_F);
    ui->actionFont->setIcon(QIcon(":imgs/Image/font.png"));
    ui->actionFont->setStatusTip(tr("Change font."));
    connect(ui->actionFont, SIGNAL(triggered(bool)), this, SLOT(Font()));

    ui->actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    ui->actionAlignRight->setIcon(QIcon(":imgs/Image/right.png"));
    ui->actionAlignRight->setStatusTip(tr("Align right."));
    connect(ui->actionAlignRight, SIGNAL(triggered(bool)), this, SLOT(AlignRight()));

    ui->actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    ui->actionAlignLeft->setIcon(QIcon(":imgs/Image/left.png"));
    ui->actionAlignLeft->setStatusTip(tr("Align left."));
    connect(ui->actionAlignLeft, SIGNAL(triggered(bool)), this, SLOT(AlignLeft()));

    ui->actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    ui->actionAlignCenter->setIcon(QIcon(":imgs/Image/center.png"));
    ui->actionAlignCenter->setStatusTip(tr("Align center."));
    connect(ui->actionAlignCenter, SIGNAL(triggered(bool)), this, SLOT(AlignCenter()));

    ui->actionAbout->setShortcut(Qt::CTRL + Qt::Key_A);
    ui->actionAbout->setIcon(QIcon(":imgs/Image/about.png"));
    ui->actionAbout->setStatusTip(tr("About this project."));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(About()));

    QToolBar *toolBar = addToolBar(tr("toolBar"));
    toolBar->setStyleSheet("QToolBar{background-color:white}");
    toolBar->addAction(ui->actionUndo);
    toolBar->addAction(ui->actionRedo);
    toolBar->addSeparator();

    QAction *boldAction = new QAction(this);
    boldAction->setIcon(QIcon(":imgs/Image/bold.png"));
    boldAction->setShortcuts(QKeySequence::Bold);
    boldAction->setStatusTip(tr("Bold."));
    toolBar->addAction(boldAction);
    connect(boldAction, SIGNAL(triggered(bool)), this, SLOT(Bold()));

    QAction *italicAction = new QAction(this);
    italicAction->setIcon(QIcon(":imgs/Image/italic.png"));
    italicAction->setShortcuts(QKeySequence::Italic);
    italicAction->setStatusTip(tr("Italic."));
    toolBar->addAction(italicAction);
    connect(italicAction, SIGNAL(triggered(bool)), this, SLOT(Italic()));

    QAction *underlineAction = new QAction(this);
    underlineAction->setIcon(QIcon(":imgs/Image/underline.png"));
    underlineAction->setShortcuts(QKeySequence::Underline);
    underlineAction->setStatusTip(tr("Underline."));
    toolBar->addAction(underlineAction);
    connect(underlineAction, SIGNAL(triggered(bool)), this, SLOT(Underline()));

    QTimer *timer1=new QTimer(this);
    timer1->start(100); // 每次发射timeout信号时间间隔为100毫秒
    connect(timer1,SIGNAL(timeout()),this,SLOT(linenum()));

    QTimer *timer = new QTimer(this);
    timer->start(1000); // 每次发射timeout信号时间间隔为1秒
    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));

    toolBar->addSeparator();
    toolBar->addAction(ui->actionColor);
    toolBar->addAction(ui->actionSize);
    toolBar->addAction(ui->actionFont);

    toolBar->addSeparator();
    toolBar->addAction(ui->actionAlignLeft);
    toolBar->addAction(ui->actionAlignCenter);
    toolBar->addAction(ui->actionAlignRight);

    statusBar();
}

void notebook::highLight(){//查找高亮
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    ui->textEdit->setPalette(palette);
}

void notebook::NewFile(){
    ui->textEdit->clear();
}

void notebook::OpenFile(){
    QString filename = QFileDialog::getOpenFileName();

    if(filename.length() != 0)
    {
        QFile file(filename);
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->textEdit->setText(QString(file.readAll()));
        }
        else
            throw "could not open file.";
    }
}

void notebook::SaveFile(){
    QString output = ui->textEdit->toPlainText();
    QString filename = QFileDialog::getSaveFileName();

    if (filename.length() != 0){
        QFile file(filename);
        if(file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            out << output;
        }
        else
            throw "could not write file.";
    }
}

void notebook::SaveAsFile(){
    SaveFile();
}

void notebook::UnDo(){
    ui->textEdit->undo();
}

void notebook::ReDo(){
    ui->textEdit->redo();
}

void notebook::Copy(){
    ui->textEdit->copy();
}

void notebook::Cut(){
    ui->textEdit->cut();
}

void notebook::Paste(){
    ui->textEdit->paste();
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
                if(ui->textEdit->find(fd_str,QTextDocument::FindBackward))
                    highLight();
                else if(ui->textEdit->find(fd_str))
                {
                    ui->textEdit->find(fd_str,QTextDocument::FindBackward);
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
                if(ui->textEdit->find(fd_str))
                    highLight();
                else if(ui->textEdit->find(fd_str,QTextDocument::FindBackward))
                {
                    ui->textEdit->find(fd_str);
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
                QString doc = ui->textEdit->toPlainText();
                if(doc.indexOf(fd_str)==-1) QMessageBox::warning(NULL,"WARNING","Content \""+ fd_str + "\" not found",QMessageBox::Ok);
                else
                    {
                        doc = doc.replace(fd_str,rp_str);
                        ui->textEdit->setPlainText(doc);
                    }
                }
            );
}

void notebook::Color(){
    QTextCharFormat fmt;
    QColor clr = QColorDialog::getColor();
    ui->textEdit->setTextColor(clr);
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
                ui->textEdit->mergeCurrentCharFormat(fmt);
                }
            );
}

void notebook::Font(){
    bool flag;
    QTextCharFormat fmt;
    QFont font = QFontDialog::getFont(&flag, this);
    if(flag){
        fmt.setFont(font);
        ui->textEdit->mergeCurrentCharFormat(fmt);//修改选中字体修改日后输入字体
    }
}

void notebook::AlignRight(){
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void notebook::AlignLeft(){
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void notebook::AlignCenter(){
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void notebook::About(){
    QMessageBox::about(this, tr("About Application"), tr("The <b>Notebook</b> is created by <br>"
                                                         "<br>EleanoreEos"
                                                         "<br>Kevin-Zh-CS"
                                                         "<br>SJoJoK"
                                                         "<br>tjc1411"));
}

void notebook::Bold(){
    if(!flagB){
        ui->textEdit->setFontWeight(75);
        flagB=true;
    }
    else{
        ui->textEdit->setFontWeight(50);
        flagB=false;
    }
}

void notebook::Italic(){
    if(flagI==false){
        ui->textEdit->setFontItalic(true);
        flagI=true;
    }
    else{
        ui->textEdit->setFontItalic(false);
        flagI=false;
    }
}

void notebook::Underline(){
    if(!flagU){
        ui->textEdit->setFontUnderline(true);
        flagU=true;
    }
    else{
        ui->textEdit->setFontUnderline(false);
        flagU=false;
    }
}

void notebook::linenum(){
    int blocknumbers = ui->textEdit->document()->blockCount();
    QString Linenum = QString::number(blocknumbers, 10);

    Linenum="line"+Linenum;
    label->setText(Linenum);
    ui->statusbar->addPermanentWidget(label);
}


void notebook::timeUpdate(){

    QDateTime CurrentTime=QDateTime::currentDateTime();
    QString Timestr=CurrentTime.toString(" yyyy年-MM月-dd日 hh:mm:ss "); //设置显示的格式


    label1->setText(Timestr);
    ui->statusbar->addWidget(label1);
}
