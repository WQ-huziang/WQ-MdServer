//
//
// Author : huziang
// This is a class, used to transform message between one thread and another thread
// This class use void point (void*) to store any types of data

#ifndef MDSERVER_MESSAGEQUEUE_H_
#define MDSERVER_MESSAGEQUEUE_H_

#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <cstddef>


class MessageQueue {
 private:
  struct Node {
    void *data;
    Node *next;
    Node(void *_data = nullptr, Node *_next = nullptr)
        : data(_data),
          next(_next)
      {}
  };
  int len;
  int cap;
  Node *head;
  Node *tail;
  pthread_mutex_t lenlock;
  sem_t datasem;

 public:
  MessageQueue(int cap = 100);
  ~MessageQueue();
  bool send(void*);
  bool receive(void*);
  void clear();
  inline int length() { return len; }
  inline int capacity() { return cap; }
  inline bool empty() { return len == 0; }
  inline bool full() { return len == cap; }
};

#endif // MDSERVER_MESSAGEQUEUE_H_