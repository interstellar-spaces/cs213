#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "signal.h"


void free_signal(signal *sig)
{
    if (sig) {
	if (sig->data) { 
	    if (sig->map_fd>=0) {
		unmap_binary_format_signal(sig);
	    } else {
		free(sig->data); 
	    }
	}
	free(sig); 
    }
}

signal *allocate_signal(int numsamples, double Fs, int for_mapping) 
{
    signal *sig;

    if (!(sig=(signal *)malloc(sizeof(signal)))) { 
	perror("Not enough memory");
	return 0;
    }
    
    sig->num_samples=numsamples;
    sig->Fs=Fs; 
    sig->data=0;
    sig->map_fd=-1;

    if (!for_mapping) {
	if (!(sig->data=(double*)malloc(sizeof(double)*sig->num_samples))) { 
	    perror("Not enough memory");
	    free_signal(sig);
	    return 0;
	}
    }

    return sig;
}

signal *load_text_format_signal(char *file)
{
    FILE *f;
    int num=0;
    double junk;
    signal *sig;

    if (!(f=fopen(file,"r"))) { 
	perror("Cannot open file");
	return 0;
    }

    while (fscanf(f,"%lf",&junk)==1) { 
	num++;
    }

    printf("Found %d samples\n", num);

    sig = allocate_signal(num,0,0);

    if (!sig) { 
      fclose(f);
      return 0;
    }
    
    rewind(f);

    for (num=0;
	 num<sig->num_samples; 
	 num++) {
	if (fscanf(f,"%lf",&(sig->data[num]))!=1) { 
	    perror("Unable to read sample\n");
	    free_signal(sig);
	    return 0;
	}
    }
    
    fclose(f);

    printf("Read %d samples\n", num);

    return sig;
}


int save_text_format_signal(char *file, signal *sig)
{
    FILE *f;
    int i;

    if (!(f=fopen(file,"w"))) { 
	perror("Cannot open file");
	return -1;
    }
    
    for (i=0;i<sig->num_samples;i++) {
	fprintf(f,"%lf\n",sig->data[i]);
    }
    
    fclose(f);

    return 0;
    

}

#define OFFSET_TO_DATA                   0

int get_num_samples_from_binary_file(char *file, int map)
{
  struct stat s;

  if (lstat(file, &s)) {
    perror("cannot stat file");
    return 0;
  }
  
  return (s.st_size-OFFSET_TO_DATA)/sizeof(double);
}


signal *load_binary_format_signal(char *file)
{
  int fd;
  int num=0;
  signal *sig;

  num=get_num_samples_from_binary_file(file,0);

  if (num<=0) { 
    return 0;
  }

  if ((fd=open(file,O_RDONLY))<0) { 
    perror("Cannot open file");
    return 0;
  }

  sig = allocate_signal(num,0,0);

  if (!sig) { 
    close(fd);
    return 0;
  }

  lseek(fd,OFFSET_TO_DATA,SEEK_SET);

  int left = num*sizeof(double);   // number of bytes left to read
  char *cur = (char*)(sig->data);  // location of next read
  int thisread;

  while (left>0) { 
    thisread = read(fd,cur,left);
    if (thisread<=0) { 
      perror("Read failure");
      free_signal(sig);
      return 0;
    }
    cur+=thisread;
    left-=thisread;
  }

  close(fd);

  printf("Read %d samples\n", num);
  
  return sig;
}


int save_binary_format_signal(char *file, signal *sig)
{
  int fd;

  if ((fd=open(file,O_WRONLY | O_CREAT,0x644))<0) { 
    perror("Cannot open file");
    return -1;
  }

  lseek(fd,OFFSET_TO_DATA,SEEK_SET);

  int left = sig->num_samples*sizeof(double);   // number of bytes left to read
  char *cur = (char*)(sig->data);  // location of next read
  int thiswrite;

  while (left>0) { 
    thiswrite = write(fd,cur,left);
    if (thiswrite<=0) { 
      perror("Write failure");
      return -1;
    }
    cur+=thiswrite;
    left-=thiswrite;
  }

  close(fd);

  printf("Wrote %d samples\n", sig->num_samples);
  
  return 0;
}



signal *map_binary_format_signal(char *file)
{
  int fd;
  int num=0;
  signal *sig;

  num=get_num_samples_from_binary_file(file,1);

  if (num<=0) { 
    return 0;
  }

  if ((fd=open(file,O_RDWR))<0) { 
    perror("Cannot open file");
    return 0;
  }

  // no space allocated here
  sig = allocate_signal(num,0,1);

  if (!sig) { 
    close(fd);
    return 0;
  }


  sig->data = mmap(0,                  // map anywhere
		   num*sizeof(double), // this number of bytes
		   PROT_READ | PROT_WRITE, // Read/Write
		   MAP_SHARED, // flush writes to file
		   fd,         // this file
		   OFFSET_TO_DATA);

  if (sig->data == MAP_FAILED) { 
    perror("Cannot mmap");
    sig->data=0;
    free_signal(sig);
    return 0;
  }

  sig->map_fd = fd; // to close later
  
  return sig;
}


int unmap_binary_format_signal(signal *sig)
{
  if (sig->map_fd<0) { 
    printf("not mapped\n");
    return -1;
  }
  
  munmap(sig->data, sig->num_samples*sizeof(double));
  sig->data=0;
  close(sig->map_fd);
  sig->map_fd=-1;
  
  return 0;
}



    
