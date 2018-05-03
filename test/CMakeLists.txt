SET(CLASS_FILE
  ../src/Md/mdengine.cpp
  ../src/Md/custommdspi.cpp
)
SET(TESTMAIN_FILE benchmarktest)
SET(CTP_SO
  thostmduserapi
  thosttraderapi
)
SET(BENCHMARK_SO
  tcp
  udp
  logger
  glog
  mongodbengine
  mongocxx
  bsoncxx
  pthread
  benchmark
  iniparser
)

ADD_EXECUTABLE(${TESTMAIN_FILE} ${TESTMAIN_FILE}.cpp ${CLASS_FILE})
TARGET_LINK_LIBRARIES(${TESTMAIN_FILE} ${CTP_SO} ${BENCHMARK_SO})
