SET(CLASS_FILE
  Md/mdengine.cpp
  Md/custommdspi.cpp
)
SET(MAIN_FILE Main/main.cpp)
SET(CTP_SO
  thostmduserapi
  thosttraderapi
)
SET(WZUTIL_SO
  tcp
  udp
  logger
  glog
  mongodbengine
  mongocxx
  bsoncxx
  iniparser
  pthread
)

ADD_EXECUTABLE(mdserver ${MAIN_FILE} ${CLASS_FILE})
TARGET_LINK_LIBRARIES(mdserver ${CTP_SO} ${WZUTIL_SO})
