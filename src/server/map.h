/**
 * \brief Třída mapy
 * \file map.h
 * \author Lukáš Vokráčko (xvokra00)
 */

class Map;

#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "player.h"
#include "dirent.h"
#include "position.h"
#include "../errors.h"

class Map
{
	public:

		static const std::string path;//TODO před odevzdání změnit složku do rootu
		static std::map<int, std::string> maplist;

	private:
		int width;
		int height;
		int map_id;

		unsigned char ** ghost_objects;
		std::string map;

	public:
		static bool exists(int map_id);
		static std::string list();
		static void init();

		Map(int map_id);
		~Map();

		int get(int x, int y);
		void set(int x, int y, int obj);
		void set_ghost(int x, int y, unsigned char obj);
		unsigned char get_ghost(int x, int y);


		std::string * get_map();
		std::string get_name();
		int get_width();
		int get_height();
		void emplace_player(Player * p);
		void unemplace_player(Player * p);
};
