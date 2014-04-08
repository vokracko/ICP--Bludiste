#include "server.h"

void stopRun(int sig)
{
	std::cout << "stoprun" << std::endl;
}

int main()
{
	signal(SIGINT, Server::kill);
	boost::shared_ptr<boost::asio::io_service> ios(new boost::asio::io_service());
	Server * server;

	Server::create(ios.get());
	server = Server::get_instance();

	server->listen();
	ios.get()->run();

	// delete server;
}
