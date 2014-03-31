#include "server.h"

int main()
{
	boost::asio::io_service ios;
	Server s(ios);
	s.listen();
	ios.run();
}
