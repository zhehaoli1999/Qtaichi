#include "minidraw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

    QApplication a(argc, argv);
    Minidraw w;
    w.show();

    return a.exec();
}
