/**
*\file bludiste2014_cli.cpp
*Obsahuje funkci main, demonstruje klienta pro konzolovou verzi bludiště
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"
#include <QCoreApplication>
#include <iostream>
#include "errors.h"

int main (int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	try
	{
		if (argc!=2) 
		{
			throw Errors(Errors::PARAM_ERROR);
		}
	}
	catch (Errors & e)
	{
		std::cerr << e.get_message()<<std::endl;
		exit(1);
	}
	
	Client_cli client;  
	try
	{
		client.connect_socket(argv[1]); 	
	}
	catch (Errors & e)
	{
		std::cerr<<e.get_message()<<std::endl;
		exit(1);	
	}
	

	return 0;
}