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
public:
	QPixmap * empty;
	QPixmap * monster_up;
	QPixmap * wall;
	QPixmap * white_up;
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