#include <iostream>

namespace helloworld {
  class HelloWorld {
  public:
    void operator() (std::ostream &os = std::cout);

  protected:
    static const std::string data;
  };
}
