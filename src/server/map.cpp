#include "map.h"

const std::string Map::path = "../../maps/";
int Map::count = 0;

Map::Map(int map_id)
{
	boost::filesystem::path p(Map::path.c_str());
	boost::filesystem::directory_iterator it(p), end;

	std::ifstream file;
	std::string line;
	size_t pos;
	int i = 1;

	std::cout << "Vytvářím mapu ve hře" << std::endl;
	for(; it != end; ++it, ++i)
	{
		if(i == map_id)
		{
			file.open(Map::path + it->path().filename().string());

			std::getline(file, line);
			height = std::stoi(line, &pos);
			line.substr(pos+1);
			width = std::stoi(line);

			while(file.good() && !file.eof())
			{
				std::getline(file, line);
				map.push_back(line);
			}

			file.close();

			break;
		}
	}

}

std::vector<std::string> * Map::get_map()
{
	// TODO můžná budou potřeba semafory'dokud se mapy nepodaří odeslat
	return &map;
}


void Map::set_position()
{
// block * b, x, y, look
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

	for(int y = 0; y < map.size(); ++y)
		for(int x = 0; x < map.at(y).length(); ++x)
		{
			if(map.at(y).at(x) == 'p')
			{
				//TODO nějak vyřešit identifikaci hráče
				pos.x = x;
				pos.y = y;
				p->set_position(pos);
				return;
			}
		}
}

std::string Map::list()
{
	int i = 1;
	std::string list = "";
	boost::filesystem::path p(Map::path.c_str());
	boost::filesystem::directory_iterator it(p), end;

	for(; it != end; ++it, ++i)
	{
		list.append(std::to_string(i) + ": " + it->path().filename().string() + "\r\n");
	}

	Map::count = i;

	return list;
}

bool Map::exists(int map_id)
{
	return map_id >= 1 && map_id <= count;
}
