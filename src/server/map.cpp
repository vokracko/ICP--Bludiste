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
	// TODO můžná budou potřeba semafory'dokud se mapy nepodaří odeslat
	return &map;
}

void Map::open_gate()
{
	//TODO vyměnit obrázky
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

	for(int y = 0; y < height; ++y)
		for(int x = 0; x < width; ++x)
		{
			//TODO nějak vyřešit náhodnost
			if(get(x, y) == Box::EMPTY)
			{
				pos.x = x;
				pos.y = y;
				p->set_position(pos);

				return;
			}
		}
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
