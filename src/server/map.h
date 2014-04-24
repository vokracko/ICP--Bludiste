class Map;

#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "player.h"
#include "position.h"
#include "../errors.h" // TODO errors přejmenovat !!! a dát do /stc, používáme oba, nezapomenou na makefile

class Map
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
			RIGHT = 2,
			BOTTOM = 3,
			LEFT = 4,
			NONE = 0
		};

		static const std::string path;//TODO před odevzdání změnit složku do rootu
		static std::map<int, std::string> maplist;
		//TODO hlídač

		// TODO kolize hráče s jiným objektem s následným zabitím hráče (týká se všech)

	private:
		int width;
		int height;
		int map_id;

		std::string map;

	public:
		static bool exists(int map_id);
		static std::string list();
		static void init();
		int get(int x, int y);
		void set(int x, int y, int box);


		Map(int map_id);
		std::string * get_map();
		int get_width();
		int get_height();
		void emplace_player(Player * p);
		void unemplace_player(Player * p);
		std::string get_name();

};
