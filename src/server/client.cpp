#include "client.h"

Client::Client()
{
	// připojení ke klientovy
	// socket.connect(endpoint);
	// socket.write("bullshit");
}

Client::~Client()
{

}

void Client::work()
{
	// připojit se ke hře
	// vytvořit novou hru ..

	//g = get_game(gid)
	//if(g.add_client(this->id)) ? OK : full

	// v cyklu přijímat zprávu
	// pokud přijmu tak zavolám objekt hry pokud jde o zprávu pro hru
	// a předám mu všechny informace co jsem přijal
	// aby je přeposlal
	// jinak zprávu obsloužím sám
}

void Client::send(std::string message)
{
	//pošli zprávu klientovy
}
