SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(CtpSystem)

SET(CPP_LIST 
	Md/CustomMdSpi.cpp
	Md/MdEngine.cpp
	Td/CustomTradeSpi.cpp
	Main/ExchangeSystem_main.cpp
	Main/IniConfig.cpp
	OutputAdapter/OutputAdapter.cpp
)

SET(CMAKE_BUILD_TYPE "Debug")

ADD_EXECUTABLE(CtpSystem ${CPP_LIST})

TARGET_LINK_LIBRARIES(CtpSystem thostmduserapi thosttraderapi)
