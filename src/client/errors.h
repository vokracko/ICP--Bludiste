#pragma once
/**
*\file errors.h
* Obsahuje implementaci hlavičky třídy Errors
*\author Michal Veselý (xvesel63)
*/

#include <iostream>
#include <string>

/**
\class Errors
* Třída je potomkem třídy exception, kterou rozšiřuje o nové výjimky, které mohou vzniknout v průběhu aplikace bludiště
*/
class Errors: public std::exception
{
public:
	int code;
	/**Enumerátor chybových kódů */
	enum error_codes 
	{
		SOCKET_CONNECT,
		PARAM_ERROR,
		BOXES_WIDTH,
		BOXES_HEIGHT,
		TIMEOUT,
		WRITE_SOCKET,
		SOCKET_READ,
		GAME_NOT_CREATED,
		NOT_JOINED,
	};

	/**Pole chybových hlášek */
	std::string error_messages[9]=
	{
		"Nepodařilo se připojit k serveru",
		"Nebyl zadán správně parametr",
		"Špatná šířka hracího pole (nutno zadat 20 - 50)",
		"Špatná výška hracího pole (nutno zadat 20 - 50)",
		"Nepovolený časový interval změn (nutno zadat 0.5 - 5 sekund)",
		"Nepodařilo se odeslat data serveru",	
		"Nepodařilo se přijmout data od serveru",
		"Hru nebylo možné vytvořit, zkontrolujte, že jste serveru poslal správné informace",
		"Nepodařilo se vás připojit do hry",
	};
public:
	Errors(int code);
	
	std::string get_message();
};