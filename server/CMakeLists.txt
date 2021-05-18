cmake_minimum_required(VERSION 3.6)
project(country_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(THREADS_PREFER_PTHREAD_FLAG ON) 
find_package(Threads REQUIRED) 

############################
##      SOURCE FILES      ##
############################


find_package(PkgConfig)
pkg_check_modules(Pistache REQUIRED IMPORTED_TARGET libpistache)

add_executable(${PROJECT_NAME} src/main.cpp)


include(FetchContent)

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
include_directories(${HEADER_SEARCH_PATHS})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json PkgConfig::Pistache Threads::Threads)