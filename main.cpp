#include "notebook.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    notebook w;
    w.setWindowTitle("Notebook");
    w.setWindowIcon(QIcon(":imgs/Image/cover.jpg"));
    w.show();
    return a.exec();
}
