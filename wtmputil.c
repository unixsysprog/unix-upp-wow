#define     _XOPEN_SOURCE
#include    <stdio.h>
#include    <fcntl.h>
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <utmp.h>
#include    <unistd.h>
#include    <time.h>
#include    "wtmputil.h"

/*
 * utmp_fize - Returns the size of the file.
 *  args: filename
 *  rets: size of file, represented by type off_t
 */
off_t utmp_fsize(const char* filename)
{
    struct stat st = {0};
    if (stat(filename, &st) != 0)
        return -1;

    return st.st_size;
}

/*
 * show_info - outputs log informatoin 
 *  args: utbufp
 * 
 * A specified subset of log information found in the utmp struct in human
 * readable form.
 */
void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;

    printf("%-8s\t", utbufp->ut_name);        /* the logname  */
    printf("%-12.12s\t", utbufp->ut_line);    /* the tty  */
    show_time(utbufp->ut_time, DATE_FMT);     /* display time */
    if (utbufp->ut_host[0] != '\0')
        printf(" (%s)", utbufp->ut_host);     /* the host */

    printf("\n");                             /* newline  */
}

#define MAXDATELEN  100
/* 
 * show_time - displays time in a format fit for human consumption.
 *  args: timeval, *fmt
 *  
 * Uses localtime to convert the timeval into a struct of elements
 * (see localtime(3)) and uses strftime to format the data
 */
void show_time( time_t timeval , char *fmt )
{
    char    result[MAXDATELEN];

    struct tm *tp = localtime(&timeval);        /* convert time */
    strftime(result, MAXDATELEN, fmt, tp);      /* format it    */
    fputs(result, stdout);
}

/*
 * convert_time - converts from string to type time_t
 *  args: *date
 *  rets: time in unix time of type time_t
 */
time_t convert_time(char* date)
{
    struct tm tp = {0};
    tp.tm_isdst = -1;

    strptime(date, "%Y %m %d", &tp);
    return mktime(&tp);
} 

