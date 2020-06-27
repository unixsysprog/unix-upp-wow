#ifndef WTMPUTIL_H
#define WTMPUTIL_H
/* wtmputil.h  - header file with decls of functions in wtmputil.c */

#include <utmp.h>

#define TEXTDATE
#ifndef DATE_FMT
#ifdef  TEXTDATE
#define DATE_FMT    "%b %e %H:%M"       /* text format  */
#else
#define DATE_FMT    "%Y-%m-%d %H:%M"    /* the default  */
#endif
#endif

off_t utmp_fsize(const char *);
void show_info(struct utmp *);
void show_time(time_t, char *);
time_t convert_time(char*);

#endif
