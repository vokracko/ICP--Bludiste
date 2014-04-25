#include "connection.h"

Connection::Connection(boost::asio::io_service & ios): socket(ios)
{
	std::cout << "conn++" << std::endl;
}

Connection::~Connection()
{
	socket.close();
	std::cout << "conn--" << std::endl;

}

void Connection::sync_send(std::string * message)
{
	boost::asio::write(
		socket,
		boost::asio::buffer(*message),
		boost::asio::transfer_all()
	);
}

void Connection::sync_receive(std::string * target)
{
	boost::asio::read_until(
		socket,
		read_buffer,
		'\n'
	);

	std::istream read_stream(&read_buffer);
	std::getline(read_stream, *target);
	target->erase(target->end()-1, target->end());
	read_buffer.consume(read_buffer.size());
}

void Connection::send(std::string * message)
{
	write_mutex.lock();
	boost::asio::async_write(
		socket,
		boost::asio::buffer(*message),
		boost::bind(&Connection::handle_send, this)
	);
}

void Connection::handle_send()
{
	write_mutex.unlock();
}

void Connection::receive(std::string * target)
{
	this->target = target;
	read_mutex.lock();
	boost::asio::async_read_until(
		socket,
		read_buffer,
		'\n',
		boost::bind(&Connection::handle_receive, this)
	);
}

void Connection::handle_receive()
{
	target->assign(boost::asio::buffer_cast<const char*>(read_buffer.data()));
	read_mutex.unlock();


}
