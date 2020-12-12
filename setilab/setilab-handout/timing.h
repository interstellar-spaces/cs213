#ifndef _timing
#define _timing

// Basic timing 
// This is elapsed real time with the
// resolution of the gettimeofday() system call
//
// You can meaningfully subtract these times even 
// they were taken on different cores
//
double get_seconds();
double get_seconds_diff(double first);

// Advanced timing
//
// This is elapsed real time using the processor cycle counter
// Note that subtracting two cycle counts only makes sense 
// if they are taken on the SAME core
//
unsigned long long get_cycle_count();
unsigned long long get_cycle_count_diff(unsigned long long first);
double cycles_to_seconds(unsigned long long count);
unsigned long long timing_overhead();

// Resource usage
//
// This determines the resources that the calling thread or process 
// consumed so far
typedef struct resources_ {
  double usertime; // seconds of processor time spent in the process/thread
  double systime;  // seconds of processor time spent in the kernel
                   // on behalf of the program
  long   pagefaults; // number of memory page faults
  long   pageswaps;  // number of memory page swaps (to/from disk)
  long   ioblocks;   // number of blocks that have been input or output to I/O devs
  long   sigs;       // number of signals received
  long   contextswitches; // number of context switches
} resources ;

typedef enum {THIS_PROCESS, THIS_THREAD} resource_scope;
  
int get_resources(resources *dest, resource_scope scope);
int get_resources_diff(resources *first, resources *second, resources *diff);


#endif
