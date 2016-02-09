#ifndef TOOLS_H_
#define TOOLS_H_

#include "common.h"

// parse dd/mm/yyyy date
time_t str2date(const char *str);

// convert date from unix time to string
char *date2str(const time_t date, char *str);

#endif /* TOOLS_H_ */
