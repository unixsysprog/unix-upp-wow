#include    <stdio.h>
#include    <unistd.h>
#include    <sys/types.h>
#include    <utmp.h>
#include    <fcntl.h>
#include    <stdlib.h>
#include    <assert.h>
#include    <errno.h>

#include    "wtmplib.h" 
#include    "wtmpsearch.h"

/*
 *  wow version 1.0      - lists logins for specified date
 *                       - user can specify sequential or binary search 
 */
#define USAGE "usage: [-f] input_file year month day [-s|-b]\n"


long int get_arg(char **argv) 
{
    char *endptr = NULL;
    char *str = NULL;
    long int ret = 0;
    
    errno = 0;    
    str = argv[optind++];
    ret = strtol(str, &endptr, 10);

    if (endptr == str) {
        fprintf(stderr, "No digits were found.\n");
        exit(1);
    }
    return ret;
}

int main(int argc, char **argv)
{
    char* f_name = WTMP_FILE;
    int opt = 0; 
    int year = 0;
    int month = 0;
    int day = 0;
    int seq_bin = 1;

    while ((opt = getopt(argc, argv, "f:sb")) != -1) {
        switch (opt) {
            case 'f':
                f_name = optarg;
                break;
            case 's':
                seq_bin = 1;
                break;
            case 'b':
                seq_bin = 0;                
                break;
            case '?':
                fprintf(stderr, USAGE);
                exit(1);
                break;
            default:    
                break;
        }
    } 
        
    if (optind == argc) {optind = 1;} 

    assert(argc > 3 && "usage: [-f] input_file year month day [-s|-b]\n");
    
    year = get_arg(argv) - 1900;
    month = get_arg(argv) - 1;
    day = get_arg(argv);

    if (utmp_open(f_name) == -1 ) {
        fprintf(stderr,"%s: cannot open %s\n", *argv, f_name);
        exit(1);
    }

    if (!seq_bin) {
        int fsize = utmp_fsize(f_name);
        fetch_bsearch(year, month, day, fsize);
    } else {
        fetch_sequential(year, month, day);
    }
    utmp_close();
    return 0;
}
