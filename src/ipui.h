#ifndef IPUI_H
#define IPUI_H

#include "info.h"
#include "dataformatter.h"

#include <QWidget>
#include <QFile>
#include <QLineEdit>
#include <QLabel>
#include <qtimer.h>
#include <QPushButton>
#include <QSettings>

namespace Ui {
class IpUi;
}

class IpUi : public QWidget
{
    Q_OBJECT

public:
    explicit IpUi(QWidget *parent = 0);
    ~IpUi();
    void showIp(Info);

private:
    Ui::IpUi *ui;
    QPushButton *logout[3];
    QLineEdit *name[3];
    QLabel *time[3], *traffic[3];
    int count;
    QString address[3];
    QString device[3];
    QSettings settings;
    void loadName();

signals:
    void logoutRequest(int);

private slots:
    void logout0Clicked();
    void logout1Clicked();
    void logout2Clicked();
    void saveName();
};

#endif // IPUI_H
