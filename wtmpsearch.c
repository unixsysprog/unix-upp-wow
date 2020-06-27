#define __USE_XOPEN  
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "utmp.h"
#include "wtmplib.h"

/*
 * fetch_sequential - outputs log data from wtmp file for specified date.
 *  args: year, month, day
 * 
 * Uses sequential search to locate specified record in data read into memory.
 */
void fetch_sequential(int year, int month, int day) 
{
    struct utmp *utbufp = {0};
    struct tm tm_lb = {0};
    struct tm tm_ub = {0};
    tm_lb.tm_isdst = -1; 
    tm_ub.tm_isdst = -1;

    /*populate lower bound*/
    tm_lb.tm_year = year;
    tm_lb.tm_mon = month;
    tm_lb.tm_mday = day;

    /*populate upper bound*/  
    tm_ub.tm_year = year;
    tm_ub.tm_mon = month;
    tm_ub.tm_mday = day + 1;

    time_t tgt_lb = mktime(&tm_lb);
    time_t tgt_ub = mktime(&tm_ub);

    while ((utbufp = utmp_next()) != ((struct utmp *) NULL)) {
        time_t log_time = (time_t)utbufp->ut_time;
        if (log_time >= tgt_ub) break;

        if (log_time >= tgt_lb && log_time < tgt_ub) {
            show_info(utbufp);
        }        
    }
}  


/*
 * fetch_bsearch - outputs log data from wtmp binary file
 *  args: year, month, day, fsize, fp
 *   
 * Uses binary search implementation to locate a record in a wtmp binary file
 * associated with a date specified by the caller.
 */
void fetch_bsearch(int year, int month, int day, int fsize)
{
    struct utmp* temp = {0};
    int l_idx = 0;
    int r_idx = 0;
    int tot_rec = fsize/(sizeof(struct utmp));     

    /*set key as the target date.*/
    struct tm tm_key = {0};
    tm_key.tm_isdst = -1;
    tm_key.tm_year = year;
    tm_key.tm_mon = month;
    tm_key.tm_mday = day;    
    time_t key = mktime(&tm_key);

    l_idx = 0;
    r_idx = tot_rec - 1;

    temp = utmp_bsearch(l_idx, r_idx, key);
    if (temp == NULL) {
        return;
    } else {
        tm_key.tm_mday = day + 1;
        time_t key_stop = mktime(&tm_key);
        while ((temp = utmp_next()) != ((struct utmp *) NULL)) {
            time_t log_time = (time_t)temp->ut_time;

            if (log_time > key_stop) break;
   
            show_info(temp);
        }
    }
}
