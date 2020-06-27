#include "notebook.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pix(":imgs/Image/cover.png");
    QSplashScreen splash(pix);
    splash.show();

    notebook w;
    w.setWindowTitle("Untitled - Notebook");
    w.setWindowIcon(QIcon(":imgs/Image/cover.png"));
    w.show();
    splash.finish(&w);

    return a.exec();
}
