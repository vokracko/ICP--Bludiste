#include "server.h"

int main()
{
	signal(SIGINT, Server::kill);
	boost::shared_ptr<boost::asio::io_service> ios(new boost::asio::io_service());
	Server * server;

	try
	{
		Server::create(ios.get());
		server = Server::get_instance();

		server->listen();
		ios.get()->run();
	}
	catch(Errors & e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch(std::exception & e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
