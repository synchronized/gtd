#include <iostream>
#include <boost/array.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>

using boost::asio::ip::tcp;

enum { BUF_SIZE = 1024 };

int main(int argc, char* argv[])
{
  try {
    if (argc != 3) {
      std::cerr << "Usage: client <host> <port>" << std::endl;
      return 1;
    }
    //All programs that use asio need to have at least one io_context object.

    boost::asio::io_context io_context;
    //We need to turn the server name that was specified as a parameter to the application, into a TCP endpoint. To do this we use an ip::tcp::resolver object.
    boost::system::error_code ec;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(boost::asio::ip::tcp::v4(), argv[1], argv[2], ec);
    if (ec) {
      throw boost::system::system_error(ec);
    }

    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    char buf[BUF_SIZE];
    //std::fill(buf, buf+BUF_SIZE, 0);
    std::size_t nread = socket.read_some(boost::asio::buffer(buf, BUF_SIZE-1), ec);
    if (ec) {
      throw boost::system::system_error(ec);
    }
    buf[nread] = 0;

    std::cout << "recv from server: " << buf << std::endl;

  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
