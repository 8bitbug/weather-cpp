cmake_minimum_required(VERSION 3.24)

project(weather-cpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXTERNAL_SOURCES
  ${CMAKE_SOURCE_DIR}/src/include/fetch/fetch.cpp
  ${CMAKE_SOURCE_DIR}/src/include/extract/extract.cpp
)

set(PROJECT_SOURCES
  src/main.cpp
)

add_executable(weather-cpp 
  ${PROJECT_SOURCES} 
  ${EXTERNAL_SOURCES}
)

target_include_directories(weather-cpp PRIVATE 
  ${CMAKE_SOURCE_DIR}/src/include/
)

find_package(CURL REQUIRED)

if (CURL_FOUND)
  target_link_libraries(weather-cpp PRIVATE 
    CURL::libcurl
  )
endif()


find_package(nlohmann_json 3.10.5 REQUIRED)
target_link_libraries(weather-cpp PRIVATE 
  nlohmann_json::nlohmann_json
)
