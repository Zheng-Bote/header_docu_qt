#pragma once

#include <QDateTime>
#include <QString>
#include <QTimeZone>

namespace rz_datetime {

struct date_time {
    QString humanUTC;
    QString stringUTC;
    QString timeUTC;
    QString timeUtcOffset;
    QString timeZAbbreviation;
    QString localTime;
    QString UTCcurrent;
};

// the end
}

class DateTime
{
public:
    DateTime();
    ~DateTime();

    void setDateTime();
    QString getHumanUTC();
    QString getUTC();

private:
    struct date_time
    {
        QString humanUTC;
        QString stringUTC;
        QString timeUTC;
        QString timeUtcOffset;
        QString timeZAbbreviation;
        QString localTime;
        QString UTCcurrent;
    };

    date_time dt;
};
