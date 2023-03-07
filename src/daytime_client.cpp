//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2019 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try /*tests the following block for errors, if no errors the block runs*/
  {
    if (argc != 2) /*if more or lessthan two cmd line inputs are given, print the statement*/
    {
      std::cerr << "Usage: client <host>" << std::endl; /*prints in error format*/
      return 1;
    } 

    /*Creates an object of class io_context. This provides usage for socket communication*/
    boost::asio::io_context io_context; 

    /*Creates a TCP resolver object, with io_context to resolve hostname and service name*/
    tcp::resolver resolver(io_context); 


    /*The resolve function is used to resolve host and service names into a list of endpoint entries.*/
      /*In this case the list of endpoints, are stored the variable of type results_type called endpoints*/
      /*resolve takes two arguments hostname and servicename*/
      /*hostname is written in commandline, servicename is daytime*/
    tcp::resolver::results_type endpoints =
      resolver.resolve(argv[1], "daytime");
      

    /*Creates a socket variable with the input io_context*/
    /*The socket represents an endpoint for communication between two processes*/
    tcp::socket socket(io_context); 
    boost::asio::connect(socket, endpoints);
    /*Establishes connection bewteen socket and endpoints*/

    while(true)
    {
      /*Creates buffer*/
      boost::array<char, 128> buf;

      /*creates an error code*/
      boost::system::error_code error;

      /*This function is used to read data from the socket. 
      The function call will block until one or more bytes of data 
      has been read successfully, or until an error occurs.*/
      size_t len = socket.read_some(boost::asio::buffer(buf), error);

      if (error == boost::asio::error::eof) //error is empty ie no error
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      /*prints buffer*/
      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}