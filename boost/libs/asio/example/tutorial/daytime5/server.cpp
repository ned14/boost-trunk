#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try
  {
    boost::asio::io_service io_service;

    udp::socket socket(io_service, udp::endpoint(udp::v4(), 13));

    for (;;)
    {
      boost::array<char, 1> recv_buf;
      udp::endpoint remote_endpoint;
      boost::asio::error error;
      socket.receive_from(boost::asio::buffer(recv_buf),
          remote_endpoint, 0, boost::asio::assign_error(error));

      if (error && error != boost::asio::error::message_size)
        throw error;

      std::string message = make_daytime_string();

      socket.send_to(boost::asio::buffer(message),
          remote_endpoint, 0, boost::asio::ignore_error());
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
