class Map;

#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <fstream>
#include <vector>
#include "player.h"

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

		static int count;
		static const std::string path;//TODO před odevzdání změnit složku do rootu
		//TODO umístění hráčů náhodně
		//TODO hlídač

		// TODO výsledek požadované operace (provedena/nelze provést); týká se pouze vlastního hráče
		// TODO kolize hráče s jiným objektem s následným zabitím hráče (týká se všech)

	private:
		int width;
		int height;
		// TODO uchovávat pozici všech hráčů ať se to nemusí hledat

		std::vector<std::string> map;


	public:
		static bool exists(int map_id);
		static std::string list();

		Map(int map_id);
		void set_position();// block * b, x, y, look
		std::vector<std::string> * get_map();
		int get_width();
		int get_height();
		void emplace_player(Player * p);


};
