#include "helloworld.h"

using namespace helloworld;

const std::string HelloWorld::data { "Hello, World!\n" };

void HelloWorld::operator() (std::ostream &os) {
  os << HelloWorld::data << std::flush;
}
