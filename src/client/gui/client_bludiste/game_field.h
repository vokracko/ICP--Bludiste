/**
*\file game_field.h
* Třída dědící od QGridLayout.<br /> 
* Obsahuje všechny herní komponenty v podobě QPixmap a pole QLabelů do kterých se tyto obrázky komponent zobrazují
*\author Michal Veselý (xvesel63)
*/
#pragma once

#include <QGridLayout>
#include <QLabel>
#include "./../../../game_components.h"

/**
\class Game_field
* Obsahuje všechny možné obrázky uložené v QPixmap, zobrazitelné na hrací ploše (hráče s natočením, hlídače s natočením, zeď, klíč, bránu). <br/>
* Obsahuje hrací plochu jako dvourozměrnou matici instancí třídy QLabel, na které se vykreslují příslušné obrázky uložené v instanci QPixmap.
*/
class Game_field : public QGridLayout
{
private:
	QPixmap * white_up;
	QPixmap * white_down;
	QPixmap * white_right;
	QPixmap * white_left;

	QPixmap * red_up;
	QPixmap * red_down;
	QPixmap * red_right;
	QPixmap * red_left;

	QPixmap * green_up;
	QPixmap * green_down;
	QPixmap * green_right;
	QPixmap * green_left;

	QPixmap * blue_up;
	QPixmap * blue_down;
	QPixmap * blue_right;
	QPixmap * blue_left;

	QPixmap * monster_up;
	QPixmap * monster_down;
	QPixmap * monster_right;
	QPixmap * monster_left;

	QPixmap * empty;
	QPixmap * wall;
	QPixmap * key;
	QPixmap * gate_open;
	QPixmap * gate_close;

public:
	QLabel * field[50][50];
	int height;
	int width;

public:
	Game_field(int height, int width,QWidget *parent=0);
	~Game_field();
public:
	void set_map(char map[50][50]);



};