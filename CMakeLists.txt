# TODO Update.
cmake_minimum_required(VERSION 3.0)

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

add_executable(helloworld helloworld.cpp)

# TODO Testing.
# TODO Lib.

install(TARGETS helloworld RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>=2.15)")
include(CPack)
