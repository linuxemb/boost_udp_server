/*
 * UDP_ASYN_Server.h
 *  this is the collection
 *  Created on: Feb 4, 2015
 *      Author: lisa
 */

#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/shared_array.hpp>

using namespace std;
using boost::asio::ip::udp;
class udp_server;
class udp_server
{
public:
  udp_server(boost::asio::io_service& io_service)
    : socket_(io_service, udp::endpoint(udp::v4(), 13))

  {
	   psp = new udp_server(io_service);
    start_receive();
  }

public:
void setReadCallback(const  boost::function<void (const char*, size_t)>& callback);

private:

static const int m_readBufferSize=512;
boost::shared_ptr<udp_server> psp; //guaranteds that it wont be deallocated until last reference expires

void start_receive();
void handle_receive(const boost::system::error_code& error, std::size_t /*bytes_transferred*/);

void handle_send(boost::shared_ptr<std::string> /*message*/, const boost::system::error_code& /*error*/, std::size_t /*bytes_transferred*/);

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
 //   boost::array<char, 1> recv_buffer_;
    size_t bytes_transfered;
    char recv_buffer_ [1024];
//char* recv_buffer_;
  boost::function<void(const char*, size_t)> m_callback;

  };


// set a read callback*/

void setReadCallback(const boost::function<void (const char*, size_t)>& callback);


