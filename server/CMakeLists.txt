cmake_minimum_required(VERSION 3.6)
project(country_server)

set(CMAKE_CXX_STANDARD 17)
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


#####################################
##      HEADERS SEARCH PATHS       ##
##################################### 
#set(PROJECT_INCLUDE_DIR "src/include")
#set(PISTACHE_INCLUDE_DIR "pistache/include")

##set(HEADER_SEARCH_PATHS ${PROJECT_INCLUDE_DIR} ${PISTACHE_INCLUDE_DIR})

#####################################
##      LIBRARY SEARCH PATHS       ##
#####################################
# set(PISTACHE_LIBRARY "${PROJECT_SOURCE_DIR}/pistache/lib/src/libpistache.a")
# set(EXTRA_LIBRARY "-pthread")

# set(LIBRARIES_SEARCH_PATHS ${PISTACHE_LIBRARY})


#######################################
##      ADDING HEADERS LIBRARY       ##
#######################################
include_directories(${HEADER_SEARCH_PATHS})
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json PkgConfig::Pistache Threads::Threads)