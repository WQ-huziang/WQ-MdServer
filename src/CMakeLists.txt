SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(CtpSystem)

SET(CPP_LIST
  Md/CustomMdSpi.cpp
  Md/MdEngine.cpp
  Main/main.cpp
  Main/IniConfig.cpp
  OutputAdapter/UdpOutputAdapter.cpp
  OutputAdapter/TcpOutputAdapter.cpp
)

SET(CMAKE_BUILD_TYPE "Debug")

ADD_EXECUTABLE(mdserver ${CPP_LIST})

TARGET_LINK_LIBRARIES(mdserver thostmduserapi thosttraderapi)
