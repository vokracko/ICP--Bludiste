/**
*\file errors.h
* Obsahuje implementaci hlavičky třídy Errors
*\author Michal Veselý (xvesel63)
*/

#pragma once

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

public:
	/**Enumerátor chybových kódů */
	enum error_codes
	{
		SOCKET_CONNECT,
		TIMEOUT,
		WRITE_SOCKET,
		SOCKET_READ,
		GAME_NOT_CREATED,
		NOT_JOINED,
		UNKNOWN_COMMAND,
		OUT_OF_RANGE,
		FORK
	};

	/**Pole chybových hlášek */
	std::string error_messages[12]=
	{
		"Nepodařilo se připojit k serveru",
		"Nepovolený časový interval změn (nutno zadat 0.5 - 5 sekund)",
		"Nepodařilo se odeslat data serveru",
		"Nepodařilo se přijmout data od serveru",
		"Hru nebylo možné vytvořit",
		"Nepodařilo se vás připojit do hry",
		"Neznámý příkaz pro tah",
		"Pozice je mimo mapu",
		"Nepovedlo se duplikovat proces pro čtení"
	};
public:
	Errors(int code);

	std::string get_message();
};
