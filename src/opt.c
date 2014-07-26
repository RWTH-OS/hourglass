/*
 * =====================================================================================
 *
 *       Filename:  opt.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  25.07.2014 15:01:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Georg Wassen (gw) (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include "opt.h"

int opt(int argc, char *argv[], struct opt *opt)
{
    opt->secs = 4;
    opt->mode = stat;
    opt->threshold = 0;

    opt->mode = hist;
    opt->hist_cnt = 100;
    opt->hist_width = 50;

    opt->mode = list;
    opt->threshold = 100;
    opt->list_cnt = 1000;

    /*
     * read command line arguments and store them in opt
     */

    return 0;
}

