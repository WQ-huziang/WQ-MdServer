//
//
// Author : huziang
// This is a class, used to transform message between one thread and another thread
// This class use void point (void*) to store any types of data

#ifndef MDSERVER_MESSAGEQUEUE_H_
#define MDSERVER_MESSAGEQUEUE_H_

#include <pthread.h>

class MessageQueue {
 private:
  inline int length() { return tail + (tail < head) * (cap + 1) - head; }
  inline bool empty() { return head == tail; }
  inline bool full() { return head == tail + 1; }
  int head;
  int tail;
  int typelen;
  int cap;
  char *datas;
  pthread_mutex_t lenlock;
  int prosem_id, consem_id;  // product Semaphore and consume Semaphore

 public:
  MessageQueue(int typelen, int cap = 100);
  ~MessageQueue();
  bool send(void*);
  bool receive(void*);   // if return NULL, mean failure
  void clear();
  inline int capacity() { return cap; }
};

#endif // MDSERVER_MESSAGEQUEUE_H_