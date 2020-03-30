cmake_minimum_required(VERSION 3.12.4) # Потому что это ранняя проверенная.

if($ENV{TRAVIS_BUILD_NUMBER})
  set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
  set(VERSION 0.0.0)
endif()
project(helloworld VERSION ${VERSION})

set_target_properties(${TARGET} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

find_package(Boost 1.21.0 COMPONENTS unit_test_framework)
set(GTEST_SRCDIR "/usr/src/gtest/")

set(SRC_PATH "src/")
include_directories("inc/")

add_library(helloworld ${SRC_PATH}/helloworld.cpp)
add_executable(helloworld_cli ${SRC_PATH}/main.cpp)
set_target_properties(helloworld_cli PROPERTIES OUTPUT_NAME helloworld)
target_link_libraries(helloworld_cli helloworld)

if(Boost_FOUND)
  add_executable(boost_test_suite ${SRC_PATH}/boost_test.cpp)
  target_link_libraries(
    boost_test_suite
    PRIVATE
    helloworld
    Boost::unit_test_framework)
  enable_testing()
  add_test(boost_test_suite boost_test_suite)
else()
  message(
    WARNING
    "Boost test suite will not be launched because Boost ist not found.")
endif()

if(EXISTS "${GTEST_SRCDIR}/CMakeLists.txt")
  add_subdirectory(${GTEST_SRCDIR}/ ${CMAKE_BINARY_DIR}/gtest/ EXCLUDE_FROM_ALL)

  add_executable(gtest_test_suite ${SRC_PATH}/gtest_test.cpp)
  target_link_libraries(
    gtest_test_suite
    PRIVATE
    helloworld
    gtest)
  enable_testing()
  add_test(gtest_test_suite gtest_test_suite)
else()
  message(
    WARNING
    "GTest test suite will not be launched because GTest sources is not found"
    " at ${GTEST_SRCDIR}.")
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=2.15)")
include(CPack)
