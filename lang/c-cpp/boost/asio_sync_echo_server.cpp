#include <iostream>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

enum { BUF_SIZE = 1024 };

void Session(boost::asio::ip::tcp::socket socket) {
  try {
    while(true) {
      boost::array<char, BUF_SIZE> data;
      boost::system::error_code ec;
      std::size_t length = socket.read_some(boost::asio::buffer(data), ec);
      if (ec == boost::asio::error::eof) {
        std::cout << "连接被 Client 妥善关闭了" << std::endl;
        break;
      } else if (ec) {
        throw boost::system::system_error(ec);
      }

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(data, length), ignored_error);
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception:" << e.what() << std::endl;
  }
}

int main(int argc, char* argv[] ) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
    return 1;
  }

  unsigned short port = std::atoi(argv[1]);

  boost::asio::io_context ioc;
  //创建Acceptor监听新的链接
  tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), port));

  try {
    while (true) {
      Session(acceptor.accept());
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return 0;
}
