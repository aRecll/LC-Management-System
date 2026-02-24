


cmake_minimum_required (VERSION 3.8)

project ("LogiCoreManagementSystem")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    
    add_compile_options(/W4 /MP)
else()
    add_compile_options(-Wall -Wextra -pthread)
endif()

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
 endif()


file(GLOB_RECURSE EXTERNAL_SOURCES 
    #"external/*.cpp" 
    "external/*.h")
file(GLOB_RECURSE APP_SOURCES
    "src/*.cpp"
    "src/*.h"
)

add_executable(LogiCore ${APP_SOURCES} ${EXTERNAL_SOURCES})
 target_include_directories(LogiCore  PRIVATE src external)
 

 if(UNIX)
   
    target_link_libraries(LogiCore PRIVATE pthread dl)
endif()

