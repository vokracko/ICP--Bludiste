/**
*\file game_field.cpp
* Soubor obsahující implementaci metod třídy Game_box. <br/>
* Třída obsahuje odkazy na všechny obrázky které může hra vykreslit a hrací pole z komponent QLabel, do které se obrázky vykreslují.

*\author Michal Veselý (xvesel63)
*/

#include "game_field.h"

/**
*\fn Game_field::Game_field(int height,int width,QWidget * parent) : QGridLayout(parent)
* \brief Konstruktor třídy Game_field vytvoří QPixmapy všech herních komponent a maticí Qlabelů, do kterých jsou tyto QPixmapy vykreslovány.
* Konstruktor třídy Game_field dědí od třídy QGridLayout. Instanciuje všechny QPixmapy, do kterých jsou uloženy jednotlivé obrázky (herní kompomenty).
* Konstruktor také vytváří dvourozměrné pole instancí třídy QLabel, do kterých jsou tyto obrázky ukládány.
*/
Game_field::Game_field(int height,int width,QWidget * parent) : QGridLayout(parent)
{
	this->height=height;
	this->width=width;
	for (int i=0;i<this->height;i++)
		for (int j=0;j<this->width;j++)
			this->field[i][j]=new QLabel();


	this->white_up= new QPixmap(IMAGPATH(white-up.png));
	this->white_down= new QPixmap(IMAGPATH(white-down.png));
	this->white_right= new QPixmap(IMAGPATH(white-right.png));
	this->white_left= new QPixmap(IMAGPATH(white-left.png));

	this->red_up= new QPixmap(IMAGPATH(red-up.png));
	this->red_down= new QPixmap(IMAGPATH(red-down.png));
	this->red_right= new QPixmap(IMAGPATH(red-right.png));
	this->red_left= new QPixmap(IMAGPATH(red-left.png));

	this->green_up= new QPixmap(IMAGPATH(green-up.png));
	this->green_down= new QPixmap(IMAGPATH(green-down.png));
	this->green_right= new QPixmap(IMAGPATH(green-right.png));
	this->green_left= new QPixmap(IMAGPATH(green-left.png));

	this->blue_up= new QPixmap(IMAGPATH(blue-up.png));
	this->blue_down= new QPixmap(IMAGPATH(blue-down.png));
	this->blue_right= new QPixmap(IMAGPATH(/blue-right.png));
	this->blue_left= new QPixmap(IMAGPATH(blue-left.png));

	this->monster_up= new QPixmap(IMAGPATH(monster-up.png));
	this->monster_down= new QPixmap(IMAGPATH(monster-down.png));
	this->monster_right= new QPixmap(IMAGPATH(monster-right.png));
	this->monster_left= new QPixmap(IMAGPATH(monster-left.png));

	this->empty=new QPixmap(IMAGPATH(none.png));
	this->wall=new QPixmap(IMAGPATH(wall.png));
	this->key=new QPixmap(IMAGPATH(key.png));
	this->gate_open=new QPixmap(IMAGPATH(gate_open.png));
	this->gate_close=new QPixmap(IMAGPATH(gate_close.png));
}


/**
*\fn void Game_field::set_map(char map[50][50])
* \brief Nastaví příslušné obrázky na každé hrací políčko podle parametru map.
* \param map Aktuální stav (mapa) hry
*/
void Game_field::set_map(char map[50][50])
{
	for (int i=0;i<this->height;i++)
		for (int j=0;j<this->width;j++)
		{
			switch (map[i][j])
			{
				case Box::WALL :
                    this->field[i][j]->setPixmap(*(this->wall));
					break;
				case Box::EMPTY :
                    this->field[i][j]->setPixmap(*(this->empty));
					break;
				case Box::GATE+Box::OPEN :
                    this->field[i][j]->setPixmap(*(this->gate_open));
                    break;
				case Box::GATE+Box::CLOSED :
                    this->field[i][j]->setPixmap(*(this->gate_close));
					break;
				case Box::KEY :
                    this->field[i][j]->setPixmap(*(this->key));
					break;

				case Box::WHITE+Box::UP :
					this->field[i][j]->setPixmap(*(this->white_up));
					break;
				case Box::WHITE+Box::DOWN :
					this->field[i][j]->setPixmap(*(this->white_down));
					break;
				case Box::WHITE+Box::LEFT :
					this->field[i][j]->setPixmap(*(this->white_left));
					break;
				case Box::WHITE+Box::RIGHT :
					this->field[i][j]->setPixmap(*(this->white_right));
					break;

				case Box::BLUE+Box::UP :
					this->field[i][j]->setPixmap(*(this->blue_up));
					break;
				case Box::BLUE+Box::DOWN :
					this->field[i][j]->setPixmap(*(this->blue_down));
					break;
				case Box::BLUE+Box::LEFT :
					this->field[i][j]->setPixmap(*(this->blue_left));
					break;
				case Box::BLUE+Box::RIGHT :
					this->field[i][j]->setPixmap(*(this->blue_right));
					break;

				case Box::RED+Box::UP :
					this->field[i][j]->setPixmap(*(this->red_up));
					break;
				case Box::RED+Box::DOWN :
					this->field[i][j]->setPixmap(*(this->red_down));
					break;
				case Box::RED+Box::LEFT :
					this->field[i][j]->setPixmap(*(this->red_left));
					break;
				case Box::RED+Box::RIGHT :
					this->field[i][j]->setPixmap(*(this->red_right));
					break;

				case Box::GREEN+Box::UP :
					this->field[i][j]->setPixmap(*(this->green_up));
					break;
				case Box::GREEN+Box::DOWN :
					this->field[i][j]->setPixmap(*(this->green_down));
					break;
				case Box::GREEN+Box::LEFT :
					this->field[i][j]->setPixmap(*(this->green_left));
					break;
				case Box::GREEN+Box::RIGHT :
					this->field[i][j]->setPixmap(*(this->green_right));
					break;

				case Box::MONSTER+Box::UP :
					this->field[i][j]->setPixmap(*(this->monster_up));
					break;
				case Box::MONSTER+Box::DOWN :
					this->field[i][j]->setPixmap(*(this->monster_down));
					break;
				case Box::MONSTER+Box::LEFT :
					this->field[i][j]->setPixmap(*(this->monster_left));
					break;
				case Box::MONSTER+Box::RIGHT :
					this->field[i][j]->setPixmap(*(this->monster_right));
					break;

				default:
					this->field[i][j]->setPixmap(*(this->empty));
			};

		}
}

Game_field::~Game_field()
{
    delete white_up;
	delete white_down;
	delete white_right;
	delete white_left;

	delete red_up;
	delete red_down;
	delete red_right;
	delete red_left;

	delete green_up;
	delete green_down;
	delete green_right;
	delete green_left;

	delete blue_up;
	delete blue_down;
	delete blue_right;
	delete blue_left;

	delete monster_up;
	delete monster_down;
	delete monster_right;
	delete monster_left;

	delete empty;
	delete wall;
	delete key;
	delete gate_open;
	delete gate_close;

	for (int i=0;i<this->height;i++)
	for (int j=0;j<this->width;j++)
		delete this->field[i][j];
}
