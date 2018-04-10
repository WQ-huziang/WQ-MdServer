SET(CLASS_FILE
  Md/MdEngine.cpp
  Md/CustomMdSpi.cpp
  MessageQueue/MessageQueue.cpp
)
SET(MAIN_FILE Main/main.cpp)
SET(CTP_SO
  thostmduserapi
  thosttraderapi
)
SET(WZUTIL_SO
  iniparser
  TcpPiper
  UDPPiper
  Logger
  glog
  MongodbEngine
  mongocxx
  bsoncxx
)

# add mongocxx and bson include dir
SET(SHARE_LIB_PREFIX /usr/local)
INCLUDE_DIRECTORIES(${SHARE_LIB_PREFIX}/include/mongocxx/v_noabi)
INCLUDE_DIRECTORIES(${SHARE_LIB_PREFIX}/include/libmongoc-1.0)
INCLUDE_DIRECTORIES(${SHARE_LIB_PREFIX}/include/bsoncxx/v_noabi)
INCLUDE_DIRECTORIES(${SHARE_LIB_PREFIX}/include/libbson-1.0)

ADD_EXECUTABLE(mdserver ${MAIN_FILE} ${CLASS_FILE})
TARGET_LINK_LIBRARIES(mdserver ${CTP_SO} ${TEST_LIB} ${WZUTIL_SO})
