#include "tools.h"

time_t mktime_tz(struct tm *tm)
{
    assert(tm);

    // save current TZ
    char *tz = getenv("TZ");
    if (tz)
        tz = strdup(tz);

    // clear TZ
    setenv("TZ", "", 1);
    tzset();

    // get unix time from structure
    time_t ret = mktime(tm);

    // revert TZ
    if (tz)
    {
        setenv("TZ", tz, 1);
        free(tz);
    }
    else
        unsetenv("TZ");
    tzset();

    return ret;
}

// parse dd/mm/yyyy date
time_t str2date(const char *str)
{
    assert(str);

    if (strlen(str) != strlen("dd/mm/yyyy"))
        return false;

    struct tm ttm = { 0 };
    ttm.tm_year = atoi(str + 6) - 1900;
    ttm.tm_mon = atoi(str + 3) - 1;
    ttm.tm_mday = atoi(str);
    //ttm.tm_isdst = -1;

    return mktime_tz(&ttm);
}

// convert date from unix time to string
char *date2str(const time_t date, char *str)
{
    assert(str);

    // get time in structure
    struct tm *ttm = gmtime(&date);
    assert(ttm);

    sprintf(str, "%02d/%02d/%d", ttm->tm_mday, ttm->tm_mon + 1, ttm->tm_year + 1900);

    return (str);
}

