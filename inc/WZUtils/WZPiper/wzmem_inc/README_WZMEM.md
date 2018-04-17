## WZMEM use shared memory to communicate between proccess

##### Members: luoqingming huangxiaolin

----

### Interface Instructions:

- MemEngine class template interface:

```
// To use this, the Server and client should decide the QueueDataType, DataQueueSize and MaxReaderSize at first
/***************************************************************************
Description: MemEngine reads data from shared memory(pop data from the MemQueue)
             MemEngine writes data into shared memory(push data to the MemQueue)
****************************************************************************/
template <typename QueueDataType, int DataQueueSize, int MaxReaderSize>
class MemEngine{

    /************************************************* 
    Function: MemEngine
    Description: Constructor, init some variables
    InputParameter: none
    Return: none
    *************************************************/
    MemEngine();

    /************************************************* 
    Function: init
    Description: read configure file and init as server or client,
      server will create the shared memory and init the QueueManager
    InputParameter: 
      file_path: the path of the configure file
      piperMode: the flag to mark server or client, 
        0 or WZ_PIPER_SERVER as server,
        1 or WZ_PIPER_CLIENT as client
    Return: positive if create succeed, -1 if failed
    *************************************************/
    int init(char file_path[256], int piperMode);

    /************************************************* 
    Function: wzRecv
    Description: read a frame from shared memory queue
    InputParameter: 
      frame: pop(memcpy) a datum in queue to mail
    Return: 1 if receive succeed, 0 if failed
    *************************************************/
    int Recv(QueueDataType &data);

    /************************************************* 
    Function: wzSend
    Description: write a frame to shared memory queue
    InputParameter: 
      frame: the datum to push(memcpy) into queue
    Return: 1 if send succeed, 0 if failed
    *************************************************/
    int Send(QueueDataType &data);
};
```

- QueueManager use in MemEngine:

```
// To use this, the MemEngine should decide the DataQueueSize and MaxReaderSize first
/***************************************************************************
Description: QueueManager manage the MemQueue used in shared memory
****************************************************************************/
template <typename QueueDataType, int DataQueueSize, int MaxReaderSize>
struct QueueManager
{

   // the MemQueue<DataType, DataQueueSize(must be 2^n), MaxReaderSize>
   MemQueue<QueueDataType, DataQueueSize, MaxReaderSize > frame_rec_queue;
   MemQueue<QueueDataType, DataQueueSize, MaxReaderSize > frame_req_queue;

   // Return: 1 if initManager succeed, 0 if failed
   bool initManager(){

      // call different queue's init
      if (!frame_req_queue.initQueue()) {
         return false;
      }

      if (!frame_rec_queue.initQueue()) {
         return false;
      }

      return true;
   }
};
```

----

### Usage Instructions:

#### Configure file must be included:

```
[MemInfo]
# key of the shared memory, better not to use 0
key=12
```

#### Include .h and .hpp file in folder WZUtils/WZPiper/inc/util/wzmem_inc/, or remember to copy them to your include folder:

```
memengine.hpp
memqueue.hpp
```

#### no need to link .so file!!!


#### The CmakeLists.txt should add following statements:

```
SET(UTILS_SO iniparser logger glog)

INCLUDE_DIRECTORIES(${INC_FOLDER_PATH}) # the include folder contains two h&hpp file above

LINK_DIRECTORIES(${LIB_FOLDER_PATH})

ADD_EXECUTABLE(main main.cpp)

// link UTILS_SO before link MEM_FILE!!!
TARGET_LINK_LIBRARIES(main ${UTILS_SO})
```

#### For MemEngine user:

- If you are the server(which should run first) like TraderServer and MdServer, follow the next step:

```
// declare
WZPiper<MemEngine<DataType, QueueSize, MaxReaderSize> >  * memServer;

// new a memServer object
memServer = new WZPiper<MemEngine<DataType, QueueSize, MaxReaderSize> > ();

// read configuer file and create the shared memory, set as WZ_PIPER_SERVER
memServer -> init(filePath, WZ_PIPER_SERVER);

// receive message
int rtn = memServer -> wzRecv(recvFrame);
if(rtn == -1) {
  printf("read failed\n");
}
else if (rtn == 0) {
  printf("read succeed\n");
}

// write message
Frame sendFrame;
sendFrame.source = 1;
sendFrame.msg_type = 1;
sendFrame.error_id = WZ_ERROR_ID_SUCCESS;
sendFrame.rtn_type = 1;
sendFrame.length = 1;


// send message
int rtn = memServer -> wzSend(sendFrame);
if(rtn == -1) {
  printf("write failed\n");
}
else if (rtn == 0) {
  printf("write succeed\n");
}


// delete it.
delete memServer;

```

- If you are the client(which should run later) like strategy, follow the next step:

```
// declare
WZPiper<MemEngine<DataType, QueueSize, MaxReaderSize> >  * memClient;

// new a memClient object 
memClient = new WZPiper<MemEngine<DataType, QueueSize, MaxReaderSize> > ();

// read configuer file and create the shared memory, set as WZ_PIPER_CLIENT
memClient -> init(filePath, WZ_PIPER_CLIENT);

// write message
Frame sendFrame;
sendFrame.source = 1;
sendFrame.msg_type = 1;
sendFrame.error_id = WZ_ERROR_ID_SUCCESS;
sendFrame.rtn_type = 1;
sendFrame.length = 1;


// send message
int rtn = memClient -> wzSend(sendFrame);
if(rtn == -1) {
  printf("write failed\n");
}
else if (rtn == 0) {
  printf("write succeed\n");
}

// receive message
int rtn = memClient -> wzRecv(recvFrame);
if(rtn == -1) {
  printf("read failed\n");
}
else if (rtn == 0) {
  printf("read succeed\n");
}
// delete it.
delete memClient;

```

------

### Related Knowledge:

- ##### 无锁队列：
    
  - www.cnblogs.com/sniperHW/p/4172248.html

- ##### C++类继承：

  - **public 继承：**基类的public，protected成员在子类中访问属性不变，子类新增的成员函数可以直接访问，但是对于基类的private成员依然是基类的私有，子类无法直接进行访问。
  - **private 继承：**基类的public，protected成员转变为子类的private成员，子类新增的成员函数可以进行访问，对于基类的private成员依然是基类的私有，子类无法直接进行访问。
  - **protected 继承：**基类的public，protected成员转变为子类的protected成员，子类新增的成员函数可以进行访问，对于基类的private成员依然是基类的私有，子类无法直接进行访问。
