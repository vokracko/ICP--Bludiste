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

		static const std::string path;//TODO před odevzdání změnit složku do rootu
		static std::map<int, std::string> maplist;
		// TODO kolize hráče s jiným objektem s následným zabitím hráče (týká se všech)

	private:
		int width;
		int height;
		int map_id;

		std::string map;
		unsigned char ** ghost_objects;

	public:
		static bool exists(int map_id);
		static std::string list();
		static void init();
		int get(int x, int y);
		void set(int x, int y, int box);


		void set_ghost(int x, int y, unsigned char obj);
		unsigned char get_ghost(int x, int y);
		Map(int map_id);
		~Map();
		std::string * get_map();
		int get_width();
		int get_height();
		void emplace_player(Player * p);
		void unemplace_player(Player * p);
		std::string get_name();

};
