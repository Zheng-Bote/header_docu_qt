#include "rz_datetime.h"

DateTime::DateTime() {}

DateTime::~DateTime() {}

void DateTime::setDateTime()
{
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());

    dt.UTCcurrent = UTC.toString("yyyy-MM-dd HH:mm:ss");
    dt.localTime = local.toString("yyyy-MM-dd HH:mm:ss");

    QTimeZone tz = UTC.timeZone();
    dt.humanUTC = UTC.toString("yyyy-MM-dd HH:mm:ss");
    dt.stringUTC = UTC.toString("yyyy-MM-dd_HH-mm-ss");
    dt.timeUTC = UTC.toString("yyyy-MM-ddTHH:mm:ssZ");
    dt.timeUtcOffset = tz.displayName(local, QTimeZone::OffsetName); // "UTC+02:00"
    dt.timeZAbbreviation = local.timeZoneAbbreviation();             // "CEST"
}

QString DateTime::getHumanUTC()
{
    return dt.humanUTC;
}

QString DateTime::getUTC()
{
    return dt.timeUTC;
}
