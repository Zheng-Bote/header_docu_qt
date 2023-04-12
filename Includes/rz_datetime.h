#pragma once
#include <QString>

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
