#ifndef WTMPLIB_H
#define WTMPLIB_H
/* wtmplib.h  - header file with decls of functions in wtmplib.c */

#include <utmp.h>

#define NRECS 10000
#define UTSIZE (sizeof(struct utmp))

struct utmp utmpbuf[NRECS];

int utmp_open(char *);
struct utmp *utmp_bsearch(int, int, time_t);
struct utmp *utmp_next();
int utmp_close();

#endif
