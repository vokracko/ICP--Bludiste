/**
 * \file map.cpp
 * \author Lukáš Vokráčko (xvokra00)
*/

#include "map.h"

const std::string Map::path = "./maps/";
std::map<int, std::string> Map::maplist;

/**
 * \fn Map::Map(int map_id)
 * \brief Vytvoří a načte mapu, alokuje pole překrytých objektů mapy
 * \param[in] map_id identifikátory mapy
*/
Map::Map(int map_id)
{
	std::ifstream file;
	std::string line;
	size_t pos;
	this->map_id = map_id;


	file.open(Map::path + Map::maplist[map_id]);

	std::getline(file, line);
	height = std::stoi(line, &pos);
	line = line.substr(pos+1);
	width = std::stoi(line);

	while(file.good() && !file.eof())
	{
		std::getline(file, line);
		map.append(line);
	}

	file.close();

	ghost_objects = new unsigned char*[height];

	for(int i = 0; i < height; ++i)
	{
		ghost_objects[i] = new unsigned char[width];
		memset(ghost_objects[i], 0, width);
	}
}

/**
 * \fn Map::~Map()
 * \brief Smaže pole překrytých objektů mapy
*/
Map::~Map()
{
	for(int i = 0; i < height; ++i)
	{
		 delete[] ghost_objects[i];
	}

	delete[] ghost_objects;
}

/**
 * \fn void Map::set_ghost(int x, int y, unsigned char obj)
 * \brief Nastaví prvek jako překrytý
 * \param[in] x souřadnice X
 * \param[in] y souřadnice Y
 * \param[in] obj objekt, jež je překryt
*/
void Map::set_ghost(int x, int y, unsigned char obj)
{
	ghost_objects[y][x] = obj;
}

/**
 * \fn unsigned char Map::get_ghost(int x, int y)
 * \param[in] x souřadnice X
 * \param[in] y souřadnice Y
 * \return objekt, jež je překryt
*/
unsigned char Map::get_ghost(int x, int y)
{
	return ghost_objects[y][x];
}



/**
 * \fn int Map::get(int x, int y)
 * \param[in] x souřadnice X
 * \param[in] y souřadnice Y
 * \return objekt na pozicích určených x a y
*/
int Map::get(int x, int y)
{
	if(x < 0 || x >= width) throw Errors(Errors::OUT_OF_RANGE);
	return map.at(y*width+x);
}

/**
 * \fn void Map::set(int x, int y, int obj)
 * \param[in] x souřadnice X
 * \param[in] y souřadnice Y
 * \param[in] obj objekt, jež má být na souřadnicích x a y
*/
void Map::set(int x, int y, int obj)
{
	if(x < 0 || x >= width) throw Errors(Errors::OUT_OF_RANGE);
	map.at(y*width+x) = obj;
}

/**
 * \fn std::string Map::get_name()
 * \retun název mapy
*/
std::string Map::get_name()
{
	return Map::maplist[map_id];
}

/**
 * \fn void Map::init()
 * \brief Vytvoří seznam dostupných map
*/
void Map::init()
{
	boost::filesystem::path p(Map::path.c_str());
	boost::filesystem::directory_iterator it(p), end;
	int i = 1;

	for(; it != end; ++it, ++i)
	{
		Map::maplist.insert(std::pair<int, std::string>(i, it->path().filename().string()));
	}
}

/**
 * \fn std::string * Map::get_map()
 * \return map
*/
std::string * Map::get_map()
{
	return &map;
}

/**
 * \fn int Map::get_width()
 * \return width
*/
int Map::get_width()
{
	return width;
}

/**
 * \fn int Map::get_height()
 * \return height
*/
int Map::get_height()
{
	return height;
}

/**
 * \fn void Map::emplace_player(Player * p)
 * \brief Umístí hráče do bludiště
 * \param[in] p ukazatel na umisťovaného hráče
*/
void Map::emplace_player(Player * p)
{
	Position pos;

	do
	{
		pos.x = rand() % get_width();
		pos.y = rand() % get_height();
	} while(get(pos.x, pos.y) != Box::EMPTY);

	pos.look = rand() % 4 + 1;
	p->set_position(pos);
	set(pos.x, pos.y, p->get_color() + pos.look);
}

/**
 * void Map::unemplace_player(Player * p)
 * \brief Odebere hráče z mapy
 * \param[in] p ukazatel na umisťovaného hráče
*/
void Map::unemplace_player(Player * p)
{
	Position pos = p->get_position();
	unsigned char ghost = get_ghost(pos.x, pos.y);
	set(pos.x, pos.y, ghost ? ghost : Box::EMPTY);
}

/**
 * \fn std::string Map::list()
 * \brief Vrátí seznam dostupných map
 * \return list seznam map
*/
std::string Map::list()
{
	std::string list = "";

	for(std::map<int, std::string>::iterator it = Map::maplist.begin(); it != Map::maplist.end(); ++it)
	{
		list.append(std::to_string(it->first) + ": " + it->second + "\r\n");
	}


	return list;
}

/**
 * \fn bool Map::exists(int map_id)
 * \brief Kontroluje, zda existuje mapa s daným identifikátorem
 * \param[in] map_id identifikátory mapy
 * \return existence mapy
*/
bool Map::exists(int map_id)
{
	return map_id >= 1 && map_id <= Map::maplist.size();
}
