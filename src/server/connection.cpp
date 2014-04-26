/**
 * \file connection.cpp
 * \author Lukáš Vokráčko (xvokra00)
*/

#include "connection.h"

 /**
  * \fn Connection::Connection(boost::asio::io_service & ios): socket(ios)
  * \brief Vytvoří třídu připojení a komikační soket
  * \param[in] ios reference na boost::io_service
 */
Connection::Connection(boost::asio::io_service & ios): socket(ios)
{
	std::cout << "conn++" << std::endl;
}

/**
 * \brief Zavře komunikační soket
 * \fn Connection::~Connection()
*/
Connection::~Connection()
{
	socket.close();
	std::cout << "conn--" << std::endl;

}

/**
 * \fn void Connection::sync_send(std::string * message)
 * \brief Synchronně odešle zprávu
 * \param[in] message zpráva, jež se má odeslat
*/
void Connection::sync_send(std::string * message)
{
	boost::asio::write(
		socket,
		boost::asio::buffer(*message),
		boost::asio::transfer_all()
	);
}

/**
 * \fn void Connection::sync_receive(std::string * target)
 * \brief Synchronně přijme zprávu, jako ukončovací znak bere nový řádek
 * \param[out] target ukazatel na místo, kam se má uložit přijatá zpráva
*/
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

/**
 * \fn void Connection::send(std::string * message)
 * \brief Asynchronně odešle zprávu
 * \param[in] message zpráva, jež se má odeslat
*/
void Connection::send(std::string * message)
{
	write_mutex.lock();
	boost::asio::async_write(
		socket,
		boost::asio::buffer(*message),
		boost::bind(&Connection::handle_send, this)
	);
}

/**
 * \fn void Connection::receive(std::string * target)
 * \brief Asynchronně přijme zprávu
 * \param[out] target ukazatel na místo, kam se má uložit přijatá zpráva
*/
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

/**
 * \fn void Connection::handle_send()
 * \see Connection::send()
 * Uvolní semafor po odeslání asynchronní zprávy
*/
void Connection::handle_send()
{
	write_mutex.unlock();
}

/**
 * \fn void Connection::handle_receive()
 * \see Connection::receive()
 * \brief Uvolní semafor po přijetí asynchronní zprávy
*/
void Connection::handle_receive()
{
	target->assign(boost::asio::buffer_cast<const char*>(read_buffer.data()));
	read_mutex.unlock();
}
