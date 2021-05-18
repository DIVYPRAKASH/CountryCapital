cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(THREADS_PREFER_PTHREAD_FLAG ON) 
find_package(Threads REQUIRED) 
find_package(Boost 1.60.0 REQUIRED COMPONENTS program_options)

############################
##      SOURCE FILES      ##
############################
add_executable(${PROJECT_NAME} src/main.cpp)

#####################################
##      HEADERS SEARCH PATHS       ##
##################################### 
set(PROJECT_INCLUDE_DIR "src/include")

set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.9.1)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

#######################################
##      ADDING HEADERS LIBRARY       ##
#######################################
include_directories(${HEADER_SEARCH_PATHS} ${Boost_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json cpr::cpr ${Boost_LIBRARIES})