cmake_minimum_required(VERSION 3.1)
project(ZedDriver)



find_package(OpenCV REQUIRED)
find_package(ZED REQUIRED)
#find_package(CUDA REQUIRED)

add_executable(run test.cpp)

include_directories(/usr/local/zed/include)
#include_directories(/usr/local/zed/include/sl)
#include_directories(/usr/local/cuda-11.1/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(home/ydm/Codes/ZedDriver)

#ink_directories(/usr/local/zed/lib)
link_directories(/usr/local/cuda-11.1/lib64)




target_link_libraries(run ${OpenCV_LIBS})
target_link_libraries(run ${ZED_LIBRARIES})
#target_link_libraries(run libsl_ai.so)
#target_link_libraries(run libsl_zed.so)
#target_link_libraries(run ${CUDA_LIBS})


