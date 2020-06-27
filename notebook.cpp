#include "notebook.h"
#include "ui_notebook.h"

static bool flagI = false;
static bool flagB = false;
static bool flagU = false;

notebook::notebook(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::notebook)
{
    createUI();//创建初始化界面
}

notebook::~notebook()
{
    delete ui;
}

void notebook::createUI(){
    ui->setupUi(this);

    QFont defaultFont("Anonymous Pro",12);
    ui->textEdit->setFont(defaultFont);
    connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(isChanged()));
    setCentralWidget(ui->textEdit);

    ui->textEdit->setStyleSheet("QTextEdit{border:1px groove gray;border-radius:10px;padding:2px 4px}");

    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionNew->setIcon(QIcon(":imgs/Image/new.png"));
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(NewFile()));//创建连接，点击触发事件，调用对应函数

    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionOpen->setIcon(QIcon(":imgs/Image/open.png"));
    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(OpenFile()));

    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSave->setIcon(QIcon(":imgs/Image/save.png"));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(SaveFile()));

    ui->actionSaveAs->setIcon(QIcon(":imgs/Image/save-as.png"));
    connect(ui->actionSaveAs, SIGNAL(triggered(bool)), this, SLOT(SaveAsFile()));

    ui->actionExit->setShortcut(Qt::Key_Escape);
    ui->actionExit->setIcon(QIcon(":imgs/Image/exit.png"));
    connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(Exit()));

    ui->actionUndo->setShortcut(QKeySequence::Undo);
    ui->actionUndo->setIcon(QIcon(":imgs/Image/undo.png"));
    connect(ui->actionUndo, SIGNAL(triggered(bool)), this, SLOT(UnDo()));

    ui->actionRedo->setShortcut(QKeySequence::Redo);
    ui->actionRedo->setIcon(QIcon(":imgs/Image/redo.png"));
    connect(ui->actionRedo, SIGNAL(triggered(bool)), this, SLOT(ReDo()));

    ui->actionCut->setShortcut(QKeySequence::Cut);
    ui->actionCut->setIcon(QIcon(":imgs/Image/cut.png"));
    connect(ui->actionCut, SIGNAL(triggered(bool)), this, SLOT(Cut()));

    ui->actionCopy->setShortcut(QKeySequence::Copy);
    ui->actionCopy->setIcon(QIcon(":imgs/Image/copy.png"));
    connect(ui->actionCopy, SIGNAL(triggered(bool)), this, SLOT(Copy()));

    ui->actionPaste->setShortcut(QKeySequence::Paste);
    ui->actionPaste->setIcon(QIcon(":imgs/Image/paste.png"));
    connect(ui->actionPaste, SIGNAL(triggered(bool)), this, SLOT(Paste()));

    ui->actionSelectAll->setShortcut(QKeySequence::SelectAll);
    ui->actionSelectAll->setIcon(QIcon(":imgs/Image/select-all.png"));
    connect(ui->actionSelectAll, SIGNAL(triggered(bool)), this, SLOT(SelectAll()));

    ui->actionFind->setShortcut(QKeySequence::Find);
    ui->actionFind->setIcon(QIcon(":imgs/Image/find.png"));
    connect(ui->actionFind, SIGNAL(triggered(bool)), this, SLOT(Find()));

    ui->actionReplace->setShortcut(QKeySequence::Replace);
    ui->actionReplace->setIcon(QIcon(":imgs/Image/replace.png"));
    connect(ui->actionReplace, SIGNAL(triggered(bool)), this, SLOT(Replace()));


    ui->actionFont->setIcon(QIcon(":imgs/Image/font.png"));
    connect(ui->actionFont, SIGNAL(triggered(bool)), this, SLOT(Font()));

    ui->actionSize->setIcon(QIcon(":imgs/Image/size.png"));
    connect(ui->actionSize, SIGNAL(triggered(bool)), this, SLOT(Size()));

    ui->actionColor->setIcon(QIcon(":imgs/Image/color.png"));
    connect(ui->actionColor, SIGNAL(triggered(bool)), this, SLOT(Color()));

    ui->actionBold->setShortcut(QKeySequence::Bold);
    ui->actionBold->setIcon(QIcon(":imgs/Image/bold.png"));
    connect(ui->actionBold, SIGNAL(triggered(bool)), this, SLOT(Bold()));

    ui->actionItalic->setShortcut(QKeySequence::Italic);
    ui->actionItalic->setIcon(QIcon(":imgs/Image/italic.png"));
    connect(ui->actionItalic, SIGNAL(triggered(bool)), this, SLOT(Italic()));

    ui->actionUnderline->setShortcut(QKeySequence::Underline);
    ui->actionUnderline->setIcon(QIcon(":imgs/Image/underline.png"));
    connect(ui->actionUnderline, SIGNAL(triggered(bool)), this, SLOT(Underline()));

    ui->actionClearFormat->setShortcut(Qt::CTRL + Qt::Key_Q);
    ui->actionClearFormat->setIcon(QIcon(":imgs/Image/clear-format.png"));
    connect(ui->actionClearFormat, SIGNAL(triggered(bool)), this, SLOT(ClearFormat()));

    ui->actionAlignLeft->setIcon(QIcon(":imgs/Image/left.png"));
    connect(ui->actionAlignLeft, SIGNAL(triggered(bool)), this, SLOT(AlignLeft()));

    ui->actionAlignCenter->setIcon(QIcon(":imgs/Image/center.png"));
    connect(ui->actionAlignCenter, SIGNAL(triggered(bool)), this, SLOT(AlignCenter()));

    ui->actionAlignRight->setIcon(QIcon(":imgs/Image/right.png"));
    connect(ui->actionAlignRight, SIGNAL(triggered(bool)), this, SLOT(AlignRight()));

    ui->actionAbout->setIcon(QIcon(":imgs/Image/about.png"));
    connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(About()));

    ui->actionZoomIn->setShortcut(QKeySequence::ZoomIn);
    ui->actionZoomIn->setIcon(QIcon(":imgs/Image/zoom-in.png"));
    connect(ui->actionZoomIn, SIGNAL(triggered(bool)), this, SLOT(ZoomIn()));

    ui->actionZoomOut->setShortcut(QKeySequence::ZoomOut);
    ui->actionZoomOut->setIcon(QIcon(":imgs/Image/zoom-out.png"));
    connect(ui->actionZoomOut, SIGNAL(triggered(bool)), this, SLOT(ZoomOut()));

    ui->actionFullscreen->setShortcut(QKeySequence::FullScreen);
    connect(ui->actionFullscreen, SIGNAL(triggered(bool)), this, SLOT(Fullscreen()));

    ui->actionShowTools->setShortcut(Qt::CTRL + Qt::Key_T);
    connect(ui->actionShowTools, SIGNAL(triggered(bool)), this, SLOT(ShowTools()));


    toolBar->setStyleSheet("QToolBar{background-color:white}");
    toolBar->addAction(ui->actionNew);
    toolBar->addAction(ui->actionOpen);
    toolBar->addAction(ui->actionSave);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionUndo);
    toolBar->addAction(ui->actionRedo);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionFind);
    toolBar->addAction(ui->actionReplace);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionBold);
    toolBar->addAction(ui->actionItalic);
    toolBar->addAction(ui->actionUnderline);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionFont);
    toolBar->addAction(ui->actionSize);
    toolBar->addAction(ui->actionColor);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionClearFormat);
    toolBar->addSeparator();
    toolBar->addAction(ui->actionAlignLeft);
    toolBar->addAction(ui->actionAlignCenter);
    toolBar->addAction(ui->actionAlignRight);
    statusBar();


    QTimer *timer = new QTimer(this);
    timer->start(100); // 每次发射timeout信号时间间隔为1秒
    connect(timer,SIGNAL(timeout()),this,SLOT(TimeUpdate()));

    QTimer *LineTimer=new QTimer(this);
    LineTimer->start(100); // 每次发射timeout信号时间间隔为100毫秒
    connect(LineTimer,SIGNAL(timeout()),this,SLOT(LineNum()));
}

void notebook::highLight(){//查找高亮
    QPalette palette = ui->textEdit->palette();
    palette.setColor(QPalette::Highlight,palette.color(QPalette::Active,QPalette::Highlight));
    ui->textEdit->setPalette(palette);
}

void notebook::isChanged()
{
    if(!isTextChanged)
    {
        setWindowTitle("*" + windowTitle());
    }

    isTextChanged = true;
}

void notebook::NewFile(){
    if(isTextChanged)
    {
        int result = QMessageBox::question(this,tr("tips"),tr("Save or not?"),QMessageBox::Yes|QMessageBox::Default,QMessageBox::No|QMessageBox::Escape);
        if (result == QMessageBox::Yes)
            SaveFile();
    }

    ui->textEdit->clear();
    filename = "";
    isTextChanged = false;
    setWindowTitle("Untitled - Notebook");
}

void notebook::OpenFile(){
    if(isTextChanged)
    {
        int result = QMessageBox::question(this,tr("tips"),tr("Save or not?"),QMessageBox::Yes|QMessageBox::Default,QMessageBox::No|QMessageBox::Escape);
        if (result == QMessageBox::Yes)
            SaveFile();
    }

    QString filepath = QFileDialog::getOpenFileName(this,"Open","../","text(*.*)");
    if(filepath.length() != 0)
    {
        QFile file(filepath);
        if(file.open(QFile::ReadOnly | QFile::Text))
        {
            ui->textEdit->setText(QString(file.readAll()));
            file.close();
            filename = filepath;
            isTextChanged = false;
            setWindowTitle(filename + " - Notebook");
        }
        else
            throw "could not open file.";
    }
}

void notebook::SaveFile(){
    QString output = ui->textEdit->toPlainText();
    QString filepath;

    if(filename == "")
        filepath = QFileDialog::getSaveFileName(this,"Save","../","text(*.txt)");
    else
        filepath = filename;

    if (filepath.length() != 0){
        QFile file(filepath);
        if(file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            out << output;
            file.close();
            filename = filepath;
            isTextChanged = false;
            setWindowTitle(filepath + " - Notebook");
        }
        else
            throw "could not write file.";
    }
}

void notebook::SaveAsFile(){
    QString output = ui->textEdit->toPlainText();
    QString filepath = QFileDialog::getSaveFileName(this,"Save","../","text(*.txt)");
    if (filepath.length() != 0){
        QFile file(filepath);
        if(file.open(QFile::WriteOnly | QFile::Text)) {
            QTextStream out(&file);
            out << output;
            file.close();
            filename = filepath;
            isTextChanged = false;
            setWindowTitle(filepath + " - Notebook");
        }
        else
            throw "could not write file.";
    }
}

void notebook::Exit(){
    close();
}

void notebook::closeEvent(QCloseEvent *event)
{
    if(isTextChanged)
    {
        int result = QMessageBox::question(this,tr("tips"),tr("Save or not?"),QMessageBox::Yes|QMessageBox::Default,QMessageBox::No|QMessageBox::Escape);
        if (result == QMessageBox::Yes)
            SaveFile();
    }

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

void notebook::Font(){
    bool flag;
    QTextCharFormat fmt;
    QFont font = QFontDialog::getFont(&flag, this);
    if(flag){
        fmt.setFont(font);
        ui->textEdit->mergeCurrentCharFormat(fmt);//修改选中字体修改日后输入字体
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
    ui->textEdit->setFontFamily("Anonymous Pro");
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
    if(ui->actionFullscreen->isChecked()==true)
        showFullScreen();
    else
        showNormal();
}

void notebook::ShowTools(){
    if(ui->actionShowTools->isChecked()==true)
        toolBar->setHidden(false);
    else
        toolBar->setHidden(true);
}

void notebook::LineNum(){
    int blocknumbers = ui->textEdit->document()->blockCount();
    QString Linenum = QString::number(blocknumbers, 10);

    Linenum="Line " + Linenum + " ";
    LineLabel->setText(Linenum);
    ui->statusbar->addPermanentWidget(LineLabel);
}

void notebook::TimeUpdate(){
    QDateTime CurrentTime=QDateTime::currentDateTime();
    QString Timestr=CurrentTime.toString(" yyyy-MM-dd hh:mm:ss "); //设置显示的格式

    TimeLabel->setText(Timestr);
    ui->statusbar->addWidget(TimeLabel);
}
