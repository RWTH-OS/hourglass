/*
 * =====================================================================================
 *
 *       Filename:  rdtsc.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  31.01.2011 10:56:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Georg Wassen (gw) (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "rdtsc.h"

static inline void cpuid(unsigned func, unsigned *eax, unsigned *ebx, unsigned *ecx, unsigned *edx) {
    asm volatile ("cpuid" : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx) : "a"(func));
}

static inline uint32_t cpuid_edx(uint32_t code) {
    uint32_t eax, ebx, ecx, edx;

    cpuid(code, &eax, &ebx, &ecx, &edx);

    return edx;
}

static uint64_t tps = 0;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  second()
 *  Description:  returns a double representation of gettimeofday (seconds.microseconds)
 * =====================================================================================
 */
static inline double second()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + 1e-6*tv.tv_usec;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  selectsleep(us)
 *  Description:  calls select() to sleep (wait) the given microseconds
 * =====================================================================================
 */
static inline void selectsleep(unsigned us)
{
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = us;
    select(0,0,0,0,&tv);    // portable way to sleep with subsecond precision
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rdtsc_ticks_per_sec()
 *  Description:  uses least squares regressen to measure the frequency of the TSC
 * =====================================================================================
 */
uint64_t rdtsc_ticks_per_sec(void)
{
    double sumx = 0, sumy = 0;
    double sumxx = 0, sumxy = 0;
    double slope;
    // least squared linear regression taken from mcert/misc/realfeed/realfeel.c
    
    const unsigned n = 30;
    unsigned i;

    for (i=0; i<n; i++) {
        double breal, real, ticks;
        uint64_t bticks = 0, aticks = 0;
        rdtsc(&bticks);
        breal = second();

        selectsleep((unsigned)(10000 + drand48() * 20000));

        rdtsc(&aticks);
        real = second() -breal;
        ticks = (double)(aticks - bticks);

        sumx += real;
        sumxx += real * real;
        sumxy += real * ticks;
        sumy += ticks;
    }
    slope = ((sumxy - (sumx*sumy) / n) / (sumxx - (sumx*sumx) / n));
     
    tps = (uint64_t)slope;
    return tps;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rdtsc_max_freq(id)
 *  Description:  reads the maximum frequency of given CPU-ID from /sys/.../cpuN/cpufreq
 *      Changes:  WASSEN, 24.5.2011: taken from hourglass via irqlab 
 * =====================================================================================
 */
uint64_t rdtsc_max_freq(int id)
{
    uint64_t mhz = -1;       
    char fname[BUFSIZ]; 
    char processor[BUFSIZ];
    char *buffer, *loc;    
    FILE *fp;              
    double tmhz;
    int ret;

    sprintf(fname, "/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_max_freq", id);

    if (NULL == (fp = fopen(fname, "r"))) {
        fprintf(stderr, "Can't open <%s>.\n", fname);
        fprintf(stderr, "Trying </proc/cpuinfo> (not as accurate)\n");

        if(NULL == (fp = fopen("/proc/cpuinfo","r"))) {
            fprintf(stderr, "Can't open </proc/cpuinfo>.\n");
            return -1;                                       
        }                                                        


        buffer = (void *) malloc(sizeof(char) * 1024 * 512);
        ret = fread(buffer, sizeof(char), 1024 * 512, fp);
        if (ret == 0) {
            fprintf(stderr, "fread() returned 0: %s\n", strerror(errno));
            return -1;
        }

        sprintf(processor, "processor\t: %d", id);
        if(NULL == (loc = strstr(buffer, processor))) {
            fprintf(stderr, "Unable to parse /proc/cpuinfo\n");
            return -1;
        }
        if(NULL == (loc = strstr(loc, "cpu MHz"))) {
            fprintf(stderr, "Unable to parse /proc/cpuinfo\n");
            return -1;                                         
        }
        loc += strlen("cpu MHz");
        while(!isdigit(*loc))
            loc++;
        loc--;
        sscanf(loc, "%lf", &tmhz);
        mhz = (uint64_t)(tmhz);
        mhz*=1000;
        free(buffer);
    } else {
        ret = fscanf(fp, "%lld", (unsigned long long*)&mhz);
        if (ret == 0) {
            fprintf(stderr, "fscanf() returned 0: %s\n", strerror(errno));
            return -1;
        }
        fclose(fp);
    }

    return mhz*1000;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rdtsc_loop(ticks)
 *  Description:  waits actively for given TSC ticks
 * =====================================================================================
 */
void rdtsc_loop(uint64_t ticks)
{
    uint64_t t_now = 0, t_end;
    rdtsc(&t_now);
    t_end = t_now + ticks;
    while (t_now < t_end) {
        rdtsc(&t_now);
    }
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rdtsc_loop_sec(ticks)
 *  Description:  waits actively for given seconds 
 *                ATTN: needs rdtsc_ticks_per_sec() unless that function was previously
 *                called (this function MIGHT use syscalls!)
 * =====================================================================================
 */
void rdtsc_loop_sec(unsigned seconds)
{
    uint64_t t_now = 0, t_end;
    rdtsc(&t_now);
    if (tps == 0) rdtsc_ticks_per_sec();
    t_end = t_now + (uint64_t)seconds * tps;
    while (t_now < t_end) {
        rdtsc(&t_now);
    }
}

/*
 * test if TSC is invariant (return value 1)
 */
int rdtsc_is_invariant(void) {
    if (cpuid_edx(0x80000007) & (1 << 8)) { // TSC is invariant
        return 1;
    }

    return 0;
}

/*
 * measure overhead of *not* serialized rdtsc() (SHL, MOV, OR)
 */
uint64_t rdtsc_get_overhead(const uint64_t iterations) {
    uint64_t c;
    uint64_t tsc_overhead_notserial = 0;
    uint64_t tsc_start;
    uint64_t tsc_end;

    if (iterations == 0) {
        return 0;
    }

    for (c = 0; c < iterations; c++) {
#if ! __MIC__
        asm volatile("lfence");
#else
        asm volatile("lock; add $0, 0(%%rsp)" ::: "memory");
#endif
        rdtsc(&tsc_start);
        rdtsc(&tsc_end);
        tsc_overhead_notserial += tsc_end - tsc_start;
    }

    return tsc_overhead_notserial / iterations;
}

/*
 * measure overhead of serialized rdtsc_serialized() (LFENCE, SHL, MOV, OR, LFENCE)
 */
uint64_t rdtsc_get_overhead_serialized(const uint64_t iterations) {
    uint64_t c;
    uint64_t tsc_overhead_serial = 0;
    uint64_t tsc_start;
    uint64_t tsc_end;

    if (iterations == 0) {
        return 0;
    }

    for (c = 0; c < iterations; c++) {
        rdtsc_serialized(&tsc_start);
        rdtsc_serialized(&tsc_end);
        tsc_overhead_serial += tsc_end - tsc_start;
    }

    return tsc_overhead_serial / iterations;
}
