/*
 * UDP_ASYN_Server.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: lisa
 */

//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2014 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "udp_server.h"
#include "usbserverobj.h"
using namespace std;
using boost::asio::ip::udp;

std::string make_daytime_string() {
	using namespace std;
	// For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

void udp_server::setReadCallback(const boost::function<void(const char*, size_t)>& callback)
{
	psp->m_callback = callback;
}

void udp_server::start_receive() {
	std::cout << "start _recieve" << std::endl;
	socket_.async_receive_from(boost::asio::buffer(recv_buffer_),
			remote_endpoint_,
			boost::bind(&udp_server::handle_receive, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}

void udp_server::handle_receive(const boost::system::error_code& error,
		std::size_t /*bytes_transferred*/) {
	//if (!error || error == boost::asio::error::message_size)
	{

		std::cout << "received message = " << recv_buffer_ << std::endl;

		if (psp->m_callback)
			psp->m_callback(psp->recv_buffer_, bytes_transfered);

//      boost::shared_ptr<std::string> message(
//          new std::string(make_daytime_string()));
//
//      socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
//          boost::bind(&udp_server::handle_send, this, message,
//            boost::asio::placeholders::error,
//            boost::asio::placeholders::bytes_transferred));
//
//      start_receive();
	}
}

void udp_server::handle_send(boost::shared_ptr<std::string> /*message*/,
		const boost::system::error_code& /*error*/,
		std::size_t /*bytes_transferred*/) {
}

//==============================test UDP=====

class receiver {
public:

	void rcvd(const char *data, unsigned int len) {
		string s(data, len);
		cout << "Call back called \"" << s << "\"" << endl;
	}

};

int main() {

	try {
		boost::asio::io_service io_service;
		udp_server udp_server(io_service);
		receiver client;
		udp_server.setReadCallback(boost::bind(&receiver::rcvd, client, _1, _2));

		io_service.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

