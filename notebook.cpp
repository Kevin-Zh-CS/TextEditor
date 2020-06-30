#include "notebook.h"
#include "ui_notebook.h"

static bool flagB = false;  //加粗
static bool flagI = false;  //斜体
static bool flagU = false;  //下划线
static bool isTextChanged = false;  //文本是否改动

//构造函数
notebook::notebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::notebook)
{
    createUI();  //创建初始化界面
}

//析构函数
notebook::~notebook()
{
    delete ui;
}

//初始化界面
void notebook::createUI()
{
    ui->setupUi(this);

    /***********文本框*************/

    setCentralWidget(ui->textEdit);  //设为中心窗口
    ui->textEdit->setStyleSheet("QTextEdit{border:1px groove gray;border-radius:10px;padding:2px 4px}");  //设置样式
    QFont defaultFont("Anonymous Pro", 12);  //默认字体
    ui->textEdit->setFont(defaultFont);
    QFontMetrics metrics(ui->textEdit->font());  //Tab缩进
    ui->textEdit->setTabStopWidth(4 * metrics.width(' '));
    connect(ui->textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(FocusCurrentLine()));  //聚焦本行
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(isChanged()));  //检测文本改动

    /***********菜单栏*************/

    //File
    ui->actionTextFile->setShortcut(QKeySequence::New);  //新建文本文件 快捷键
    ui->actionTextFile->setIcon(QIcon(":imgs/Image/new.png"));  //图标
    connect(ui->actionTextFile, SIGNAL(triggered(bool)), this, SLOT(NewTextFile()));  //触发函数

    ui->actionCppFile->setShortcut(Qt::CTRL + Qt::SHIFT + Qt::Key_N);  //新建C++文件
    connect(ui->actionCppFile, SIGNAL(triggered(bool)), this, SLOT(NewCppFile()));

    ui->actionOpen->setShortcut(QKeySequence::Open);  //打开
    ui->actionOpen->setIcon(QIcon(":imgs/Image/open.png"));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(OpenFile()));

    ui->actionSave->setShortcut(QKeySequence::Save);  //保存
    ui->actionSave->setIcon(QIcon(":imgs/Image/save.png"));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(SaveFile()));

    ui->actionSaveAs->setIcon(QIcon(":imgs/Image/save-as.png"));  //另存为
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(SaveAsFile()));

    ui->actionExit->setShortcut(Qt::Key_Escape);  //退出
    ui->actionExit->setIcon(QIcon(":imgs/Image/exit.png"));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));

    //Edit
    ui->actionUndo->setShortcut(QKeySequence::Undo);  //撤销
    ui->actionUndo->setIcon(QIcon(":imgs/Image/undo.png"));
    connect(ui->actionUndo, SIGNAL(triggered(bool)), this, SLOT(UnDo()));

    ui->actionRedo->setShortcut(QKeySequence::Redo);  //重做
    ui->actionRedo->setIcon(QIcon(":imgs/Image/redo.png"));
    connect(ui->actionRedo, SIGNAL(triggered(bool)), this, SLOT(ReDo()));

    ui->actionCut->setShortcut(QKeySequence::Cut);  //剪切
    ui->actionCut->setIcon(QIcon(":imgs/Image/cut.png"));
    connect(ui->actionCut, SIGNAL(triggered(bool)), this, SLOT(Cut()));

    ui->actionCopy->setShortcut(QKeySequence::Copy);  //复制
    ui->actionCopy->setIcon(QIcon(":imgs/Image/copy.png"));
    connect(ui->actionCopy, SIGNAL(triggered(bool)), this, SLOT(Copy()));

    ui->actionPaste->setShortcut(QKeySequence::Paste);  //粘贴
    ui->actionPaste->setIcon(QIcon(":imgs/Image/paste.png"));
    connect(ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(Paste()));

    ui->actionSelectAll->setShortcut(QKeySequence::SelectAll);  //全选
    ui->actionSelectAll->setIcon(QIcon(":imgs/Image/select-all.png"));
    connect(ui->actionSelectAll, SIGNAL(triggered(bool)), this, SLOT(SelectAll()));

    ui->actionFind->setShortcut(QKeySequence::Find);  //查找
    ui->actionFind->setIcon(QIcon(":imgs/Image/find.png"));
    connect(ui->actionFind, SIGNAL(triggered(bool)), this, SLOT(Find()));

    ui->actionReplace->setShortcut(QKeySequence::Replace);  //替换
    ui->actionReplace->setIcon(QIcon(":imgs/Image/replace.png"));
    connect(ui->actionReplace, SIGNAL(triggered(bool)), this, SLOT(Replace()));

    //Format
    ui->actionFont->setIcon(QIcon(":imgs/Image/font.png"));  //字体
    connect(ui->actionFont, SIGNAL(triggered(bool)), this, SLOT(Font()));

    ui->actionSize->setIcon(QIcon(":imgs/Image/size.png"));  //字号
    connect(ui->actionSize, SIGNAL(triggered(bool)), this, SLOT(Size()));

    ui->actionColor->setIcon(QIcon(":imgs/Image/color.png"));  //颜色
    connect(ui->actionColor, SIGNAL(triggered(bool)), this, SLOT(Color()));

    ui->actionBold->setShortcut(QKeySequence::Bold);  //加粗
    ui->actionBold->setIcon(QIcon(":imgs/Image/bold.png"));
    connect(ui->actionBold, SIGNAL(triggered(bool)), this, SLOT(Bold()));

    ui->actionItalic->setShortcut(QKeySequence::Italic);  //斜体
    ui->actionItalic->setIcon(QIcon(":imgs/Image/italic.png"));
    connect(ui->actionItalic, SIGNAL(triggered(bool)), this, SLOT(Italic()));

    ui->actionUnderline->setShortcut(QKeySequence::Underline);  //下划线
    ui->actionUnderline->setIcon(QIcon(":imgs/Image/underline.png"));
    connect(ui->actionUnderline, SIGNAL(triggered(bool)), this, SLOT(Underline()));

    ui->actionClearFormat->setShortcut(Qt::CTRL + Qt::Key_Q);  //清除格式
    ui->actionClearFormat->setIcon(QIcon(":imgs/Image/clear-format.png"));
    connect(ui->actionClearFormat, SIGNAL(triggered(bool)), this, SLOT(ClearFormat()));

    //Paragraph
    ui->actionAlignLeft->setIcon(QIcon(":imgs/Image/left.png"));  //左对齐
    connect(ui->actionAlignLeft, SIGNAL(triggered(bool)), this, SLOT(AlignLeft()));

    ui->actionAlignCenter->setIcon(QIcon(":imgs/Image/center.png"));  //居中
    connect(ui->actionAlignCenter, SIGNAL(triggered(bool)), this, SLOT(AlignCenter()));

    ui->actionAlignRight->setIcon(QIcon(":imgs/Image/right.png"));  //右对齐
    connect(ui->actionAlignRight, SIGNAL(triggered(bool)), this, SLOT(AlignRight()));

    //Help
    ui->actionAbout->setIcon(QIcon(":imgs/Image/about.png"));  //关于
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(About()));

    ui->actionZoomIn->setShortcut(QKeySequence::ZoomIn);  //放大
    ui->actionZoomIn->setIcon(QIcon(":imgs/Image/zoom-in.png"));
    connect(ui->actionZoomIn, SIGNAL(triggered(bool)), this, SLOT(ZoomIn()));

    ui->actionZoomOut->setShortcut(QKeySequence::ZoomOut);  //缩小
    ui->actionZoomOut->setIcon(QIcon(":imgs/Image/zoom-out.png"));
    connect(ui->actionZoomOut, SIGNAL(triggered(bool)), this, SLOT(ZoomOut()));

    ui->actionFullscreen->setShortcut(QKeySequence::FullScreen);  //全屏
    connect(ui->actionFullscreen, SIGNAL(triggered(bool)), this, SLOT(Fullscreen()));

    ui->actionReadOnly->setShortcut(Qt::CTRL + Qt::Key_R);  //只读
    connect(ui->actionReadOnly, SIGNAL(triggered(bool)), this, SLOT(ReadOnly()));

    ui->actionShowTools->setShortcut(Qt::CTRL + Qt::Key_T);  //显示工具栏
    connect(ui->actionShowTools, SIGNAL(triggered(bool)), this, SLOT(ShowTools()));

    /***********工具栏*************/

    toolBar->setStyleSheet("QToolBar{background-color:white}");  //设置样式
    //File
    toolBar->addAction(ui->actionTextFile);  //新建文本文件
    toolBar->addAction(ui->actionOpen);  //打开
    toolBar->addAction(ui->actionSave);  //保存
    toolBar->addSeparator();  //分割线
    //Edit
    toolBar->addAction(ui->actionUndo);  //撤销
    toolBar->addAction(ui->actionRedo);  //重做
    toolBar->addSeparator();
    toolBar->addAction(ui->actionFind);  //查找
    toolBar->addAction(ui->actionReplace);  //替换
    toolBar->addSeparator();
    //Format
    toolBar->addAction(ui->actionBold);  //加粗
    toolBar->addAction(ui->actionItalic);  //斜体
    toolBar->addAction(ui->actionUnderline);  //下划线
    toolBar->addSeparator();
    toolBar->addAction(ui->actionFont);  //字体
    toolBar->addAction(ui->actionSize);  //字号
    toolBar->addAction(ui->actionColor);  //颜色
    toolBar->addSeparator();
    toolBar->addAction(ui->actionClearFormat);  //清除格式
    toolBar->addSeparator();
    //Paragraph
    toolBar->addAction(ui->actionAlignLeft);  //左对齐
    toolBar->addAction(ui->actionAlignCenter);  //居中
    toolBar->addAction(ui->actionAlignRight);  //右对齐

    /***********状态栏*************/

    statusBar();

    //行号
    QTimer *lineTimer=new QTimer(this);
    lineTimer->start(100);
    connect(lineTimer,SIGNAL(timeout()),this,SLOT(LineNumUpdate()));

    //时间
    QTimer *timer = new QTimer(this);
    timer->start(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(TimeUpdate()));
}

/******************************************
                文本框
******************************************/

//聚焦本行
void notebook::FocusCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelection;
    QTextEdit::ExtraSelection selection;
    QColor lineColor = QColor(Qt::gray).lighter(150);

    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection,true);
    selection.cursor = ui->textEdit->textCursor();
    selection.cursor.clearSelection();
    extraSelection.append(selection);

    ui->textEdit->setExtraSelections(extraSelection);
}

//检测文本改动
void notebook::isChanged()
{
    if(!isTextChanged)  //更改标题
        setWindowTitle("*" + windowTitle());

    isTextChanged = true;
}

/******************************************
                菜单栏
******************************************/

void notebook::NewTextFile(){
    NewFile();

    if(highlighter != nullptr)  //清除语法高亮
        highlighter->clearHighlight();
}

void notebook::NewCppFile(){
    NewFile();

    highlighter = new CppHighlighter(ui->textEdit->document());  //添加语法高亮
}

void notebook::CloseModified()
{
    if(isTextChanged)  //是否保存
    {
        int result = QMessageBox::question(this, tr("Modified"), tr("Do you want to save this file?"), QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape);
        if (result == QMessageBox::Yes)
            SaveFile();
    }
}

void notebook::NewFile(){
    CloseModified();

    ui->textEdit->clear();  //清空内容
    filename = "";
    isTextChanged = false;
    setWindowTitle("Untitled - Notebook");
}

void notebook::OpenFile(){
    CloseModified();

    QString filepath = QFileDialog::getOpenFileName(this, "Open", "../", "Text files (*.txt);;C++ files (*.cpp);;All files (*.*)");
    ReadFromFile(filepath);

    QString filetype = QFileInfo(filename).suffix();  //后缀名
    if(filetype == "cpp")  //添加语法高亮
        highlighter = new CppHighlighter(ui->textEdit->document());
    else  //清除语法高亮
    {
        if(highlighter != nullptr)
            highlighter->clearHighlight();
    }
}

void notebook::ReadFromFile(const QString &filepath)
{
    if(filepath.length() != 0)
    {
        QFile file(filepath);
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            QString str = file.readAll();
            if(Qt::mightBeRichText(str))  //富文本格式
                ui->textEdit->setHtml(str);
            else  //非富文本格式
                ui->textEdit->setText(str);
            file.close();

            filename = filepath;  //设置基本信息
            isTextChanged = false;
            setWindowTitle(QFileInfo(filename).fileName() + " - Notebook");
        }
        else  //打开异常
            throw "could not open file.";
    }
}

void notebook::SaveFile(){
    if(filename == "")  //新文件
        SaveAsFile();
    else  //旧文件，保存到原地址
    {
        QString filepath = filename;
        WriteToFile(filepath);
    }
}

void notebook::SaveAsFile(){
    QString filepath;
    filepath = QFileDialog::getSaveFileName(this, "Save", "../", "Text files (*.txt);;C++ files (*.cpp);;All files (*.*)");

    WriteToFile(filepath);
}

void notebook::WriteToFile(const QString &filepath)
{
    QString output;

    QString filetype = QFileInfo(filepath).suffix();  //后缀名
    if(filetype == "cpp")  //纯文本格式保存
        output = ui->textEdit->toPlainText();
    else  //富文本格式保存
        output = ui->textEdit->toHtml();

    if(filepath.length() != 0)
    {
        QFile file(filepath);
        if(file.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);
            out << output;
            file.close();

            filename = filepath;  //设置基本信息
            isTextChanged = false;
            setWindowTitle(QFileInfo(filename).fileName() + " - Notebook");
        }
        else  //保存异常
            throw "could not save file.";
    }
}

void notebook::closeEvent(QCloseEvent *event)
{
    CloseModified();

    event->accept();
}

void notebook::UnDo(){
    ui->textEdit->undo();
}

void notebook::ReDo(){
    ui->textEdit->redo();
}

void notebook::Cut(){
    ui->textEdit->cut();
}

void notebook::Copy(){
    ui->textEdit->copy();
}

void notebook::Paste(){
    ui->textEdit->paste();
}

void notebook::SelectAll(){
    ui->textEdit->selectAll();
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
                if(fd_str=="")
                    QMessageBox::warning(NULL,"WARNING","Content can not be empty",QMessageBox::Ok);
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
                if(fd_str=="")
                    QMessageBox::warning(NULL,"WARNING","Content can not be empty",QMessageBox::Ok);
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
                if(doc.indexOf(fd_str)==-1)
                    QMessageBox::warning(NULL,"WARNING","Content \""+ fd_str + "\" not found",QMessageBox::Ok);
                else
                    {
                        doc = doc.replace(fd_str,rp_str);
                        ui->textEdit->setPlainText(doc);
                    }
                }
            );
}

void notebook::highLight(){
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
    ui->textEdit->setPalette(palette);
}

void notebook::Font(){
    bool flag;
    QTextCharFormat fmt;
    QFont font = QFontDialog::getFont(&flag, this);

    if(flag){
        fmt.setFont(font);
        ui->textEdit->mergeCurrentCharFormat(fmt);  //修改选中字体，修改日后输入字体
    }
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

void notebook::Color(){
    QTextCharFormat fmt;
    QColor clr = QColorDialog::getColor();
    ui->textEdit->setTextColor(clr);
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

void notebook::ClearFormat(){
    ui->textEdit->setFontFamily("Anonymous Pro");  //恢复原本格式
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->setTextColor(Qt::black);

    ui->textEdit->setFontWeight(50);
    flagB=false;
    ui->textEdit->setFontItalic(false);
    flagI=false;
    ui->textEdit->setFontUnderline(false);
    flagU=false;
}

void notebook::AlignLeft(){
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void notebook::AlignCenter(){
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void notebook::AlignRight(){
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void notebook::About(){
    QMessageBox::about(this, tr("About Application"), tr("The <b>Notebook</b> is created by <br>"
                                                         "<br>EleanoreEos"
                                                         "<br>Kevin-Zh-CS"
                                                         "<br>SJoJoK"
                                                         "<br>tjc1411"));
}

void notebook::ZoomIn(){
    ui->textEdit->zoomIn();
}

void notebook::ZoomOut(){
    ui->textEdit->zoomOut();
}

void notebook::Fullscreen(){
    if(ui->actionFullscreen->isChecked())
        showFullScreen();
    else
        showNormal();
}

void notebook::ReadOnly(){
    if(ui->actionReadOnly->isChecked())
        ui->textEdit->setReadOnly(true);
    else
        ui->textEdit->setReadOnly(false);
}

void notebook::ShowTools(){
    if(ui->actionShowTools->isChecked())
        toolBar->setHidden(false);
    else
        toolBar->setHidden(true);
}

/******************************************
                状态栏
******************************************/

//行数统计（右下角）
void notebook::LineNumUpdate(){
    int blocknumbers = ui->textEdit->document()->blockCount();
    QString Linenum = QString::number(blocknumbers, 10);
    Linenum = "Line " + Linenum + " ";

    LineLabel->setText(Linenum);
    ui->statusbar->addPermanentWidget(LineLabel);
}

//更新时间（左下角）
void notebook::TimeUpdate(){
    QDateTime CurrentTime=QDateTime::currentDateTime();
    QString Timestr=CurrentTime.toString(" yyyy-MM-dd hh:mm:ss ");  //设置时间显示的格式

    TimeLabel->setText(Timestr);
    ui->statusbar->addWidget(TimeLabel);
}
