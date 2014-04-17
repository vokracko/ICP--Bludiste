/**
*\file game_field.h
* Třída dědící od QGridLayout.<br /> 
* Obsahuje všechny herní komponenty v podobě QPixmap a pole QLabelů do kterých se tyto obrázky komponent zobrazují
*\author Michal Veselý (xvesel63)
*/

#include <QGridLayout>
#include <QLabel>

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

private:
	enum game_components
	{
		RED_UP=41,
		RED_DOWN=43,
		RED_LEFT=42,
		RED_RIGHT=44,

		BLUE_UP=61,
		BLUE_DOWN=63,
		BLUE_LEFT=62,
		BLUE_RIGHT=64,

		WHITE_UP=71,
		WHITE_DOWN=73,
		WHITE_LEFT=72,
		WHITE_RIGHT=74,

		GREEN_UP=51,
		GREEN_DOWN=53,
		GREEN_LEFT=52,
		GREEN_RIGHT=54,

		MONSTER_UP=81,
		MONSTER_DOWN=83,
		MONSTER_LEFT=82,
		MONSTER_RIGHT=84,

		KEY=90,
		WALL=110,
		EMPTY=120,
		GATE_OPEN=105,
		GATE_CLOSE=106,
	};

public:
	Game_field(int height, int width,QWidget *parent=0);
	~Game_field();
public:
	void set_map(char map[50][50]);



};