SET(CLASS_FILE
  Md/CustomMdSpi.cpp
  Md/MdEngine.cpp
  Main/IniConfig.cpp
  OutputAdapter/TcpOutputAdapter.cpp
  OutputAdapter/UdpOutputAdapter.cpp
)
SET(MAIN_FILE Main/main.cpp)
SET(CTP_SO thostmduserapi thosttraderapi)

# add c++11 and -g
SET(CMAKE_CXX_FLAGS "-std=c++11 -g")

ADD_EXECUTABLE(mdserver ${MAIN_FILE} ${CLASS_FILE})
TARGET_LINK_LIBRARIES(mdserver ${CTP_SO} ${TEST_LIB})