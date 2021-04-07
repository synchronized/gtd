#include <iostream>

#define BOOST_ASIO_NO_DEPRECATED
#include <boost/system/error_code.hpp>
#include <boost/timer/timer.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/deadline_timer.hpp>

void Print(boost::system::error_code ec) {
  std::cout << "Hello, world!" << std::endl;
}

void Print2(boost::system::error_code ec, boost::asio::deadline_timer* timer, int* count) {
  if (*count < 3) {
    std::cout << "Print2: " << *count << std::endl;
    ++(*count);

    timer->expires_at(timer->expires_at() + boost::posix_time::seconds(1));
    timer->async_wait(std::bind(&Print2, std::placeholders::_1, timer, count));
  }
}

class Printer {
public:
  Printer(boost::asio::deadline_timer &timer): mTimer(timer) {}

  void Print(boost::system::error_code ec) {
    if (count < 3) {
      std::cout << "Printer::Print: " << count << std::endl;
      ++(count);

      mTimer.expires_at(mTimer.expires_at() + boost::posix_time::seconds(1));
      mTimer.async_wait(std::bind(&Printer::Print, this, std::placeholders::_1));
    }
  }

  void operator() (boost::system::error_code ec) {
    this->Print(ec);
  }
private:
  boost::asio::deadline_timer & mTimer; //this line remove default ctor, It's can't copy
  int count;
};

int main() {
  boost::asio::io_context ioc;
  boost::asio::deadline_timer timer(ioc, boost::posix_time::seconds(3));
  boost::asio::deadline_timer timer2(ioc, boost::posix_time::seconds(3));
  Printer printer(timer2);
  std::function<void(boost::system::error_code)> fprinter = std::bind(&Printer::Print, &printer, std::placeholders::_1);
  timer.async_wait(&Print);
  int count = 0;
  timer.async_wait(std::bind(&Print2, std::placeholders::_1, &timer, &count));
  timer.async_wait(fprinter);
  ioc.run();
  return 0;
}
