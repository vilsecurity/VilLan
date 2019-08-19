cmake_minimum_required(VERSION 3.10)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  message("Using ccache")
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

set(CMAKE_CXX_STANDARD 17)

project(villan)

set(PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto)
find_package(Boost REQUIRED system)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

file(GLOB_RECURSE villan_source ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_subdirectory(proto)

add_executable(villan ${villan_source})

target_link_libraries(villan
  PUBLIC
  Boost::boost
  Boost::system
  OpenSSL::SSL
  Threads::Threads
  villan_proto
  PRIVATE
  spiderweb_proto
)

target_include_directories(villan
  PUBLIC
  $<INSTALL_INTERFACE:include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include(GNUInstallDirs REQUIRED)
install(TARGETS villan
    EXPORT villan
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
set_target_properties(villan PROPERTIES EXPORT_NAME VilSecurity::VilLan)

#enable_testing()
#find_package(GTest REQUIRED)
#file(GLOB_RECURSE tests_source test/*.cpp)
#add_executable(tests ${tests_source})
#target_link_libraries(tests villan GTest::GTest)
#gtest_discover_tests(tests)

