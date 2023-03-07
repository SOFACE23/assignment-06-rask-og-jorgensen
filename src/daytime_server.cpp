//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

/*function that creates a string of the current date and time*/
std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
  try /*tests the following block for errors, if no errors the block runs*/
  {
    /*Creates an object of class io_context. This provides usage for socket communication*/
    boost::asio::io_context io_context;

    /*Creates acceptor object that listens for incoming connections on a 
    specified endpoint address*/
    /*Uses the IPv4 protocol and uses port 13 which is used for daytime protocol
    which returns current date and time when connection is established*/
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    while (true)
    {
      /*creates socket*/ 
      tcp::socket socket(io_context);

      /*This function is used to accept a new connection from a peer into the 
      given socket. The function call will block until a new connection has 
      been accepted successfully or an error occurs.*/
      acceptor.accept(socket);

      /*Invokes method from earlier*/
      std::string message = make_daytime_string();

      /*creates erroe code for potential error*/
      boost::system::error_code ignored_error;

      /*server writes data to client*/
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}