//
//
// Author : huziang
// This is a file about semaphore

#ifndef MDSERVER_SEMAPHORE_H_
#define MDSERVER_SEMAPHORE_H_

#include <pthread.h> 
#include <sys/sem.h>  
  
// union semun  
// {  
//     int val;  
//     struct semid_ds *buf;  
//     unsigned short *arry;  
// };  

pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
long long key = 0;    

// return given sem_id
bool set_semvalue(int *sem_id, int initvalue) {
    // key ++ must be lock
    pthread_mutex_lock(&mylock);
    *sem_id = semget((key_t)key++, 1, 0666 | IPC_CREAT); 
    pthread_mutex_unlock(&mylock);

    // init semaphore, init value is given value
    union semun sem_union;  
    sem_union.val = initvalue;  
    return semctl(*sem_id, 0, SETVAL, sem_union) != -1;  
}  
  
bool del_semvalue(int *sem_id)  
{
    return semctl(*sem_id, 0, IPC_RMID) != -1;   
}  

bool trywait_semvalue(int *sem_id) {
    // semaphore - 1 
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = -1;  // wait 
    sem_b.sem_flg = IPC_NOWAIT | SEM_UNDO;  
    return semop(*sem_id, &sem_b, 1) != -1;
}

bool wait_semvalue(int *sem_id) {  
    // semaphore - 1 
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = -1;  // wait 
    sem_b.sem_flg = SEM_UNDO;  
    return semop(*sem_id, &sem_b, 1) != -1;
}  
  
bool signal_semvalue(int *sem_id) {  
    // semaphore + 1 
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = 1;  // signal  
    sem_b.sem_flg = SEM_UNDO;  
    return semop(*sem_id, &sem_b, 1) != -1;
}

#endif  // MDSERVER_SEMAPHORE_H_