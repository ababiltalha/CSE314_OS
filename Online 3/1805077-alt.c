#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <pthread.h>
#include "zemaphore.h"

#define NUM_THREADS 3
#define NUM_ITER 10

zem_t t[NUM_THREADS];

void *justprintRRD(void *data)
{
//   int thread_id = *((int *)data);

  for(;;)
    {
      zem_down(&t[0]);
      printf("RRD\n");
      zem_up(&t[1]);
    }
   
  return 0;
}

void *justprintMTH(void *data)
{
//   int thread_id = *((int *)data);

  for(;;)
    {
      zem_down(&t[1]);
      printf("MTH\n");
      zem_up(&t[2]);
    }
   
  return 0;
}

void *justprintBB(void *data)
{
//   int thread_id = *((int *)data);

  for(;;)
    {
      zem_down(&t[2]);
      printf("BB\n");
      zem_up(&t[0]);
    }
   
  return 0;
}





int main(int argc, char *argv[])
{

  pthread_t mythreads[NUM_THREADS];
  int mythread_id[NUM_THREADS];

  for(int i =0; i < NUM_THREADS; i++){
    zem_init(&t[i], 0);
  }

  zem_up(&t[0]);

  
//   for(int i =0; i < NUM_THREADS; i++)
//     {
//       mythread_id[i] = i;
//       pthread_create(&mythreads[i], NULL, justprint, (void *)&mythread_id[i]);
//     }

    pthread_create(&mythreads[0], NULL, justprintRRD, (void *)&mythread_id[0]);
    pthread_create(&mythreads[1], NULL, justprintMTH, (void *)&mythread_id[1]);
    pthread_create(&mythreads[2], NULL, justprintBB, (void *)&mythread_id[2]);
  
  for(int i =0; i < NUM_THREADS; i++)
    {
      pthread_join(mythreads[i], NULL);
    }
  
  return 0;
}
