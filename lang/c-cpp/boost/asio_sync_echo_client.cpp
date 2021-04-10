#include <iostream>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

using boost::asio::ip::tcp;

enum { BUF_SIZE = 1024 };

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
    return 1;
  }

  try {
    boost::asio::io_context ioc;

    tcp::resolver resolver(ioc);
    auto endpointers = resolver.resolve(tcp::v4(), argv[1], argv[2]);

    tcp::socket socket(ioc);
    boost::asio::connect(socket, endpointers);
    boost::system::error_code ec;

    char buf[BUF_SIZE];
    while(true) { //main loop

      std::size_t data_length;
      do {
        std::cout << "Enter msessage: ";
        std::cin.getline(buf, BUF_SIZE-1);
        buf[BUF_SIZE-1] = 0;
        data_length = std::strlen(buf);
      } while(data_length == 0);
      boost::asio::write(socket, boost::asio::buffer(buf, data_length));

      //char reply[BUF_SIZE];
      //std::size_t reply_length = socket.read_some(boost::asio::buffer(reply, data_length), ec);
      //if (ec == boost::asio::error::eof) {
      //  std::cout << "服务关闭连接" << std::endl;
      //  break;
      //} else if (ec) {
      //  throw boost::system::system_error(ec);
      //}
      //std::cout.write(reply, reply_length);
      //std::cout << std::endl;

      std::size_t total_reply_length = 0;
      do {
        std::array<char, BUF_SIZE> reply;
        std::size_t reply_length = socket.read_some(boost::asio::buffer(reply), ec);
        if (ec == boost::asio::error::eof) {
          std::cout << "服务关闭连接" << std::endl;
          return 0;
        } else if (ec) {
          throw boost::system::system_error(ec);
        }

        std::cout.write(reply.data(), reply_length);
        total_reply_length += reply_length;
      } while(total_reply_length < data_length);
      std::cout << std::endl;
    }

  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return 2;
  }
  return 0;
}
