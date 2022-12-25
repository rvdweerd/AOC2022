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
	using ULL = unsigned long long;
	auto PosHash = [](int pos_0, int pos_1)->ULL { return (ULL(pos_0) << 32 | pos_1); };
	
	/*std::pair<int, int> i2coord(int index, size_t w, size_t h) {
		return { index % w, index / h };
	}
	int coord2i(std::pair<int, int> coord, size_t w, size_t h) {
		return w * coord.second + coord.first;
	}*/

	class units {
	public:
		units()
		{}
		units(int ore, int clay, int obs, int geo)
			:
			ORE(ore),
			CLA(clay),
			OBS(obs),
			GEO(geo)
		{}
	public:
		int ORE = 0;
		int CLA = 0;
		int OBS = 0;
		int GEO = 0;
		int operator/(const units& rhs) const
		{
			int m1 = ORE == 0 ? 999999999 : rhs.ORE / ORE;
			int m2 = CLA == 0 ? 999999999 : rhs.CLA / CLA;
			int m3 = OBS == 0 ? 999999999 : rhs.OBS / OBS;
			int m4 = GEO == 0 ? 999999999 : rhs.GEO / GEO;
			return std::min(std::min(m1,m2),std::min(m3,m4));
		}
		units& operator*=(int rhs)
		{
			ORE *= rhs;
			CLA *= rhs;
			OBS *= rhs;
			GEO *= rhs;
			return *this;
		}
		units operator*(int rhs) const
		{
			return units(*this) *= rhs;
		}
		units& operator-=(const units& rhs)
		{
			ORE -= rhs.ORE;
			CLA -= rhs.CLA;
			OBS -= rhs.OBS;
			GEO -= rhs.GEO;
			return *this;
		}
		units& operator+=(const units& rhs)
		{
			ORE += rhs.ORE;
			CLA += rhs.CLA;
			OBS += rhs.OBS;
			GEO += rhs.GEO;
			return *this;
		}
		units operator+(const units& rhs) const
		{
			return units(*this) += rhs;
		}
		units operator-(const units& rhs) const
		{
			return units(*this) -= rhs;
		}
	};

	template <typename T>
	class _Vec2 {
	public:
		_Vec2() 
		{}
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
	
	
	void LoadGridInput(std::string filepath, std::vector<std::vector<char>>& grid, std::map<int, char>& cellvalues, bool convertChar2Int)
	{
		int x = 0;
		int y = 0;
		int width = 0;
		std::ifstream in(filepath);
		while (!in.eof())
		{
			std::vector<char> lineinput;
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
		while ((next = str.find(delim, last)) != std::string::npos)
		{
			parsed_text.push_back(str.substr(last, next - last));
			last = next + 1;
		}
		parsed_text.push_back(str.substr(last));
		return parsed_text;
	}

	std::string remove_substring(std::string original, const std::string& substring)
	{
		std::size_t ind = original.find(substring); // Find the starting position of substring in the string
		if (ind != std::string::npos) {
			original.erase(ind, substring.length()); // erase function takes two parameter, the starting index in the string from where you want to erase characters and total no of characters you want to erase.
			//std::cout << original << "\n";
		}
		return original;
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
	
	class segments
	{
	public:
		segments(int low, int high)
			:
			segmap({ {low, high} })
		{}
		void cut(int low, int high)
		{
			std::vector<std::pair<int, int>> segmap_new;
			for (std::pair<int, int> seg : segmap)
			{
				if (high >= seg.first && low <= seg.second) // overlap
				{
					if (low <= seg.first && high >= seg.second) // eliminate segment
					{
						continue;
					}
					if (low > seg.first && high < seg.second) // split
					{
						//if (seg.first != low) {
						segmap_new.push_back({ seg.first,low-1 });
						//}
						//if (high != seg.second) {
						segmap_new.push_back({ high+1, seg.second });
						//}
					}
					else if (low < seg.first) // cut left
					{
						segmap_new.push_back({ high+1, seg.second });
					}
					else if (high > seg.second) // cut right
					{
						segmap_new.push_back({ seg.first, low-1 });
					}
				}
				else // no overlap, keep segment
				{
					segmap_new.push_back(seg);
				}
			}
			segmap = std::move(segmap_new);
		}
	public:
		std::vector<std::pair<int, int>> segmap;
	};

	std::string ToBin(unsigned long long int n, int min_digits = 64)
	{
		std::string bin_str;
		for (int count = 0; n != 0 || count < min_digits; n >>= 1, count++)
		{
			bin_str.push_back(bool(n & 0b1) ? '1' : '0');
		}
		std::reverse(bin_str.begin(), bin_str.end());
		return bin_str;
	}
	
	class Graph {
	
	public:
		Graph()
		{}
		Graph(std::map<std::string, int> release_rates, std::map<std::string, std::set<std::string>> edges)
			:
			releasenodes_str(64,'0'),
			t(0),
			T(30),
			node_rates(release_rates),
			edges(edges)
		{
			for (auto n : node_rates)
			{
				nodes.push_back(n.first);
			}
			std::sort(nodes.begin(), nodes.end());
			for (size_t i = 0; i < nodes.size(); ++i) {
				if (node_rates[nodes[i]] > 0) {
					releasenodes_str[63-i] = '1';
					releasenodes = releasenodes | (ULL(1) << i);
				}
				node2idx[nodes[i]] = i;
			}
			MapReachableValves();
			// switch node BB off
			/*auto test1 = ToBin(releasenodes);
			ULL offnode = (ULL(1) << 1);
			auto test2 = ToBin(offnode);
			ULL negoffnode = ~offnode;
			auto test3 = ToBin(negoffnode);
			releasenodes &= negoffnode;
			auto test4 = ToBin(releasenodes);*/
		}
	private:
		void MapReachableValves() {
			// create all from-to distances in the graph to valves with positie flowrates
			for (auto node : nodes) {
				std::map<std::string, int> reachable;
				std::set<std::string> visited;
				std::queue<std::pair<std::string, int>> queue;
				queue.push({ node,0 });
				while (!queue.empty()) {
					std::string currnode = queue.front().first;
					int steps = queue.front().second;
					queue.pop();
					//if (visited.find(currnode) == visited.end()) 
					{
						//visited.insert(currnode);
						for (auto t : edges[currnode]) {
							if (visited.find(t) == visited.end()) {
								visited.insert(t);
								if (node_rates[t] > 0) { // only map valves with positive flow
									reachable[t] = steps + 1;
								}
								queue.push({ t,steps + 1 });
							}
						}
					}
				}
				reachable_valves[node] = reachable;
			}
		}
	public:
		std::string currnode = "AA";
		ULL releasenodes=0;
		std::string releasenodes_str;
		int t;
		int T;
		std::vector<std::string> nodes;
		std::map<std::string, size_t> node2idx;
		std::map<std::string, int> node_rates;
		std::map<std::string, std::set<std::string>> edges;
		std::map<std::string, std::map<std::string, int>> reachable_valves;
	};
}

