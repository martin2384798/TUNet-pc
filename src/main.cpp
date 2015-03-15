#include "aboutui.h"
#include "loginui.h"
#include "loadingui.h"
#include "accountui.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Lab mU");
    QCoreApplication::setOrganizationDomain("lab.mu");
    QCoreApplication::setApplicationName("tunet");
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    try {
        Controller controller;
        return a.exec();
    }
    catch(std::exception e){
        QMessageBox *msg = new QMessageBox(QMessageBox::Critical, "Boom!",
            QString("TUNet exploded because ") + QString(e.what()), QMessageBox::Ok);
        msg->exec();
    }
}
