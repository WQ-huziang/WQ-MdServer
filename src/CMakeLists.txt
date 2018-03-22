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
)

ADD_EXECUTABLE(mdserver ${MAIN_FILE} ${CLASS_FILE})
TARGET_LINK_LIBRARIES(mdserver ${CTP_SO} ${TEST_LIB} ${WZUTIL_SO})