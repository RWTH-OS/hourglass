/*
 * =====================================================================================
 *
 *       Filename:  run.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.07.2014 15:08:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Georg Wassen (gw) (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef __RUN_H__
#define __RUN_H__

#include "opt.h"

#include <stdint.h>

struct result {
    uint64_t dummy;

    uint64_t min;
    uint64_t max;
    uint64_t sum;
    uint64_t cnt;
    uint64_t t_min;
    uint64_t t_max;

};

int run(struct opt *opt, struct result *result);
int run_free(struct opt *opt, struct result *result);


#endif //  __RUN_H__

