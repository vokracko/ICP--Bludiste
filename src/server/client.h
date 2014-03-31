#ifndef _H_CLIENT
#define _H_CLIENT

#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>

class Client
{
	int id;
	// boost::asio::ip::tcp::socket socket;

	public:
		Client();
		~Client();
		void work();
		void send(std::string message);
};

#endif
