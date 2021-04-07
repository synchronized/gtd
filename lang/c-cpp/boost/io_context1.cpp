#include <boost/asio.hpp>

int main() {
  boost::asio::io_context ioc;
  ioc.run();
  return 0;
}
