
Hourglass benchmark
===================

This is a jitter benchmark based on the hourglass published by John Regehr, 2002.

John Regehr: "Inferring Scheduling Behavior with Hourglass". Proceedings of the 2002 USENIX Technical Conference FREENIX Track. [Online](http://static.usenix.org/publications/library/proceedings/usenix02/tech/freenix/regehr.html).

The code is C11 and warning-free (except unused parameters) and should be compatible
with UNIX systems. Tested only on Linux (OpenSUSE 13.1).

The calibration (ticks per second of the CPU's time-stamp counter) is not very
stable. This could be due to the power governor changing the frequency during
run-time. The program should be executed in the *performance* mode. So far, this is
not implemented in the setup. For all CPUs, issue (as root):

    :::bash
    # echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor

(Undo with *ondemand* or whatever was in these files before.)

Contact
=======
Georg Wassen <georg.wassen@gmail.com>

