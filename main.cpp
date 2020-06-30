#include "notebook.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pix(":imgs/Image/cover.png");  //开屏动画
    QSplashScreen splash(pix);
    splash.show();

    notebook w;
    w.setWindowTitle("Untitled - Notebook");  //初始标题
    w.setWindowIcon(QIcon(":imgs/Image/cover.png"));  //顶部图标
    w.show();
    splash.finish(&w);

    return a.exec();
}
