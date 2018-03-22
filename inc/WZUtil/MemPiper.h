#ifndef MEMPIPER_H_
#define MEMPIPER_H_

#include "WZPiper.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>

#define PRT(...) printf(__VA_ARGS__);

#ifndef SHM_FAILED 
#define SHM_FAILED -1  
#endif // SHM_FAILED

#define SHM_FLAG IPC_CREAT|0666
//#define SHM_FLAG IPC_CREAT|IPC_EXCL|SHM_R|SHM_W

class MemPiper : public WZPiper {
 public:
   
   // from WZPiper
   virtual void init_as_server();
   virtual void set_config_info(char file_path[256]);
   virtual void init_as_client();
   virtual int do_read(Frame &mail);
   virtual void do_write(Frame mail);

 public:

   
   // build-in function
   MemPiper();
   ~MemPiper();

   // create shared memory function
   bool createMemory();

   // destroy shared memory function
   bool destroyMemory();

   // attach shared memory function
   bool attachMemory(char*& pmemoryAddr);

   // detach shared memory function
   bool detachMemory(char* pmemoryAddr);


 private:

   // shared memory information
   int m_key;			// shared memory key
   int m_size;			// shared memory size
   int m_flag;			// shared memory flag
   int m_shmid;			// shared memory descriptor
   char *m_memoryAddr;	// shared memory address pointer
   
};

#endif // MEMPIPER_H_