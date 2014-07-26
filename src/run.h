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
};

int run(struct opt opt, struct result *result);


#endif //  __RUN_H__

