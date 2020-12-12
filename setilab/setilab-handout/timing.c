#define _GNU_SOURCE
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "timing.h"



double get_seconds()
{
  struct timeval t;

  gettimeofday(&t,0);
  
  return (double)t.tv_sec + (double)t.tv_usec/1e6;
}

double get_seconds_diff(double first)
{
  double second = get_seconds();
  
  return second-first;
}



#define CPU_KHZ 2792847 // clock rate on class machine

unsigned long long get_cycle_count() 
{
  unsigned long long tsc;            // 64 bits                               
  unsigned int a, d;                 // 32 bits

  // this one instruction reads the current cycle count
  // on this processor core.
  asm volatile("rdtsc"
               : "=a" (a),
                 "=d" (d));

  tsc = (((unsigned long long) d) << 32) + (unsigned long long ) a;

  return tsc;
}

unsigned long long get_cycle_count_diff(unsigned long long first)
{
    unsigned long long next = get_cycle_count();
    return next-first;
}

double cycles_to_seconds(unsigned long long count)
{
    return ((double)count)/(1000.0*(double)CPU_KHZ);
}

unsigned long long  timing_overhead()
{
  unsigned long long start, end;

  start=get_cycle_count();
  end=get_cycle_count();

  printf("timing overhead is at least %llu cycles\n",end-start);
  
  return end-start;
}


int get_resources(resources *dest, resource_scope scope)
{
  struct rusage ru;

  if (getrusage(scope==THIS_PROCESS ? RUSAGE_SELF : RUSAGE_THREAD, &ru)<0)  {
    perror("Cannot getrusage");
    return -1;
  }

  dest->usertime = (double)(ru.ru_utime.tv_sec) + (double)(ru.ru_utime.tv_usec)*1e-6;
  dest->systime = (double)(ru.ru_stime.tv_sec) + (double)(ru.ru_stime.tv_usec)*1e-6;
  dest->pagefaults = ru.ru_minflt+ru.ru_majflt;
  dest->pageswaps = ru.ru_nswap;
  dest->ioblocks = ru.ru_inblock + ru.ru_oublock;
  dest->sigs = ru.ru_nsignals;
  dest->contextswitches = ru.ru_nvcsw + ru.ru_nivcsw;
  
  return 0;
}

int get_resources_diff(resources *first, resources *second, resources *dest)
{
  
  dest->usertime = second->usertime - first->usertime;
  dest->systime = second->systime - first->systime;
  dest->pagefaults = second->pagefaults - first->pagefaults;
  dest->pageswaps = second->pageswaps - first->pageswaps;
  dest->ioblocks = second->ioblocks - first->ioblocks;
  dest->sigs = second->sigs - first->sigs;
  dest->contextswitches = second->contextswitches - first->contextswitches;

  return 0;
}  

