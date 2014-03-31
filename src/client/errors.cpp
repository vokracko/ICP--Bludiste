/**
*\file errors.cpp 
* Soubor obsahující implementaci metod třídy Errors
*\author Michal Veselý (xvesel63)
*/

#include "errors.h"

Errors::Errors(int code)
{
	this->code=code;
}

/**\fn std::string Errors::get_message()
*
*\return Chybovou hlášku vyjímky, která byla vyvolána
 */
std::string Errors::get_message()
{
	return error_messages[this->code];
}