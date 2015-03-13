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
    QPushButton *logout[3];
    QLineEdit *name[3];
    QLabel *time[3], *traffic[3];
    Ui::IpUi *ui;

signals:
    void logoutRequest(int);

private slots:
    void logout0Clicked();
    void logout1Clicked();
    void logout2Clicked();
};

#endif // IPUI_H
