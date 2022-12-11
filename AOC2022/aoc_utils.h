#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <type_traits>
#include <set>

namespace aoc 
{
	/*std::pair<int, int> i2coord(int index, size_t w, size_t h) {
		return { index % w, index / h };
	}
	int coord2i(std::pair<int, int> coord, size_t w, size_t h) {
		return w * coord.second + coord.first;
	}*/
	template <typename T>
	class _Vec2 {
	public:
		_Vec2() {}
		_Vec2(T x, T y)
			:
			x(x),
			y(y)
		{}
		_Vec2(const _Vec2& vect)
			:
			_Vec2(vect.x, vect.y)
		{}
		_Vec2 operator-() const
		{
			return _Vec2(-x, -y);
		}
		_Vec2& operator=(const _Vec2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}
		_Vec2& operator+=(const _Vec2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		_Vec2& operator-=(const _Vec2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}
		_Vec2 operator+(const _Vec2& rhs) const
		{
			return _Vec2(*this) += rhs;
		}
		_Vec2 operator-(const _Vec2& rhs) const
		{
			return _Vec2(*this) -= rhs;
		}
		bool operator==(const _Vec2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
		bool operator!=(const _Vec2& rhs) const
		{
			return !(*this == rhs);
		}
		_Vec2& operator/=(const T& rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}
		_Vec2 operator/(const T& rhs) const
		{
			return _Vec2(*this) /= rhs;
		}
	public:
		T x;
		T y;
	};
	typedef _Vec2<int> Vei2;

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
	
	std::vector<std::string> parse_string(const std::string& str, char delim)
	{
		std::vector<std::string> parsed_text;
		size_t last = 0;
		size_t next = 0;
		while ((next = str.find(' ', last)) != std::string::npos)
		{
			parsed_text.push_back(str.substr(last, next - last));
			last = next + 1;
		}
		parsed_text.push_back(str.substr(last));
		return parsed_text;
	}


	template<typename Type>
	auto setIntersection(std::set<Type> set0, std::set<Type> set1)
	{
		std::set<Type> intersection;
		for (auto value : set0)
			if (set1.find(value) != set1.end()) {
				intersection.insert(value);
			}
		return intersection;
	};
}