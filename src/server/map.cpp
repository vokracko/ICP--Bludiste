#include "map.h"

const std::string Map::path = "../../maps/";
std::map<int, std::string> Map::maplist;

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

void Map::set_ghost(int x, int y, unsigned char obj)
{
	ghost_objects[y][x] = obj;
}

unsigned char Map::get_ghost(int x, int y)
{
	return ghost_objects[y][x];
}

Map::~Map()
{
	for(int i = 0; i < height; ++i)
	{
		 delete[] ghost_objects[i];
	}

	delete[] ghost_objects;
}

int Map::get(int x, int y)
{
	if(x < 0 || x >= width) throw Errors(Errors::OUT_OF_RANGE);
	return map.at(y*width+x);
}

void Map::set(int x, int y, int box)
{
	if(x < 0 || x >= width) throw Errors(Errors::OUT_OF_RANGE);
	map.at(y*width+x) = box;
}

std::string Map::get_name()
{
	return Map::maplist[map_id];
}

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

std::string * Map::get_map()
{
	return &map;
}

int Map::get_width()
{
	return width;
}

int Map::get_height()
{
	return height;
}

void Map::emplace_player(Player * p)
{
	Position pos;
	int x, y, x_end, y_end, x_start;

	if(p->get_color() > Box::GREEN)
	{
		y = height/2;
		y_end = height;
	}
	else
	{
		y = 0;
		y_end = height/2;
	}

	if((p->get_color()/10) % 2 == 0)
	{
		x_start = width/2;
		x_end = width;
	}
	else
	{
		x_start = 0;
		x_end = width/2;
	}


	for(; y < y_end; ++y)
		for(x = x_start; x < x_end; ++x)
		{
			if(get(x, y) == Box::EMPTY)
			{
				pos.x = x;
				pos.y = y;
				pos.look = rand()%4+1;
				p->set_position(pos);
				set(x, y, p->get_color() + pos.look);

				return;
			}
		}
}

void Map::unemplace_player(Player * p)
{
	Position pos = p->get_position();
	set(pos.x, pos.y, Box::EMPTY);
}

std::string Map::list()
{
	std::string list = "";

	for(std::map<int, std::string>::iterator it = Map::maplist.begin(); it != Map::maplist.end(); ++it)
	{
		list.append(std::to_string(it->first) + ": " + it->second + "\r\n");
	}


	return list;
}

bool Map::exists(int map_id)
{
	return map_id >= 1 && map_id <= Map::maplist.size();
}
