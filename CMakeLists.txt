cmake_minimum_required(VERSION 3.15)

project(MathLab)

set(Application_Name "MathLab")

set(DCMAKE_SYSTEM_VERSION 10.0)
option(USE_LIBRARY "Use Library" ON)

include(CMakeDependentOption)

cmake_dependent_option(
  USE_STATIC_LIBRARY "Use Static Library" ON
  USE_LIBRARY ON
)
cmake_dependent_option(
  USE_SHARED_LIBRARY "Use Shared Library" OFF
  USE_LIBRARY ON
)

set(SourcePath ${PROJECT_SOURCE_DIR}/Source)

if(USE_LIBRARY)

file(GLOB_RECURSE _sources 
  ${SourcePath}/*.cpp 
  ${SourcePath}/*.h)

add_library(${Application_Name} STATIC "")

target_sources(${Application_Name} PRIVATE
  ${_sources}
)

target_include_directories(${Application_Name}  PUBLIC
  ${SourcePath}
)

else()

endif()


add_executable(main "main.cpp")
target_link_libraries(main PRIVATE
  ${Application_Name}
)