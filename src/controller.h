#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"
#include "accountui.h"
#include "info.h"
#include "loadingui.h"
#include "network.h"
#include <QtWidgets>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    ~Controller();

private:
    QTimer *timer;
    Network *network;
    LoginUi *loginUi;
    LoadingUi *loadingUi;
    AccountUi *accountUi;
    IpUi *ipUi;
    QMenu *trayMenu;
    QSystemTrayIcon *trayIcon;
    enum kind{change, login, loading, account} last;

signals:
    void querySignal(QString, QString);
    void checkSignal();

private slots:
    void setTimer();
    void onTimeOut();
    void onLoginStart(QString, QString);
    void onLoginSucceed();
    void onLogoutSucceed();
    void onLoginFail();
    void showUi(kind);
    void createTrayMenu();
    void quit();
    void showHide();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
};

#endif // CONTROLLER_H
