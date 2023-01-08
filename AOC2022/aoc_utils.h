#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <type_traits>
#include <set>
#define NOMINMAX
#include <Windows.h>
#include <Python.h>
#include <algorithm>
#include <stdlib.h>

namespace aoc 
{
	long long int powi(unsigned long long int base, unsigned long long int exp)
	{
		unsigned long long int res = 1;
		while (exp) {
			if (exp & 1)
				res *= base;
			exp >>= 1;
			base *= base;
		}
		return res;
	}
	enum directions {
		R = 0,
		D,
		L,
		U
	};
	using LLI = long long int;
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

	// https://docs.python.org/3/extending/embedding.html
	void CallPython(std::string PythonModuleName, std::string PythonFunctionName)
	{
		char* funcname = new char[PythonFunctionName.length() + 1];
		strcpy_s(funcname, PythonFunctionName.length() + 1, PythonFunctionName.c_str());

		char* modname = new char[PythonModuleName.length() + 1];
		strcpy_s(modname, PythonModuleName.length() + 1, PythonModuleName.c_str());

		printf("Hit any key to initialize the Python interpreter\n");
		system("pause");

		// Initialize the Python interpreter 
		// https://docs.python.org/3/c-api/init.html#c.Py_Initialize
		Py_Initialize();

		TCHAR cwd[2048];

		//auto cwd_len = GetCurrentDirectory(sizeof(cwd), cwd);
		//cwd[cwd_len] = 92;// '\'
		////cwd[cwd_len+1] = 92;// '\'
		//cwd_len += 1;
		//auto mod_len = PythonModuleName.length()+1;

		//for (size_t i = 0; i < mod_len; i++) {
		//	cwd[cwd_len + i] = modname[i];
		//}

		//char* filepath = new char[cwd_len + mod_len];
		//for (size_t i = 0; i < cwd_len+mod_len; i++) {
		//	filepath[i] = cwd[i];
		//}


		// Import a module. This is best described by referring to the built-in Python function __import__().
		// https://docs.python.org/3/c-api/import.html?highlight=pyimport_importmodule#c.PyImport_ImportModule 
		printf("Hit any key to Load the Python module %ws - %s\n", cwd, modname);
		system("pause");
		PyObject* my_module = PyImport_ImportModule(modname);
		//PyObject* my_module = PyImport_ImportModule(filepath);

		// Print a standard traceback to sys.stderr and clear the error indicator
		// https://docs.python.org/3/c-api/exceptions.html?highlight=pyerr_print#c.PyErr_Print
		PyErr_Print();

		printf("Module found\n");
		printf("Hit any key to find function %s from Python module %ws\n", funcname, cwd);
		system("pause");

		// Get the address of the particular Python function in the imported module
		// https://docs.python.org/3/c-api/object.html?highlight=pyobject_getattrstring#c.PyObject_GetAttrString
		printf("Getting address of %s in Python module\n", funcname);
		PyObject* my_function = PyObject_GetAttrString(my_module, funcname);

		PyErr_Print();

		printf("Function found\n");
		printf("Hit any key to call function %s from Python module %ws\n", funcname, cwd);
		system("pause");

		// Call a callable Python object callable, with arguments given by the tuple args. 
		// If no arguments are needed, then args can be NULL.
		// https://docs.python.org/3/c-api/call.html?highlight=pyobject_callobject#c.PyObject_CallObject
		PyObject* my_result = PyObject_CallObject(my_function, NULL);

		PyErr_Print();

		printf("Your function has been called\n");
		//system("pause");

		// Undo all initializations made by Py_Initialize() and subsequent use of Python/C API functions, 
		// and destroy all sub-interpreters (see Py_NewInterpreter() below) that were created and not yet 
		// destroyed since the last call to Py_Initialize(). Ideally, this frees all memory allocated by the Python interpreter.
		// https://docs.python.org/3/c-api/init.html?highlight=py_finalize#c.Py_FinalizeEx
		Py_Finalize();

		delete[] funcname;
		delete[] modname;
	};
}



