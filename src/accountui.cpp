#include <QFile>
#include <QDebug>
#include "accountui.h"
#include "ui_accountui.h"

AccountUi::AccountUi(IpUi *ipUi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountUi)
{
    ip = ipUi;
    ui->setupUi(this);
    aboutUi = new AboutUi;
    timer = new QTimer;
    QFile *file = new QFile(":qss/qss/accountui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();
    connect(ui->aboutButton, SIGNAL(clicked()),
            aboutUi, SLOT(exec()));
    connect(ui->logoutButton, SIGNAL(clicked()),
            this, SLOT(logoutClicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeIncrement()));

    ui->verticalLayout_2->addWidget(ip);

    this->setFixedSize(320, 340);
    ui->extendWidget->setVisible(false);
    ui->extendButton->setCheckable(true);

    connect(ui->extendButton, SIGNAL(toggled(bool)),
            this, SLOT(adjustWindow(bool)));
}

AccountUi::~AccountUi()
{
    delete ui;
}

void AccountUi::logoutClicked()
{
    emit logoutSignal();
}

void AccountUi::infoSlot(Info info)
{
    QString flowText, moneyText;
    if (info.infoType == Info::LoginInfo) {
        flowText = ">=" + DataFormatter::trafficForm(info.accountInfo.roughTraffic);
        moneyText = "Loading...";
    }
    else {
        flowText = DataFormatter::trafficForm(info.accountInfo.totalAccurateTraffic);
        moneyText = QString::number(info.accountInfo.balance, 'f', 2) + "RMB";
    }
    ui->username->setText(info.accountInfo.userName);
    ui->flowNumber->setText(flowText);
    ui->moneyNumber->setText(moneyText);
    if (info.infoType == Info::QueryInfo)
        ip->showIp(info);
}

void AccountUi::checkResultSlot(Info info)
{
    int timeReceived = info.accountInfo.loginTime;
    if (onlineTime != timeReceived) {
        onlineTime = timeReceived;
        timer->start(1000); 
    }
}

void AccountUi::timeIncrement()
{
    if (onlineTime >= 0) {
        onlineTime++;
        QString timeText = DataFormatter::timeForm(onlineTime / 60 / 60) + ":" +
                           DataFormatter::timeForm(onlineTime / 60 % 60) + ":" +
                           DataFormatter::timeForm(onlineTime % 60);
        ui->timeNumber->setText(timeText);
    }
    else {
        ui->timeNumber->setText("Loading...");
    }
}

void AccountUi::logoutFailSlot(Info info)
{
    logoutFail = new FailUi(info.accountInfo.error);
    logoutFail->exec();
    logoutFail->deleteLater();
}

void AccountUi::adjustWindow(bool state)
{
    ui->extendWidget->setVisible(state);
    if (state)
        this->setFixedSize(320, 425);
    else
        this->setFixedSize(320, 340);
}

void AccountUi::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
