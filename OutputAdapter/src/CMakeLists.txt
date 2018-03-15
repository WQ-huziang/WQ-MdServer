SET(CMAKE_CXX_FLAGS "-std=c++11 -g")

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(OutputAdapter)

SET(CPP_LIST 
	TcpOutputAdapter.cpp
	UdpOutputAdapter.cpp
	main.cpp
)

SET(CMAKE_BUILD_TYPE "Debug")

ADD_EXECUTABLE(OutputAdapter ${CPP_LIST})
