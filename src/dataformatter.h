#ifndef DATAFORMATTER_H
#define DATAFORMATTER_H

#include <QString>

class DataFormatter
{
public:
    DataFormatter();
    ~DataFormatter();
    static QString trafficForm(double);
    static QString timeForm(int);
};

#endif // DATAFORMATTER_H
