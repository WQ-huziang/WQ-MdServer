//
//
// Author : huziang
// This is a cpp file corresponded with it's head file

#include "MessageQueue.h"
#include <iostream>
#include "semaphore.h"

MessageQueue::MessageQueue(int _typelen, int _cap) {
  head = 0;
  tail = 0;
  cap = _cap;
  typelen = _typelen;
  datas = new char[(cap + 1) * typelen];
  pthread_mutex_init(&lenlock, NULL);  // normal lock
  // get semaphores' id
  if (!set_semvalue(&prosem_id, cap)) {
    perror("Can't create product semaphore!");
    exit(1);
  }
  if (!set_semvalue(&consem_id, 0)) {
    perror("Can't create consume semaphore!");
    exit(1);
  } 
}

MessageQueue::~MessageQueue() {
  delete [] datas;
  pthread_mutex_destroy(&lenlock);
  // destroy semaphore   
  del_semvalue(&prosem_id);
  del_semvalue(&consem_id); 
}

bool MessageQueue::send(void *_data) {
  // if full, drop oldest data, get the semaphore
  if (!trywait_semvalue(&prosem_id)) {
    // some extreme status
    if (!trywait_semvalue(&consem_id)) {
      return false;
    }
    // same as receive
    pthread_mutex_lock(&lenlock);
    int index = head++;
    if (head == cap + 1) {
      head = 0;
    }
    pthread_mutex_unlock(&lenlock);
  }

  pthread_mutex_lock(&lenlock);
  int index = tail++;
  if (tail == cap + 1) {
    tail = 0;
  }
  pthread_mutex_unlock(&lenlock);
  memcpy(datas + index * typelen, _data, typelen);
  signal_semvalue(&consem_id);
  return true;
}

bool MessageQueue::receive(void *_data) {
  wait_semvalue(&consem_id);
  pthread_mutex_lock(&lenlock);
  int index = head++;
  if (head == cap + 1) {
    head = 0;
  }
  pthread_mutex_unlock(&lenlock);
  memcpy(_data, datas + index * typelen, typelen);
  signal_semvalue(&prosem_id);
  return true;
}

void MessageQueue::clear() {
  head = 0;
  tail = 0;
}
