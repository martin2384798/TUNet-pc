﻿#include "controller.h"

Controller::Controller()
{
    network = new Network;
    loginUi = new LoginUi;
    loadingUi = new LoadingUi;
    ipUi = new IpUi;
    accountUi = new AccountUi(ipUi);

    loginUi->setWindowFlags(Qt::Tool);
    loadingUi->setWindowFlags(Qt::Tool);
    accountUi->setWindowFlags(Qt::Tool);

    timer = new QTimer;
    timer->stop();
    showUi(login);

    creatTrayMenu();
    trayIcon = new QSystemTrayIcon;
    trayIcon->setContextMenu(trayMenu);
    trayIcon->setIcon(QIcon(":/imgs/images/logo.png"));
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));


    //登陆
    connect(loginUi, SIGNAL(loginSignal(QString, QString)),
            network, SLOT(loginSlot(QString, QString)));
    connect(loginUi, SIGNAL(loginSignal(QString, QString)),
            this, SLOT(onLoginStart(QString)));

    //登陆成功
    connect(network, SIGNAL(loginSucceed(Info)),
            accountUi, SLOT(infoSlot(Info)));
    connect(network, SIGNAL(loginSucceed(Info)),
            this, SLOT(onLoginSucceed()));
    connect(network, SIGNAL(loginSucceed(Info)),
            this, SLOT(setTimer()));
    
    //登录失败
    connect(network, SIGNAL(loginFail(Info)),
            loginUi, SLOT(loginFailDialog(Info)));
    connect(network, SIGNAL(loginFail(Info)),
            this, SLOT(onLoginFail()));

    //Abort login
    connect(loadingUi, SIGNAL(loginAbort()),
            network, SLOT(loginAbortSlot()));

    //定时查询
    connect(timer, SIGNAL(timeout()),
            this, SLOT(onTimeOut()));
    connect(this, SIGNAL(checkSignal()),
            network, SLOT(checkSlot()));
    connect(network, SIGNAL(checkResult(Info)),
            accountUi, SLOT(checkResultSlot(Info)));
    connect(this, SIGNAL(querySignal(QString, QString)),
            network, SLOT(querySlot(QString, QString)));
    connect(network, SIGNAL(infoSignal(Info)),
            accountUi, SLOT(infoSlot(Info)));

    //下线IP
    connect(ipUi, SIGNAL(logoutRequest(int)),
            network, SLOT(dropIpSlot(int)));
    connect(network, SIGNAL(dropIpSucceed()),
            this, SLOT(onTimeOut()));

    //断开
    connect(accountUi, SIGNAL(logoutSignal()),
            network, SLOT(logoutSlot()));

    //断开成功
    connect(network, SIGNAL(logoutSucceed()),
            this, SLOT(onLogoutSucceed()));
    connect(network, SIGNAL(logoutSucceed()),
            timer, SLOT(stop()));

    //断开失败
    connect(network, SIGNAL(logoutFail(Info)),
            accountUi, SLOT(logoutFailSlot(Info)));

    if (loginUi->autoLogin)
        emit loginUi->loginSignal(loginUi->username, loginUi->password);
}

void Controller::showUi(kind which)
{
    if (which != change)
    {
        if (loginUi->isVisible()) loginUi->hide();
        if (loadingUi->isVisible()) loadingUi->hide();
        if (accountUi->isVisible()) accountUi->hide();
    }
    QWidget* window;
    switch (which)
    {
        case change:
            if (last == login) window = loginUi;
            if (last == loading) window = loadingUi;
            if (last == account) window = accountUi;
            break;
        case login:
            window = loginUi;
            last = login;
            break;
        case loading:
            window = loadingUi;
            last = loading;
            break;
        case account:
            window = accountUi;
            last = account;
            break;
    }
    if (which != change || !window->isVisible()) {
        window->show();
        window->activateWindow();
    }
    else window->hide();
}

void Controller::setTimer()
{
    timer->start(30000);
}

void Controller::onTimeOut()
{
    emit checkSignal();
    emit querySignal(loginUi->username, loginUi->password);
}

void Controller::onLoginStart(QString username)
{
    loginUi->setEnabled(false);
    loadingUi->setUsername(username);
    showUi(loading);
}

void Controller::onLoginSucceed()
{
    loginUi->setEnabled(true);
    showUi(account);
    emit checkSignal();
    emit querySignal(loginUi->username, loginUi->password);
}

void Controller::onLoginFail()
{
    loginUi->setEnabled(true);
    showUi(login);
}

void Controller::onLogoutSucceed()
{
    loginUi->setEnabled(true);
    showUi(login);
}

void Controller::creatTrayMenu()
{
    trayMenu = new QMenu((QWidget*)QApplication::desktop());

    QAction *showHideAction = new QAction("Show/Hide", this);
    QAction *quitAction = new QAction(tr("Exit"), this);
    trayMenu->addAction(showHideAction);
    trayMenu->addAction(quitAction);
    connect(quitAction, SIGNAL(triggered()),
            this, SLOT(quit()));
    connect(showHideAction, SIGNAL(triggered()),
            this, SLOT(showHide()));
}

void Controller::quit()
{
    qApp->quit();
}

void Controller::showHide()
{
    showUi(change);
}

void Controller::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger)
    {
        emit showHide();
    }
}

Controller::~Controller()
{
}
