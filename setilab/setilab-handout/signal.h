#ifndef __signal
#define __signal

typedef struct _signal {
    int    map_fd;       // >=0 => fd of mapped file
    int    num_samples;  // number of samples
    double Fs;          // sample rate
    double *data;       // loaded or mapped data
} signal;

signal *allocate_signal(int numsamples, double Fs, int for_mapping);
void    free_signal(signal *sig);

signal *load_text_format_signal(char *file);
int     save_text_format_signal(char *file, signal *sig);

signal *load_binary_format_signal(char *file);
int     save_binary_format_signal(char *file, signal *sig);

signal *map_binary_format_signal(char *file);
int     unmap_binary_format_signal(signal *sig);

#endif
