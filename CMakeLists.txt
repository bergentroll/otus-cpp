cmake_minimum_required(VERSION 3.12.4) # Потому что это ранняя проверенная.

if ($ENV{TRAVIS_BUILD_NUMBER})
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

add_library(helloworld helloworld.cpp)
add_executable(helloworld_cli main.cpp)
set_target_properties(helloworld_cli PROPERTIES OUTPUT_NAME helloworld)
target_link_libraries(helloworld_cli helloworld)

if(Boost_FOUND)
  add_executable(test_suite test.cpp)
  target_link_libraries(
    test_suite
    PRIVATE
    helloworld
    Boost::unit_test_framework)
  enable_testing()
  add_test(test_suite test_suite)
else()
  message(WARNING "Test suite will not be launched because Boost not found.")
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=2.15)")
include(CPack)
