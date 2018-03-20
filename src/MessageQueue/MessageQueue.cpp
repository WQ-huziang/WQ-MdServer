//
//
// Author : huziang
// This is a cpp file corresponded with it's head file

#include "MessageQueue.h"
#include "pthread.h"

MessageQueue::MessageQueue(int _cap) {
  cap = _cap;
  len = 0;
  head = new Node();
  tail = head;
  pthread_mutex_init(&lenlock, NULL);  // normal lock
  sem_init(&datasem, 0, 0);  // normal semaphore
}

MessageQueue::~MessageQueue() {
  clear();
  delete head;
  pthread_mutex_destroy(&lenlock);
  sem_destroy(&datasem);
}

bool MessageQueue::send(void *data) {
  if (full()) {
    return false;
  }

  pthread_mutex_lock(&lenlock);
  len++;
  pthread_mutex_unlock(&lenlock);

  tail->next = new Node(data);
  tail = tail->next;

  sem_post(&datasem);
  return true;
}

bool MessageQueue::receive(void *data) {
  sem_wait(&datasem);

  pthread_mutex_lock(&lenlock);
  len--;
  if (empty()) {
    tail = head;
  }
  pthread_mutex_unlock(&lenlock);

  Node* temp = head->next;
  head->next = temp->next;
  data = temp->data;
  delete temp;

  return true;
}

void MessageQueue::clear() {
  Node *temp = head->next;
  while (temp != nullptr) {
    Node* del = temp;
    temp = temp->next;
    delete del;
  }
  len = 0;
}