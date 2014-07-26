/*
 * =====================================================================================
 *
 *       Filename:  run.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.07.2014 15:10:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Georg Wassen (gw) (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "run.h"
#include "rdtsc.h"

#include <limits.h>
#include <stdio.h>

static struct result *results;


static void store_results_stat(uint64_t gap, uint64_t offset)
{

    if (gap < results->min) {
        results->min = gap;
        results->t_min = results->cnt;
    }
    if (gap > results->max) {
        results->max = gap;
        results->t_max = results->cnt;
    }
    results->sum += gap;
    results->cnt++;                                 /* avg = sum/cnt */
}

static void store_results_hist(uint64_t gap, uint64_t offset)
{
    /*
     * create histogram 
     */
    store_results_stat(gap, offset);
    results->dummy = gap;
}

static void store_results_list(uint64_t gap, uint64_t offset)
{
    /*
     * store all timestamps
     */
    results->dummy = gap;
}

static void (*store_results)(uint64_t gap, uint64_t offset);


static int hourglass(uint64_t duration, uint64_t threshold)
{
    uint64_t t1, t2, t_end, diff;             /* timestamps */

    rdtsc(&t1);                               /* start-time */
    t_end = t1 + duration;            /* calculate end-time */

    while (t1 < t_end) {             /* loop until end-time */
        t2 = t1;
        rdtsc(&t1);
        diff = t1 - t2;
        if (diff > threshold) {
            store_results(diff, t2);
        }
        /* Note: additional workload may be added here */
    }
    return 0;
}

int run(const struct opt *opt, struct result *result)
{
    results = result;

    results->min=UINT64_MAX;
    results->max=0;
    results->sum=0;
    results->cnt=0;
    results->t_min = 0;
    results->t_max = 0;

    switch (opt->mode) {
        case stat :
            store_results = store_results_stat;
            break;
        case hist :
            store_results = store_results_hist;
            break;
        case list :
            store_results = store_results_list;
            break;
    }

    /*
     * execute hourglass routine
     */

    hourglass(opt->secs * opt->tps, 0);
    return 0;
}

int run_free(const struct opt *opt, struct result *result)
{
    return 0;
}
