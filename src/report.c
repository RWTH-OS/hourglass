/*
 * =====================================================================================
 *
 *       Filename:  report.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.07.2014 15:11:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Georg Wassen (gw) (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "report.h"

#include <stdio.h>


static int report_stat(struct result *result)
{
    printf("   # loops  : %15llu\n",
            (unsigned long long)result->cnt);
    printf("   Min.     : %15llu     (@loop #%llu)\n",
            (unsigned long long)result->min,
            (unsigned long long)result->t_min);
    printf("   Avg.     : %18.2lf\n",
            (double)result->sum/(double)result->cnt);
    printf("   Max.     : %15llu     (@loop #%llu)\n",
            (unsigned long long)result->max,
            (unsigned long long)result->t_max);
    return 0;
}

int report(struct opt *opt, struct result *result)
{
    /*
     * write results to stdout (or file)
     * depending on opt
     */

    printf("Dummy result: %llu \n", (unsigned long long)result->dummy);

    report_stat(result);

    return 0;
}
