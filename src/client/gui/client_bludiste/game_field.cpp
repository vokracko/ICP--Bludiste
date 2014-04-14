#include "game_field.h"


Game_field::Game_field(int height,int width,QWidget * parent) : QGridLayout(parent)
{
	this->height=height;
	this->width=width;
	for (int i=0;i<this->height;i++)
		for (int j=0;j<this->width;j++)
			this->field[i][j]=new QLabel();
	this->empty=new QPixmap("./../../../images/none.png");
	this->white_up= new QPixmap("./../../../images/white-up.png");
	this->monster_up=new QPixmap("./../../../images/monster-up.png");
	this->wall=new QPixmap("./../../../images/wall.png");
}

void Game_field::set_map(char map[50][50])
{
	for (int i=0;i<this->height;i++)
		for (int j=0;j<this->width;j++)
		{
			switch (map[i][j])
			{
				case 'w' :
                    this->field[i][j]->setPixmap(*(this->wall));
					break;
				case 'e' :
                    this->field[i][j]->setPixmap(*(this->empty));
					break;
				case 'p' :
                    this->field[i][j]->setPixmap(*(this->white_up));
					break;
				case 'm' :
                    this->field[i][j]->setPixmap(*(this->monster_up));
					break;
				default:
                    this->field[i][j]->setPixmap(*(this->empty));
			};
			
		}
}

Game_field::~Game_field(){}
