#include "ipui.h"
#include "ui_ipui.h"

IpUi::IpUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IpUi)
{
    ui->setupUi(this);

    QFile *file = new QFile(":qss/qss/ipui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();

    connect(ui->name_1, SIGNAL(textChanged(QString)),
            this, SLOT(saveName()));
    connect(ui->name_2, SIGNAL(textChanged(QString)),
            this, SLOT(saveName()));
    connect(ui->name_3, SIGNAL(textChanged(QString)),
            this, SLOT(saveName()));

    connect(ui->logout_1, SIGNAL(clicked()),
            this, SLOT(logout0Clicked()));
    connect(ui->logout_2, SIGNAL(clicked()),
            this, SLOT(logout1Clicked()));
    connect(ui->logout_3, SIGNAL(clicked()),
            this, SLOT(logout2Clicked()));

    name[0] = ui->name_1; time[0] = ui->time_1; traffic[0] = ui->traffic_1; logout[0] = ui->logout_1;
    name[1] = ui->name_2; time[1] = ui->time_2; traffic[1] = ui->traffic_2; logout[1] = ui->logout_2;
    name[2] = ui->name_3; time[2] = ui->time_3; traffic[2] = ui->traffic_3; logout[2] = ui->logout_3;
}

IpUi::~IpUi()
{
	delete ui;
}

void IpUi::showIp(Info info)
{
    count = info.accountInfo.onlineIpCount;
    for (int i = 0; i < count; ++i)
    {
        address[i] = info.accountInfo.ipInfo[i].macAdress;
        time[i]->setText(DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[0]) + ":" +
                         DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[1]) + ":" +
                         DataFormatter::timeForm(info.accountInfo.ipInfo[i].onlineTime[2]));
        traffic[i]->setText(DataFormatter::trafficForm(info.accountInfo.ipInfo[i].accurateTraffic));
        name[i]->show();
        time[i]->show();
        traffic[i]->show();
        logout[i]->show();
    }
    loadName();
    for (int i = count; i < 3; ++i)
    {
        name[i]->hide();
        time[i]->hide();
        traffic[i]->hide();
        logout[i]->hide();
    }
}

void IpUi::loadName()
{
    for (int i = 0; i < count; ++i)
        device[i] = settings.value(address[i], "Unknown").toString();
    for (int i = 0; i < count; ++i)
        name[i]->setText(device[i]);
}

void IpUi::saveName()
{
    for (int i = 0; i < count; ++i)
        settings.setValue(address[i], name[i]->text());
}


void IpUi::logout0Clicked()
{
    emit logoutRequest(0);
}

void IpUi::logout1Clicked()
{
    emit logoutRequest(1);
}

void IpUi::logout2Clicked()
{
    emit logoutRequest(2);
}
