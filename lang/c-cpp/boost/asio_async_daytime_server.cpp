#include <iostream>

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/write.hpp>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

class tcp_connection: public std::enable_shared_from_this<tcp_connection> {
public:
  using pointer = std::shared_ptr<tcp_connection>;

  static pointer create(boost::asio::io_context& ioc) {
    return pointer(new tcp_connection(ioc));
  }

  tcp::socket& socket() {
    return socket_;
  }

  void start() {
    message_ = make_daytime_string();
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
                       std::bind(&tcp_connection::handle_write, shared_from_this(),
                                 std::placeholders::_1, std::placeholders::_2));
  }

private:
  tcp_connection(boost::asio::io_context& ioc) :socket_(ioc) {}

  void handle_write(const boost::system::error_code& ec, std::size_t length) {
  }

  tcp::socket socket_;
  std::string message_;
};

class tcp_server {
public:
  tcp_server(boost::asio::io_context& ioc, std::uint16_t port)
    : acceptor_(ioc, tcp::endpoint(tcp::v4(), port)){
    start_accept();
  }
private:
  void start_accept() {
    auto connection = tcp_connection::create(acceptor_.get_executor().context());

    acceptor_.async_accept(connection->socket(),
                           std::bind(&tcp_server::handle_accept, this,
                                     std::placeholders::_1, connection));
  }

  void handle_accept(const boost::system::error_code& ec, const tcp_connection::pointer connection) {
    if (ec) {
      std::cerr << "handle_accept: " << ec.message() << std::endl;
    } else {
      connection->start();
    }
    start_accept();
  }

  tcp::acceptor acceptor_;
};


int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
    return 1;
  }

  try {
    std::uint16_t port = std::atoi(argv[1]);
    boost::asio::io_context ioc;
    tcp_server server(ioc, port);

    ioc.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
