#include <iostream>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/connect.hpp>

using boost::asio::ip::tcp;

enum { BUF_SIZE = 10 };

class Client {
public:
  Client(boost::asio::io_context& ioc, const std::string& host, const std::string& port)
    :socket_(ioc), resolver_(ioc), total_reply_length(0) {
    resolver_.async_resolve(tcp::v4(), host, port,
                            std::bind(&Client::OnResolve, this, std::placeholders::_1, std::placeholders::_2));
  }

private:
  void OnResolve(boost::system::error_code ec, tcp::resolver::results_type endpoints) {
    if (ec) {
      std::cerr << "Resolve: " << ec.message() << std::endl;
      return;
    }
    boost::asio::async_connect(socket_, endpoints,
                               std::bind(&Client::OnConnect, this, std::placeholders::_1, std::placeholders::_2));
  }

  void OnConnect(boost::system::error_code ec, tcp::endpoint endpoint) {
    if (ec) {
      std::cerr << "Connect: " << ec.message() << std::endl;
      socket_.close();
      return;
    }

    DoWrite();
  }

  void DoWrite() {
    do {
      std::cout << "EnterMessage: ";
      std::cin.getline(cin_buf_, BUF_SIZE-1);
      data_length = std::strlen(cin_buf_);
    } while(data_length == 0);
    std::cin.clear(); //work in large data clear buffer
    total_reply_length = 0;
    if (data_length == 0) {
      return;
    }

    boost::asio::async_write(socket_, boost::asio::buffer(cin_buf_, data_length),
                             std::bind(&Client::OnWrite, this, std::placeholders::_1, std::placeholders::_2));
  }

  void OnWrite(boost::system::error_code ec, std::size_t write_length) {
    if (ec) {
      std::cerr << "Write: " << ec.message() << std::endl;
      return;
    }

    DoRead();
  }

  void DoRead() {
    socket_.async_read_some(boost::asio::buffer(buf_),
                            std::bind(&Client::OnRead, this, std::placeholders::_1, std::placeholders::_2));
  }

  void OnRead(boost::system::error_code ec, std::size_t read_length) {
    if (ec) {
      std::cerr << "Read" << ec.message() << std::endl;
      return;
    }
    std::cout << "recv from server: ";
    std::cout.write(buf_.data(), read_length);
    std::cout << std::endl;
    total_reply_length += read_length;
    if (total_reply_length >= data_length) {
      std::cout << "data_length:" << data_length << ", total_reply_length:" << total_reply_length << std::endl;
      DoWrite();
    } else {
      DoRead();
    }
  }

private:
  tcp::socket socket_;
  tcp::resolver resolver_;

  char cin_buf_[BUF_SIZE];
  int data_length;
  std::array<char, 10> buf_;
  int total_reply_length;
};

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
    return 1;
  }

  const char* host = argv[1];
  const char* port = argv[2];

  boost::asio::io_context ioc;
  Client client(ioc, host, port);

  ioc.run();

  return 0;
}
