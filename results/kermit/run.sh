#!/bin/bash
#===============================================================================
#
#          FILE:  run.sh
# 
#         USAGE:  ./run.sh 
# 
#   DESCRIPTION:  
# 
#       OPTIONS:  ---
#  REQUIREMENTS:  ---
#          BUGS:  ---
#         NOTES:  ---
#        AUTHOR:   (), 
#       COMPANY:  
#       VERSION:  1.0
#       CREATED:  28.07.2014 12:10:14 CEST
#      REVISION:  ---
#===============================================================================


../../src/hg -d 15m > data_stat.out
../../src/hg -d 15m -r hist -c 50 -b 100 > data_hist.out
../../src/hg -d 15m -r list -c 1000 -t 1000 > data_thres1000.out
../../src/hg -d 15m -r list -c 1000 -t 10000 > data_thres10000.out

