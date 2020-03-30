#include "helloworld.h"
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_helloworld)

BOOST_AUTO_TEST_CASE(test_output) {
  std::ostringstream oss { };
  helloworld::HelloWorld()(oss);
  BOOST_CHECK(oss && oss.str() == "Hello, World!\n");
}

BOOST_AUTO_TEST_SUITE_END()
