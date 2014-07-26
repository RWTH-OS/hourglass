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

int report(struct opt opt, struct result result)
{
    /*
     * write results to stdout (or file)
     * depending on opt
     */

    printf("Dummy result: %llu \n", (unsigned long long)result.dummy);

    return 0;
}
