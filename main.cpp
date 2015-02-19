#include "aboutui.h"
#include "loginui.h"
#include "accountui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Lab µ");
    QCoreApplication::setOrganizationDomain("lab.mu");
    QCoreApplication::setApplicationName("tunet");
    QApplication::setStyle("windowxp");
    QApplication a(argc, argv);
    AboutUi w;

    w.show();

    return a.exec();
}
