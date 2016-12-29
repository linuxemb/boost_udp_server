/*
 * udpserverobj.h
 *
 *  Created on: Feb 5, 2015
 *      Author: lisa
 */

#ifndef UDPSERVEROBJ_H_
#define UDPSERVEROBJ_H_

#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#define BUFFER_SIZE_MAX	512
using boost::asio::ip::udp;

class udpserverobj: private boost::noncopyable
{
public:

	udpserverobj()
		:m_io() { 	}

	virtual ~udpserverobj();

	boost::asio::io_service m_io; ///< Io service object

	size_t m_writeBufferSize; ///< Size of writeBuffer

	udp::socket socket_;
	udp::endpoint remote_endpoint_;
	//   boost::array<char, 1> recv_buffer_;
	size_t bytes_transfered;
	char recv_buffer_[BUFFER_SIZE_MAX];

	//   boost::shared_ptr<udpserverobj> psp;

};

//-------------------------------------------

class udpserverdai: private boost::noncopyable
{
public:

	udpserverdai(): psp(new udpserverobj) {}

private:
    boost::shared_ptr<udpserverobj> psp;


};

#endif /* UDPSERVEROBJ_H_ */

