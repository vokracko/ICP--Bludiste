#include "server.h"

int main()
{
	boost::asio::io_service * ios = new boost::asio::io_service;
	boost::shared_ptr<Server> server;

	Server::create(ios);
	server = Server::get_instance();

	server->listen();
	ios->run();

	server.reset();
	delete ios;
}
