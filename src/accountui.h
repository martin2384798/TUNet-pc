#ifndef ACCOUNTUI_H
#define ACCOUNTUI_H

#include "aboutui.h"
#include "ipui.h"
#include "info.h"
#include "failui.h"
#include "dataformatter.h"

#include <QWidget>
#include <qtimer.h>
#include <QCloseEvent>
#include <QPropertyAnimation>

namespace Ui {
class AccountUi;
}

class AccountUi : public QWidget
{
    Q_OBJECT
public:
    explicit AccountUi(IpUi *ip, QWidget *parent = 0);
    ~AccountUi();

public:
    int onlineTime = -1;

private:
    Ui::AccountUi *ui;
    AboutUi *aboutUi;
    FailUi *logoutFail;
    QTimer *timer;
    IpUi *ip;
    QPropertyAnimation animation;
    double roughTraffic = 0, thisSessionTraffic = 0;
    bool hasAccurateTraffic = false;
    void updateTraffic();

signals:
    void logoutSignal();

private slots:
    void logoutClicked();
    void timeIncrement();
    void adjustWindow(bool state);

public slots:
    void infoSlot(Info);
    void checkResultSlot(Info);
    void logoutFailSlot(Info);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // ACCOUNTUI_H
