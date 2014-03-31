#ifndef _H_BOX
#define _H_BOX

#include <string>


class Box
{
	public:
		enum
		{
			RED = 10,
			GREEN = 20,
			BLUE = 30,
			WHITE = 40,

			MONSTER = 50,
			KEY = 60,
			GATE = 70,
			WALL = 80,

			TOP = 1,
			LEFT = 2,
			RIGHT = 3,
			BOTTOM = 4,
			NONE = 0
		};


		static std::string get_image(int type, int position = NONE)
		{
			std::string filename;
			switch(type)
			{
				case MONSTER: filename = "monster";break;
				case KEY: filename = "key";break;
				case GATE: filename = "gate";break;
				case WALL: filename = "wall";break;
				case RED: filename = "red";break;
				case GREEN: filename = "green";break;
				case BLUE: filename = "blue";break;
				case WHITE: filename = "white";break;
			}

			switch(position)
			{
				case TOP: filename.append("-top");break;
				case LEFT: filename.append("-left");break;
				case RIGHT: filename.append("-right");break;
				case Box::BOTTOM: filename.append("-bottom");break;
			}

			return filename.append(".png");
		}
};

#endif
