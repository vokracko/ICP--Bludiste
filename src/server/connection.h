/**
 * Třída spojení
 * \file connetion.h
 * \author Lukáš Vokráčko (xvokra00)
 */

class Connection;

#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/read_until.hpp>
#include <mutex>
#include <istream>

class Connection
{
	private:
		std::mutex write_mutex;
		std::mutex read_mutex;
		boost::asio::streambuf read_buffer;
		std::string * target;

	public:
		boost::asio::ip::tcp::socket socket;
		enum {SYNC, ASYNC};

	private:
		void handle_receive();
		void handle_send();

	public:
		Connection(boost::asio::io_service & ios);
		~Connection();
		void send(std::string * message);
		void sync_send(std::string * message);
		void receive(std::string * target);
		void sync_receive(std::string * target);
		// boost::asio::ip::tcp::socket get_socket();
};
