#include <semaphore.h>   // using semaphore headerfile to create functions for synchronization problems using semaphore..



//***Rendezvous Functions ***

sem_t aArrived;
sem_t bArrived;

void rendezvous(){
    //initializes semaphore and does error handling
    if(sem_init(&aArrived,0,0)==-1){
        perror("error initilalizing semaphore for rendezvous\n");
    }
    if (sem_init(&bArrived,0,0)==-1){
        perror("error initilalizing semaphore for rendezvous\n");
    }
}

void rendez_a_wait(){
    //rendezvous thread 1 wait
    sem_post(&aArrived);
    sem_wait(&bArrived);
}

void rendez_b_wait(){
    //rendezvous thread 2 wait
    sem_post(&bArrived);
    sem_wait(&aArrived);
}


//*** Mutex Functions ***

sem_t smutex;

void mutex(){
    if(sem_init(&smutex,0,1)==-1){
        perror("error initilalizing semaphore for mutex\n");
    }
}

void mutex_wait(){
    sem_wait(&smutex);
}

void mutex_signal(){
    sem_post(&smutex);
}


//*** Multiplex Functions ***
sem_t smultiplex;

void multiplex(int n){

    if(sem_init(&smultiplex,0,n)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
}

void multiplex_wait(){
    sem_wait(&smultiplex);
}

void multiplex_signal(){
    sem_post(&smultiplex);
}


//*** Queues Functions***
sem_t slqueues;
sem_t sfqueues;
sem_t sqmutex;
sem_t sqrend;

int fcount, lcount;

void queues(){
    fcount = 0;
    lcount = 0;

    if(sem_init(&slqueues,0,0)==-1){
        perror("error initilalizing semaphore for leader queues\n");
    }
    if(sem_init(&sfqueues,0,0)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
    if(sem_init(&sqmutex,0,1)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
    if(sem_init(&sqrend,0,0)==-1){
        perror("error initilalizing semaphore for queues\n");
    }
}

void lqueues_wait(){
    sem_wait(&sqmutex);
    if(fcount>0){
        fcount--;
        sem_post(&sfqueues);
    }
    else{
        lcount++;
        sem_post(&sqmutex);
        sem_wait(&slqueues);
    }
}
void lqueues_signal(){
    sem_wait(&sqrend);
    sem_post(&sqmutex);

}

void fqueues_wait(){
    sem_wait(&sqmutex);
    if(lcount>0){
        lcount--;
        sem_post(&slqueues);
    }
    else{
        fcount++;
        sem_post(&sqmutex);
        sem_wait(&sfqueues);
    }
}

void fqueues_signal(){
    sem_post(&sqrend);
}


//*** Synchronization Problem - Sleeping Barber***

sem_t waitingRoom; // Signal that the waiting room can accommodate  customers
sem_t barberSeat; // Signal to ensure exclusive access to the barber seat
sem_t doneWithCustomer; // Signals the customer that the barber is done with him/her
sem_t barberBed; // Signal to wake up the barber

void sbarber(int numWaitingChairs){
    // Initialize the semaphores
    if(sem_init(&waitingRoom, 0, numWaitingChairs)==-1){
        perror("error initilalizing semaphore for waiting room\n");
    }
    if(sem_init(&barberSeat, 0, 1)==-1)
    {
        perror("error initilalizing semaphore for barber seat\n");
    }
    if(sem_init(&doneWithCustomer, 0, 0)==-1)
    {
        perror("error initilalizing semaphore for done customer\n");
    }
    if(sem_init(&barberBed, 0, 0)==-1)
    {
        perror("error initilalizing semaphore for barber bed\n");
    }
}

void sbarber_bed_wait(){
    sem_wait(&barberBed); // barber sleeping
}

void sbarber_bed_signal(){
     sem_post(&barberBed); // Wake up barber
}

void sbarber_doneCust_wait(){
    sem_wait(&doneWithCustomer);
}

void sbarber_doneCust_signal(){
    sem_post(&doneWithCustomer);
}

void sbarber_waitingRoom_wait(){
    sem_wait(&waitingRoom);
}

void sbarber_waitingRoom_signal(){
    sem_post(&waitingRoom);
}

void sbarber_bSeat_wait(){
    sem_wait(&barberSeat); // Wait for the barber to become free
}

void sbarber_bSeat_signal(){
    sem_post(&barberSeat); // Give up seat
}

//*** Barrier ***

int bCount=0;
int bTotal;
sem_t sbarrier, bmutex;

void barrier(int n){
    bTotal=n;

    if(sem_init(&sbarrier,0,0)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
    if(sem_init(&bmutex,0,1)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }

}

void barrier_wait(){

    sem_wait(&bmutex);
    bCount++;
    sem_post(&bmutex);

    if(bCount==bTotal)
        sem_post(&sbarrier);

    sem_wait(&sbarrier);
    sem_post(&sbarrier);
}


//*** Reusable Barrier ***

int rbCount, rbTotal,i;
sem_t rbMutex, turnstile, turnstile2;

void reusable_barrier(int n){

    rbCount=0;
    rbTotal=n;

    if(sem_init(&rbMutex,0,1)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
    if(sem_init(&turnstile,0,0)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
    if(sem_init(&turnstile2,0,1)==-1){
        perror("error initilalizing semaphore for multiplex\n");
    }
}

void phase1(){
    sem_wait(&rbMutex);
    rbCount++;
    if(rbCount==rbTotal){
        for(i=0;i<rbTotal;i++){
            sem_post(&turnstile);
        }
    }
    sem_post(&rbMutex);
    sem_wait(&turnstile);
}

void phase2(){
    sem_wait(&rbMutex);
    rbCount--;
    if(rbCount==0){
        for(i=0;i<rbTotal;i++){
            sem_post(&turnstile2);
        }
    }
    sem_post(&rbMutex);
    sem_wait(&turnstile2);
}

void reusable_barrier_wait(){
    phase1();
    phase2();
}