/**
*\file game_field.cpp
* Soubor obsahující implementaci metod třídy Game_box. <br/>
* Třída obsahuje odkazy na všechny obrázky které může hra vykreslit a hrací pole z komponent QLabel, do které se obrázky vykreslují.

*\author Michal Veselý (xvesel63)
*/

#include "game_field.h"

/**
*\fn Game_field::Game_field(int height,int width,QWidget * parent) : QGridLayout(parent)
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

	this->white_up= new QPixmap("./../../../images/white-up.png");
	this->white_down= new QPixmap("./../../../images/white-down.png");
	this->white_right= new QPixmap("./../../../images/white-right.png");
	this->white_left= new QPixmap("./../../../images/white-left.png");

	this->red_up= new QPixmap("./../../../images/red-up.png");
	this->red_down= new QPixmap("./../../../images/red-down.png");
	this->red_right= new QPixmap("./../../../images/red-right.png");
	this->red_left= new QPixmap("./../../../images/red-left.png");

	this->green_up= new QPixmap("./../../../images/green-up.png");
	this->green_down= new QPixmap("./../../../images/green-down.png");
	this->green_right= new QPixmap("./../../../images/green-right.png");
	this->green_left= new QPixmap("./../../../images/green-left.png");

	this->blue_up= new QPixmap("./../../../images/blue-up.png");
	this->blue_down= new QPixmap("./../../../images/blue-down.png");
	this->blue_right= new QPixmap("./../../../images/blue-right.png");
	this->blue_left= new QPixmap("./../../../images/blue-left.png");

	this->monster_up= new QPixmap("./../../../images/monster-up.png");
	this->monster_down= new QPixmap("./../../../images/monster-down.png");
	this->monster_right= new QPixmap("./../../../images/monster-right.png");
	this->monster_left= new QPixmap("./../../../images/monster-left.png");

	this->empty=new QPixmap("./../../../images/none.png");
	this->wall=new QPixmap("./../../../images/wall.png");
	this->key=new QPixmap("./../../../images/key.png");
	this->gate_open=new QPixmap("./../../../images/gate_open.png");
	this->gate_close=new QPixmap("./../../../images/gate_close.png");
}


/**
*\fn void Game_field::set_map(char map[50][50])
* Nastaví příslušné obrázky na každé hrací políčko podle parametru map.
* \param map Aktuální stav (mapa) hry
*/
void Game_field::set_map(char map[50][50])
{
	for (int i=0;i<this->height;i++)
		for (int j=0;j<this->width;j++)
		{
			switch (map[i][j])
			{
				case WALL :
                    this->field[i][j]->setPixmap(*(this->wall));
					break;
				case EMPTY :
                    this->field[i][j]->setPixmap(*(this->empty));
					break;
				case GATE_OPEN :
                    this->field[i][j]->setPixmap(*(this->gate_open));
                    break;
				case GATE_CLOSE :
                    this->field[i][j]->setPixmap(*(this->gate_close));
					break;
				case KEY :
                    this->field[i][j]->setPixmap(*(this->key));
					break;
				
				case WHITE_UP :
					this->field[i][j]->setPixmap(*(this->white_up));
					break;
				case WHITE_DOWN :
					this->field[i][j]->setPixmap(*(this->white_down));
					break;
				case WHITE_LEFT :
					this->field[i][j]->setPixmap(*(this->white_left));
					break;
				case WHITE_RIGHT :
					this->field[i][j]->setPixmap(*(this->white_right));
					break;

				case BLUE_UP :
					this->field[i][j]->setPixmap(*(this->blue_up));
					break;
				case BLUE_DOWN :
					this->field[i][j]->setPixmap(*(this->blue_down));
					break;
				case BLUE_LEFT :
					this->field[i][j]->setPixmap(*(this->blue_left));
					break;
				case BLUE_RIGHT :
					this->field[i][j]->setPixmap(*(this->blue_right));
					break;

				case RED_UP :
					this->field[i][j]->setPixmap(*(this->red_up));
					break;
				case RED_DOWN :
					this->field[i][j]->setPixmap(*(this->red_down));
					break;
				case RED_LEFT :
					this->field[i][j]->setPixmap(*(this->red_left));
					break;
				case RED_RIGHT :
					this->field[i][j]->setPixmap(*(this->red_right));
					break;

				case GREEN_UP :
					this->field[i][j]->setPixmap(*(this->green_up));
					break;
				case GREEN_DOWN :
					this->field[i][j]->setPixmap(*(this->green_down));
					break;
				case GREEN_LEFT :
					this->field[i][j]->setPixmap(*(this->green_left));
					break;
				case GREEN_RIGHT :
					this->field[i][j]->setPixmap(*(this->green_right));
					break;

				case MONSTER_UP :
					this->field[i][j]->setPixmap(*(this->monster_up));
					break;
				case MONSTER_DOWN :
					this->field[i][j]->setPixmap(*(this->monster_down));
					break;
				case MONSTER_LEFT :
					this->field[i][j]->setPixmap(*(this->monster_left));
					break;
				case MONSTER_RIGHT :
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
