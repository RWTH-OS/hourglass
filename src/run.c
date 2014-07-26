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

static struct result *results;


static void store_results_hist(uint64_t t)
{
    /*
     * create histogram 
     */
    results->dummy = t;
}

static void store_results_list(uint64_t t)
{
    /*
     * store all timestamps
     */
    results->dummy = t;
}

static void (*store_results)(uint64_t t);

int run(struct opt opt, struct result *result)
{
    uint64_t t;

    results = result;
    store_results = store_results_hist;

    /*
     * execute hourglass routine
     */

    rdtsc(&t);

    store_results(t);

    return 0;
}

