#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <type_traits>

namespace aoc 
{
	std::pair<int, int> i2coord(int index, size_t w, size_t h) {
		return { index % w, index / h };
	}
	int coord2i(std::pair<int, int> coord, size_t w, size_t h) {
		return w * coord.second + coord.first;
	}
	void LoadGridInput(std::string filepath, std::vector<std::vector<int>>& grid, std::map<int, int>& cellvalues, bool convertChar2Int)
	{
		int x = 0;
		int y = 0;
		int width = 0;
		std::ifstream in(filepath);
		while (!in.eof())
		{
			std::vector<int> lineinput;
			for (char ch = in.get(); ch != '\n' && !in.eof(); ch = in.get())
			{
				int entry = ch;
				if (convertChar2Int) {
					entry -= '0';
				}
				lineinput.push_back(entry);
				cellvalues[x + y * width] = entry;
				x++;
				if (x > width) {
					width = x;
				}
			}
			grid.push_back(lineinput);
			x = 0;
			y++;
		}
		return;
	}
}