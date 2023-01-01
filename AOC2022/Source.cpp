#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <cctype>
#include <stack>
#include <queue>
#include <ranges>
#include <assert.h>
#include "aoc_utils.h"
#include <stdlib.h>

namespace Day1 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		void LoadData() {
			std::ifstream in(filename_);
			std::vector<int> input;
			while (!in.eof())
			{
				std::string str;
				for (char ch = in.get(); ch != '\n' && !in.eof(); ch = in.get())
				{
					str += ch;
				}
				std::cout << str;
			}
		}
		void LoadData2() {
			std::ifstream in(filename_);
			std::string str;
			
			int count_current = 0;
			while (std::getline(in, str)) {
				if (str == "") {
					cal_carried_.push_back(count_current);
					count_current = 0;
					continue;
				}
				count_current += stoi(str);

			}		
		}
		void Solve() {
			LoadData2();
			std::sort(cal_carried_.rbegin(), cal_carried_.rend());

			int cal_top3 = 0;
			for (std::vector<int>::iterator it = cal_carried_.begin(); it != cal_carried_.begin()+3; ++it) {
				cal_top3 += *it;
			}
			
			std::cout << "Top calories carried : " << cal_carried_.front() << '\n';
			std::cout << "Sum of top-3 calories: " << cal_top3;
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<int> cal_carried_;
	};
}

namespace Day2 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		void ProcessData(std::pair<int,int>& scores) {
			std::ifstream in(filename_);
			std::string str;
			
			while (std::getline(in, str)) {
				int opponent_move = str[0] - 65; // Rock=0, Paper=1, Scissors=2
				int own_move1     = str[2] - 88; // idem
				int own_move2     = response_matrix[opponent_move][own_move1]; // lookup required response for lose=0/draw=1/win=2			
				scores.first  += move_scores[own_move1] + score_matrix[opponent_move][own_move1];
				scores.second += move_scores[own_move2] + score_matrix[opponent_move][own_move2];
			}
		}
		void Solve() {
			std::pair<int, int> scores = {0,0};
			ProcessData(scores);
			std::cout << "Part 1 score: " << scores.first << '\n';
			std::cout << "Part 2 score: " << scores.second;
			std::cin.get();
		}
	private:
		std::string filename_;
		 
		// score_matrix: maps opponent & own move to scores
		std::vector<std::vector<int>> score_matrix = { {3,6,0},{0,3,6},{6,0,3} };
		//                own move:
		//				   0 1 2
		//                 R P S
		//                -------
		// opponent  0 R | 3 6 0
		// move:     1 P | 0 3 6
		//   		 2 S | 6 0 3
		//
		
		// response_matrix: maps opponent move to own move 
		std::vector<std::vector<int>> response_matrix = { {2,0,1},{0,1,2},{1,2,0} };
		//                 0    1    2
		//                Lose Draw Win
		//                -------------
		// opponent  0 R | 2    0    1
		// move:     1 P | 0    1    2
		//           2 S | 1    2    0
		//		

		// move_scores: maps own move to score
		std::vector<int> move_scores = { 1,2,3 };
	};
}

namespace Day3 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		char map2val(char ch) {
			bool is_upper = std::isupper(ch);
			char offset = 96;
			if (is_upper) {
				offset = 64 - 26;
			}
			return ch - offset;
		}
		int ProcessData() {
			std::ifstream in(filename_);
			std::string str;
			int priority_count = 0;
			while (std::getline(in, str)) {
				size_t slen = str.size();
				std::unordered_set<char> bag1;
				for (size_t i = 0; i < slen/2; ++i) {
					bag1.insert(map2val(str[i]));
				}
				for (size_t i = slen/2; i < slen ; ++i) {
					auto search = bag1.find(map2val(str[i]));
					if (search != bag1.end()) {
						priority_count += *search;
						break;
					}
				}
			}
			return priority_count;
		}
		void LoadData(std::vector<std::set<char>>& dataset) {
			std::ifstream in(filename_);
			std::string str;
			int priority_count = 0;
			while (std::getline(in, str)) {
				std::set<char> bag;
				for (char ch : str) {
					bag.insert(map2val(ch));
				}
				dataset.push_back(bag);
			}
		}
		void Solve() {
			// Part1
			int count1 = ProcessData();
			std::cout << "Count, part 1: " << count1 <<  '\n';
		
			// Part2
			std::vector<std::set<char>> dataset;
			LoadData(dataset);
			int count2 = 0;
			for (size_t i = 0; i < dataset.size(); i += 3) {
				auto intersection1 = aoc::setIntersection(dataset[i], dataset[i+1]);
				auto intersection2 = aoc::setIntersection(intersection1, dataset[i + 2]);
				for (auto val : intersection2) {
					count2 += int(val);
				}
				
			}
			std::cout << "Count, part 2: " << count2;
			std::cin.get();
		}
	private:
		std::string filename_;

	};
}

namespace Day4 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		std::pair<int,int> ProcessData() {
			std::ifstream in(filename_);
			std::string str;
			
			int counter1 = 0;
			int counter2 = 0;
			while (std::getline(in, str)) {
				
				std::string delimiter1 = ",";
				std::string delimiter2 = "-";

				std::string token1 = str.substr(0, str.find(delimiter1));
				std::string token2 = str.substr(str.find(delimiter1)+1);
				
				std::string token1a = token1.substr(0, token1.find(delimiter2));
				std::string token1b = token1.substr(token1.find(delimiter2)+1);
				std::pair<int, int> range1 = { stoi(token1a), stoi(token1b) };
				
				std::string token2a = token2.substr(0, token2.find(delimiter2));
				std::string token2b = token2.substr(token2.find(delimiter2) + 1);
				std::pair<int, int> range2 = { stoi(token2a), stoi(token2b) };
				
				// Check containment
				if (((range1.first >= range2.first) && (range1.second <= range2.second)) ||
					((range1.first <= range2.first) && (range1.second >= range2.second))) {
					counter1++;
				}
				// Check overlap
				if ( range1.second >= range2.first && range1.first <= range2.second) {
					counter2++;
				}

			}
			return { counter1, counter2 };
		}
		void Solve() {
			// Part1
			std::pair<int,int> counters = ProcessData();
			std::cout << "Counter1: " << counters.first << '\n';
			std::cout << "Counter2: " << counters.second << '\n';
			std::cin.get();
		}
	private:
		std::string filename_;

	};
}

namespace Day5 {
	struct instruction
	{
		size_t _num;
		size_t _from;
		size_t _to;
	};
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{}
		void ReadStackLine(std::string& str, std::vector<std::stack<char>>& stacks)
		{
			size_t stack_nr = 0;
			for (size_t idx = 1; idx < str.size(); idx += 4)
			{
				char container = str[idx];
				if (container != ' ')
				{
					stacks[stack_nr].push(container);
				}
				stack_nr++;
			}
		}
		void LoadData() 
		{
			std::ifstream in(filename_);
			std::string str;
			std::vector<std::stack<char>> stacks_loaded;
			int seq = 0;
			while (std::getline(in, str)) {
				if (seq == 0)
				{
					// Initialize stacks and read first line
					size_t num_stacks = (str.size() - 3)/4 + 1;
					stacks_loaded.resize(num_stacks);
					stacks_method1.resize(num_stacks);
					stacks_method2.resize(num_stacks);
					ReadStackLine(str, stacks_loaded);
					seq = 1;
				}
				else if(seq == 1)
				{
					// Read stack layouts
					if (str[0] == '[')
					{
						ReadStackLine(str, stacks_loaded);
					}
					else
					{
						seq = 2;
						// Empty queues into stacks (correct the reversed ordering)
						assert (stacks_loaded.size() == stacks_method1.size());
						for (size_t i=0; i<stacks_loaded.size(); ++i)
						{
							while (!stacks_loaded[i].empty())
							{
								stacks_method1[i].push(stacks_loaded[i].top());
								stacks_method2[i].push(stacks_loaded[i].top());
								stacks_loaded[i].pop();
							}
						}
						std::getline(in, str);
					}
				}
				else if (seq == 2)
				{
					// Read instructions
					std::vector<std::string> pt = aoc::parse_string(str, ' ');
					instructions.push_back({ (size_t)stoi(pt[1]), (size_t)stoi(pt[3]), (size_t)stoi(pt[5]) });
				}
			}
		}		
		
		void Solve() 
		{	
			LoadData();
			// Method 1
			for (const auto& instr : instructions) 
			{
				for (size_t i = 0; i < instr._num; i++)
				{
					char item = stacks_method1[instr._from-1].top();
					stacks_method1[instr._from-1].pop();
					stacks_method1[instr._to-1].push(item);
				}
			}
			for (const std::stack<char>& stk : stacks_method1)
			{
				std::cout << stk.top();
			}
			std::cout<<'\n';

			// Method 2
			for (const auto& instr : instructions)
			{
				std::stack<char> temp;
				for (size_t i = 0; i < instr._num; i++)
				{
					char item = stacks_method2[instr._from - 1].top();
					stacks_method2[instr._from - 1].pop();
					temp.push(item);
				}
				while (!temp.empty())
				{
					stacks_method2[instr._to-1].push(temp.top());
					temp.pop();
				}
			}
			for (const std::stack<char>& stk : stacks_method2)
			{
				std::cout << stk.top();
			}
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::stack<char>> stacks_method1; 
		std::vector<std::stack<char>> stacks_method2;
		std::vector<instruction> instructions;
	};
}

namespace Day6 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			std::ifstream in(filename_);
			std::string str;
			std::getline(in, signal);
		}
		size_t get_marker_idx(size_t seq_len)
		{
			size_t num_unique = 1;
			size_t ptrL = 0;
			size_t ptrR = 0;
			while (num_unique != seq_len)
			{
				ptrR++;
				for (size_t idx = ptrL; idx < ptrR; idx++)
				{
					if (signal[idx] == signal[ptrR])
					{
						ptrL = idx + 1;
						num_unique = ptrR - ptrL;
						break;
					}
				}
				num_unique++;
			}
			return ptrR + 1;
		}
		void Solve() {
			std::cout << "Start of packet marker index : " << get_marker_idx(4);
			std::cout << "Start of message marker index: " << get_marker_idx(14);
			std::cin.get();
		}
	private:
		std::string filename_;
		std::string signal;
	};
}

namespace Day7 {
	// To hell with memory leaks :-)
	struct directory
	{
		directory(std::string name)
			:
			name_(name)
		{}
		std::string name_;
		std::string full_pathname_;
		directory* parent_ = nullptr;
		std::map<std::string, directory*> subdirmap;
		std::map<std::string, size_t> files_;
		size_t dirsize_ = 0;
	};
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			std::ifstream in(filename_);
			std::string str;
			while (std::getline(in, str)) {
				commands.push_back(str);
			}
		}
		size_t process_ls_command(directory* curr_dir, size_t idx) {
			while (idx < commands.size())
			{
				std::vector<std::string> lsinfo = aoc::parse_string(commands[idx],' ');
				if (lsinfo[0] == "$")
				{
					return idx - 1;
				}
				else if (lsinfo[0] == "dir")
				{
					// Insert new directory in the index
					if (curr_dir->subdirmap.find(lsinfo[1]) == curr_dir->subdirmap.end())
					{
						directory* newdir_ptr = new directory(lsinfo[1]);
						curr_dir->subdirmap[lsinfo[1]] = newdir_ptr;
						curr_dir->subdirmap[lsinfo[1]]->full_pathname_ = curr_dir->full_pathname_ + "/" + lsinfo[1];
						dirmap[curr_dir->subdirmap[lsinfo[1]]->full_pathname_] = newdir_ptr;
						curr_dir->subdirmap[lsinfo[1]]->parent_ = curr_dir;
						curr_dir->subdirmap[lsinfo[1]]->subdirmap[".."] = curr_dir;

					}
				}
				else
				{
					// Insert a new file in the index
					if (curr_dir->files_.find(lsinfo[1]) == curr_dir->files_.end())
					{
						// Process new fileinfo in current directory
						size_t filesize = (size_t)stoi(lsinfo[0]);
							curr_dir->files_[lsinfo[1]] = filesize;
						curr_dir->dirsize_ += curr_dir->files_[lsinfo[1]];
						
						// Increase size of all parent directories with added filesize
						directory* iter = curr_dir;
						while (iter->parent_ != nullptr)
						{
							iter = iter->parent_;
							iter->dirsize_ += filesize;
						}
					}
					else
					{
						assert(false);
					}
				}
				idx++;
			}
			return idx;
		}
		directory* process_cd_command(directory* curr_dir, std::string dirname)
		{
			if (dirname == "/")
			{
				return rt;
			}
			else if (curr_dir->subdirmap.find(dirname) != curr_dir->subdirmap.end())
			{
				return curr_dir->subdirmap[dirname];
			}
			return curr_dir;
		}
		void Solve() {
			rt = new directory("/");
			rt->full_pathname_ = "/";
			directory* curr_dir = rt;
			dirmap["/"] = rt;
			
			//assert(commands[0] == "$ cd /");

			for (size_t idx = 0; idx < commands.size(); ++idx)
			{
				std::vector<std::string> command = aoc::parse_string(commands[idx], ' ');
				if (command[0] == "$" && command[1] == "ls")
				{
					idx = process_ls_command(curr_dir, idx + 1);
				}
				else if (command[0] == "$" && command[1] == "cd")
				{
					curr_dir = process_cd_command(curr_dir, command[2]);
				}
			}
			size_t counter = 0;
			for (auto n : dirmap)
			{
				if (n.second->dirsize_ < 100000)
				{
					counter += n.second->dirsize_;
				}
				std::cout << n.second->full_pathname_ <<", size = " << n.second->dirsize_ << '\n';
			}
			std::cout << "Sum of sizes of all directories <100000 : " << counter;
			std::cout << "\n___\n";

			size_t dsize_total = 70000000;
			size_t dsize_req   = 30000000;
			size_t dsize_curr  = rt->dirsize_;
			size_t dsize_avail = dsize_total - dsize_curr;
			size_t dsize_to_be_deleted = dsize_req - dsize_avail;
			size_t min_size = dsize_curr;
			for (auto n : dirmap)
			{
				if (n.second->dirsize_ >= dsize_to_be_deleted)
				{
					if (n.second->dirsize_ < min_size)
					{
						min_size = n.second->dirsize_;
					}
				}
			}
			std::cout << "Size of smallest directory that can be deleted: " << min_size;
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::string> commands;
		directory* rt = nullptr;
		std::map<std::string, directory*> dirmap;
	};
}

namespace Day8 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			std::ifstream in(filename_);
			std::string str;
			while (std::getline(in, str)) {
				std::vector<int> line;
				for (char c : str)
				{
					line.push_back(int(c-48));
				}
				field.push_back(line);
			}
			width = field[0].size();
			height = field.size();
			visible= std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
			std::set<char> set;
			visible_info = std::vector<std::vector<std::pair<int, std::set<char>>>>(height, std::vector<std::pair<int, std::set<char>>>(width, { 0, set}));
		}
		void add_visibility(size_t row, size_t col, char direction)
		{
			visible[row][col] = 1;
			visible_info[row][col].first++;
			visible_info[row][col].second.insert(direction);
		}
		void Solve() {
			// scan rows top down
			for (size_t row=0; row<height; row++)
			{
				// scan columns left-right
				add_visibility(row, 0, 'L');
				size_t mark_left = 0;
				size_t highest = field[row][0];
				for (size_t col = 1; col < width; col++)
				{
					if (field[row][col] > highest)
					{
						add_visibility(row, col, 'L');
						highest = field[row][col];
					}
					else
					{
						if (field[row][col] < highest && (highest == 9))
						{
							mark_left = col;
							break;
						}
					}
				}
				// scan columns right-left
				highest = field[row][width-1];
				add_visibility(row, width - 1, 'R');
				for (size_t col = width-2; col > mark_left; col--)
				{
					if (field[row][col] > highest)
					{
						add_visibility(row, col, 'R');
						highest = field[row][col];
					}
					else
					{
						if (field[row][col] < highest && (highest == 9)) break;
					}
				}
			}
			// scan columns left to right
			for (size_t col = 0; col < width; col++)
			{
				// scan rows top-down
				add_visibility(0, col, 'T');
				size_t mark_top = 0;
				size_t highest = field[0][col];
				for (size_t row = 1; row < height; row++)
				{
					if (field[row][col] > highest)
					{
						add_visibility(row, col, 'T');
						highest = field[row][col];
					}
					else
					{
						if (field[row][col] < highest && (highest == 9))
						{
							mark_top = row;
							break;
						}
					}
				}
				// scan rows bottom-up
				add_visibility(height-1, col, 'B');
				highest = field[height-1][col];
				for (size_t row = height - 2; row > mark_top; row--)
				{
					if (field[row][col] > highest)
					{
						add_visibility(row, col, 'B');
						highest = field[row][col];
					}
					else
					{
						if (field[row][col] < highest && (highest == 9)) break;
					}
				}
			}
			size_t count = 0;
			for (const auto& row : visible) {
				for (const auto& col : row) {
					count += col;
					std::cout << ((col == 1) ? ('*') : ('.'));
				}
				std::cout << '\n';
			}
			std::cout << "Number of visible trees :" << count;
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::vector<int>> field;
		size_t width;
		size_t height;
		std::vector<std::vector<std::pair<int, std::set<char>>>> visible_info;
		std::vector<std::vector<int>> visible;
		
	};
}

namespace Day9 {

	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			std::ifstream in(filename_);
			std::string str;
			while (std::getline(in, str)) {
				std::vector<std::string> cmd = aoc::parse_string(str, ' ');
				commands.push_back({ cmd[0][0], stoi(cmd[1]) });
			}
		}
		void ProcessMove(aoc::Vei2& posH, aoc::Vei2& posT)
		{
			aoc::Vei2 posT_orig = posT;
			aoc::Vei2 dpos = posH - posT;
			int maxd = std::max(std::abs(dpos.x), std::abs(dpos.y));
			if (maxd > 1) // T needs to follow H 
			{
				if (std::abs(dpos.x) + std::abs(dpos.y) == 2)
				{
					posT += (dpos / 2);
				}
				else
				{
					if (std::abs(dpos.x) == 1)
					{
						posT += aoc::Vei2{ dpos.x, dpos.y / 2 };
					}
					else if (std::abs(dpos.x) == 2 && std::abs(dpos.y) == 2)
					{
						posT += dpos / 2;
					}
					else
					{
						posT += aoc::Vei2{ dpos.x / 2, dpos.y };
					}
				}
			}
		}
		void SolveWithKnots(size_t num_knots) {
			std::set<std::string> visitedT = { {"0,0"} };
			std::vector<aoc::Vei2> knots = std::vector<aoc::Vei2>(num_knots, { 0,0 });
			for (const auto& cmd : commands)
			{
				for (size_t i = 0; i < cmd.second; i++)
				{
					knots[0] += moves[cmd.first]; // head knot moves according to command
					for (size_t k = 0; k < knots.size() - 1; k++)
					{
						ProcessMove(knots[k], knots[k + 1]);
					}
					std::string posT_hash = std::to_string(knots.back().x) + "," + std::to_string(knots.back().y);
					visitedT.insert(posT_hash);
				}
			}
			std::string posT_hash = std::to_string(posT.x) + "," + std::to_string(posT.y);
			std::cout << "Rope with " << num_knots << " knots, tail unique cells visited:" << visitedT.size() << '\n';
		}
		void Solve()
		{
			SolveWithKnots(2);
			SolveWithKnots(10);
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::pair<char, int>> commands;
		aoc::Vei2 posH = { 0,0 };
		aoc::Vei2 posT = { 0,0 };
		std::map<char, aoc::Vei2> moves = {
			{'U',{ 0,-1} },
			{'D',{ 0, 1} },
			{'L',{-1, 0} },
			{'R',{ 1, 0} }
		};
	};
}

namespace Day10 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			std::ifstream in(filename_);
			std::string str;
			while (std::getline(in, str)) {
				commands.push_back(str);
			}
		}
		int value_at_time(int t)
		{
			// Binary search the timeline vector to get the correct index
			size_t l = 0;
			size_t r = timeline.size() - 1;
			size_t m = l + r / 2;
			while (true)
			{
				int test = timeline[m];
				if (timeline[m] == t)
				{
					return values[m-1];
				}
				else if (timeline[m] > t)
				{
					r = m;//check
					m = l + (r-l) / 2;
				}
				else if (timeline[m] < t)
				{
					if (timeline[m + 1] < t)
					{
						l = m;
						m = l + (r-l) / 2;
					}
					/*else if (timeline[m + 1] == t)
					{
						return values[m + 1];
					}*/
					else return values[m];
				}
			}
		}
		void Solve() {
			timeline.push_back(0);
			int marker = 0;
			values.push_back(1);
			for (const auto& line : commands)
			{
				std::vector<std::string> command = aoc::parse_string(line, ' ');
				if (command[0] == "noop")
				{
					marker++;
				}
				else
				{
					marker += 2;
					timeline.push_back(marker);
					values.push_back(values.back() + stoi(command[1]));
				}
			}
			// Ensure array of noobs at end of signal gets processed
			timeline.push_back(marker);
			values.push_back(values.back());

			std::vector<int> evals = { 20,60,100,140,180,220 };
			int acc = 0;
			for (int e : evals) {
				int val = value_at_time(e);
				std::cout << "Value at time " << e << ": " << val << '\n';
				acc += val*e;
			}
			std::cout << "----\nProduct: " << acc << "\n\n";

			for (int cycle = 1; cycle < 241; cycle++)
			{
				if (cycle == 237) {
					int k = 0;
				}
				int pos = (cycle-1)%40 ;
				int mpos = value_at_time(cycle);
				if (mpos == pos || mpos - 1 == pos || mpos + 1 == pos)
				{
					std::cout << '#';
				}
				else
				{
					std::cout << '.';
				}
				if (cycle % 40 == 0)
				{
					std::cout << '\n';
				}
			}
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::string> commands;
		std::vector<int> timeline;
		std::vector<int> values;
	};
}

namespace Day12 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			int x = 0;
			int y = 0;
			//int width = 0;
			std::ifstream in(filename_);
			while (!in.eof())
			{
				std::vector<char> lineinput;
				for (char ch = in.get(); ch != '\n' && !in.eof(); ch = in.get())
				{
					int entry = ch;
					if (entry == 'a') {
						lowpoints.push_back({ x, y });
					}
					if (entry == 'S') {
						startpos = { x,y }; 
						entry = 'a';
						lowpoints.push_back({ x, y });
					}
					if (entry == 'E') { 
						endpos = { x,y }; 
						entry = 'z';
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
			assert (width == (int)grid[0].size());
			height = (int)grid.size();
			startval = x + y * width;
			endval = x + y * width;
		}
		std::string Hash(const aoc::Vei2& pos) const
		{
			return std::to_string(pos.x) + "," + std::to_string(pos.y);
		}
		bool IsValidPos(const aoc::Vei2& pos) const
		{
			if (pos.x < 0) return false;
			if (pos.x > width - 1) return false;
			if (pos.y < 0) return false;
			if (pos.y > height - 1) return false;
			return true;
		}
		std::vector<aoc::Vei2> GetNeighbors(aoc::Vei2& currpos)
		{
			std::vector<aoc::Vei2> neighbors;
			for (auto& move : moves) {
				aoc::Vei2 newpos = currpos + move.second;
				if (IsValidPos(newpos)) {
					neighbors.push_back(newpos);
				}
			}
			return neighbors;
		}
		size_t SolveFromAtoB(aoc::Vei2 spos, aoc::Vei2 epos) {
			assert(queue.size() == 0);
			assert(visited.size() == 0);
			size_t move_count = 0;
			aoc::Vei2 currpos = spos;
			queue.push({ currpos, move_count });
			visited.insert(Hash(currpos));
			while (!queue.empty()) {
				currpos = queue.front().first;
				move_count = queue.front().second;
				queue.pop();
				if (currpos == epos) {
					break;
				}
				std::vector<aoc::Vei2> neighbors = GetNeighbors(currpos);
				for (const auto& n : neighbors) {
					std::string nhash = Hash(n);
					char diff = grid[n.y][n.x] - grid[currpos.y][currpos.x];
					if (diff <= 1 && visited.find(nhash) == visited.end()) {
						queue.push({ n, move_count + 1 });
						visited.insert(nhash);
					}
				}
			}
			visited.clear();
			if (queue.empty()) return 1000000000;
			while (!queue.empty()) queue.pop();
			return move_count;
		}
		void Solve() {
			std::cout << "Num steps: " << SolveFromAtoB(startpos, endpos) << '\n';

			size_t minsteps = 1000000000;
			for (auto lp : lowpoints) { // could optimize by using dynamic programming here...
				size_t steps = SolveFromAtoB(lp, endpos);
				//std::cout << "lp (" << lp.x << "," << lp.y << "), steps: " << steps << '\n';
				if (steps < minsteps) minsteps = steps;
			}
			std::cout << "Min steps: " << minsteps << '\n';
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::vector<char>> grid;
		std::map<int, char> cellvalues;
		std::vector<aoc::Vei2> lowpoints;
		aoc::Vei2 startpos;
		aoc::Vei2 endpos;
		int width;
		int height;
		int startval;
		int endval;
		std::set<std::string> visited;
		std::queue<std::pair<aoc::Vei2,size_t>> queue; // queue entries: { position, move_counter }
		std::map<char, aoc::Vei2> moves = {
			{'U',{ 0,-1} },
			{'D',{ 0, 1} },
			{'L',{-1, 0} },
			{'R',{ 1, 0} }
		};
	};
}

namespace Day15 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			std::ifstream in(filename_);
			std::string str;
			while (std::getline(in, str)) {
				auto parsed = aoc::parse_string(str, '=');
				int sensorX = stoi(aoc::parse_string(parsed[1], ',')[0]);
				int sensorY = stoi(aoc::parse_string(parsed[2], ':')[0]);
				int beaconX = stoi(aoc::parse_string(parsed[3], ',')[0]);
				int beaconY = stoi(parsed[4]);
				input.push_back({sensorX,sensorY,beaconX,beaconY});
			}
		}
		void Solve() {
			Solve1();
			Solve2();
		}
		void Solve1() {
			int LINE = 2000000;
			for (const std::vector<int>& line : input)
			{
				int distance = std::abs(line[0] - line[2]) + std::abs(line[1] - line[3]);
				if (std::abs(LINE - line[1]) <= distance ) {
					int y = LINE;
					int offsetY = std::abs(y - line[1]);
					int offsetX = std::abs(std::abs(offsetY) - distance);
					for (int x = line[0] - offsetX; x <= line[0] + offsetX; x++)
					{
						map[y][x] = true;
					}
					if (line[3]==LINE) map[line[3]].erase(line[2]);
				}
			}
			std::cout << "Answer part 1: " << map[LINE].size() << "\n[Press enter]\n";
			std::cin.get();
		}
		void Solve2() {
			int LOW = 0;
			int HIGH = 4000000;
			std::cout << "Processing input";
			std::vector<aoc::segments> segvec = std::vector<aoc::segments>(HIGH-LOW,aoc::segments(LOW, HIGH));
			for (const std::vector<int>& line : input)
			{
				std::cout << ".";
				int distance = std::abs(line[0] - line[2]) + std::abs(line[1] - line[3]);
				for (int y = line[1]-distance; y <= line[1]+distance; y++)
				{
					int offsetY = std::abs(y - line[1]);
					if (y >= LOW && y < HIGH)
					{
						int offsetX = std::abs(std::abs(offsetY) - distance);
						int xmin = line[0] - offsetX;
						int xmax = line[0] + offsetX;
						if ((xmin >= LOW && xmin <= HIGH) || (xmax >= LOW && xmax <= HIGH) || (xmin <= LOW && xmax >= HIGH))
						{
							segvec[y].cut(xmin, xmax);
						}
					}
				}
			}
			for (size_t y = 0; y < segvec.size(); ++y) {
				if (segvec[y].segmap.size()>0)
				{
					int x = segvec[y].segmap[0].first;
					std::cout << "\nAnswer part 2: (x=" << x << ",y=" << y << "), tuning freq:" << (long long)x * 4000000 + (long long)y << "\n[Press enter]\n";
				}
			}
			std::cin.get();
		}

	private:
		std::string filename_;
		std::vector<std::vector<int>> input;
		std::map<int, std::map<int, bool>> map;

	};
}

namespace Day16 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			LoadData();
		}
		void LoadData(){
			std::ifstream in(filename_);
			std::string str;
			std::map<std::string, int> release_rates;
			std::map<std::string, std::set<std::string>> edges;
			while (std::getline(in, str)) {
				auto parsed = aoc::parse_string(str, ' ');
				auto parsed1 = aoc::parse_string(parsed[4], '=');
				auto parsed2 = aoc::parse_string(parsed1[1], ';');
				//auto parsed3 = aoc::parse_string(str, 's');
				
				std::string node_name = parsed[1];
				int rate = stoi(parsed2[0]);
				std::string target = "";
				std::set<std::string> targets;
				for (size_t k = 9; k < parsed.size(); k++)
				{
					for (size_t i = 0; i < parsed[k].size(); i++) {
						if (parsed[k][i] != ' ' && parsed[k][i] != ',') {
							target += parsed[k][i];
						}
						if (target.size() == 2) {
							targets.insert(target);
							target = "";
						}
					}
				}
				release_rates[node_name] = rate;
				edges[node_name] = targets;
			}
			g = aoc::Graph(release_rates,edges);
		}
		int GetMaxFlow(aoc::Graph& g, int acc) {
			int max_flow = 0;
			for (auto target_valve : g.reachable_valves[g.currnode]) {
				int accumulated_flow = 0;
				int time_left = g.T - g.t;
				int action_timespan = target_valve.second + 1;
				if (time_left <= action_timespan) {
					continue; // no time left to open this valve, continue to the next
				}
				if (g.node_rates[target_valve.first] > 0) {
					std::string currnode = g.currnode;
					int rate = g.node_rates[target_valve.first];
					int added_flow = rate * (time_left - action_timespan);
					
					// adjust the graph to reflect the action taken
					g.currnode = target_valve.first;
					g.t += action_timespan;
					g.node_rates[target_valve.first] = 0; // set flow to zero, indicating value has been opened
					
					// Keep track of visited valves using a 64 bitcode
					path += target_valve.first;
					aoc::ULL switch_on = (aoc::ULL(1) << g.node2idx[target_valve.first]);
					visited |= switch_on;
//visited_str = aoc::ToBin(visited);

// Recurse
accumulated_flow = added_flow + GetMaxFlow(g, acc + added_flow);
//std::cout << visited_str << ", " << acc+added_flow << ", " << path << '\n';

// Store max attainable flow release yields for all possible routings
if (flowmap.find(visited) == flowmap.end() || acc + added_flow > flowmap[visited]) {
	flowmap[visited] = acc + added_flow;
}

// revert the graph (to continue the recursion)
visited &= ~switch_on;
visited_str = aoc::ToBin(visited);
if (path.size() > 1) {
	path.pop_back();
	path.pop_back();
}

g.currnode = currnode;
g.t -= action_timespan;
g.node_rates[target_valve.first] = rate; // reset flow
				}
				if (accumulated_flow > max_flow) {
					max_flow = accumulated_flow;
				}
			}
			return max_flow;
		}
		void Solve1() {
			g.T = 30;
			auto max_flow = GetMaxFlow(g, 0);
			std::cout << "Max flow: " << max_flow << std::endl;
			std::cin.get();
		}
		void Solve2() {
			clear(); // reset relevant member data
			g.T = 26;
			auto max_flow = GetMaxFlow(g, 0);
			std::cout << "Max flow: " << max_flow << std::endl;
			//print_flowmap();

			int maxscore = 0;
			aoc::ULL l1 = 0;
			aoc::ULL l2 = 0;
			for (auto e1 : flowmap) {
				for (auto e2 : flowmap) {
					if (((e1.first & e2.first) == 0) && e1 != e2) {
						maxscore = std::max(e1.second + e2.second, maxscore);
						l1 = e1.first;
						l2 = e2.first;
					}
				}
			}
			std::cout << "Maxscore: " << maxscore << '\n';
			std::cout << aoc::ToBin(l1) << '\n' << aoc::ToBin(l2);
			std::cin.get();
		}
		void Solve() {
			Solve1();
			Solve2();
		}

	private:
		void clear() {
			flowmap.clear();
			visited = 0;
			path = "";
			std::string visited_str = std::string('0', 64);
		}
		void print_flowmap() {
			for (auto e : flowmap) {
				std::cout << aoc::ToBin(e.first) << "," << e.second << '\n';
			}
		}
		std::string filename_;
		aoc::Graph g;
		//std::map<int, std::vector<std::string>> paths;
		std::map<aoc::ULL, int> flowmap;
		std::string path;
		unsigned long long int visited = 0;
		std::string visited_str = std::string('0', 64);
		int max_depth = 0;
		int max_score = 0;
	};
}

namespace Day19 {
	struct RobotAccounting {
		int num;
		// cost in [#ORE, #CLA, #OBS] 
		aoc::units ORErobot = aoc::units(0, 0, 0, 0);
		aoc::units CLArobot = aoc::units(0, 0, 0, 0);
		aoc::units OBSrobot = aoc::units(0, 0, 0, 0);
		aoc::units GEOrobot = aoc::units(0, 0, 0, 0);

	};
	struct Assets {
		aoc::units wallet = aoc::units(0, 0, 0, 0);
		aoc::units robots = aoc::units(0, 0, 0, 0);
	};
	class Solution 
	{
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
			LoadData();
		}
		void LoadData() {
			std::ifstream in(filename_);
			std::string str;
			std::map<std::string, int> release_rates;
			std::map<std::string, std::set<std::string>> edges;
			int count = 1;
			while (std::getline(in, str)) {
				auto parsed = aoc::parse_string(str, ' ');
				RobotAccounting pricelist;
				pricelist.num = count;
				pricelist.ORErobot.ORE = stoi(parsed[6]);
				pricelist.CLArobot.ORE = stoi(parsed[12]);
				pricelist.OBSrobot.ORE = stoi(parsed[18]);
				pricelist.OBSrobot.CLA = stoi(parsed[21]);
				pricelist.GEOrobot.ORE = stoi(parsed[27]);
				pricelist.GEOrobot.OBS = stoi(parsed[30]);
				blueprints.push_back(pricelist);
				count++;
			}
		}
		aoc::units GetBuyingOptions(const aoc::units& wallet, const RobotAccounting& pricelist) const {
			return { pricelist.ORErobot / wallet,  pricelist.CLArobot / wallet, pricelist.OBSrobot / wallet, pricelist.GEOrobot / wallet };
		}
		Assets MakePurchase(const aoc::units& purchase, Assets assets, const RobotAccounting& pricelist) const {
			assets.wallet -= pricelist.ORErobot * purchase.ORE;
			assets.wallet -= pricelist.CLArobot * purchase.CLA;
			assets.wallet -= pricelist.OBSrobot * purchase.OBS;
			assets.wallet -= pricelist.GEOrobot * purchase.GEO;
			assets.wallet += assets.robots;
			assets.robots += purchase;
			return assets;
		}
		void ExploreAllTrajectories(Assets assets, const RobotAccounting& pricelist, int t, aoc::units previous_purchase_options, bool  previous_purchase_made) {
			counter++;
			if (t == 32) {
				if (max_geodes.find(pricelist.num) == max_geodes.end()) {
					max_geodes[pricelist.num] = assets.wallet.GEO;
				}
				else {
					max_geodes[pricelist.num] = std::max(max_geodes[pricelist.num], assets.wallet.GEO);
				}
				return;
			}
			aoc::units purchase_options = GetBuyingOptions(assets.wallet, pricelist);
			
			// If a GEO can be bought, take this option exclusively (so return immediately)
			if (purchase_options.GEO > 0) {
				Assets new_assets = MakePurchase({ 0,0,0,1 }, assets, pricelist);
				ExploreAllTrajectories(new_assets, pricelist, t + 1, purchase_options, true);
				return;
			}
			
			// If any other robot can be bought:
			if (purchase_options.ORE > 0) {
				bool silly_purchase = (!previous_purchase_made && previous_purchase_options.ORE > 0) || assets.robots.ORE > max_ore_needed;
				if (!silly_purchase) {
					Assets new_assets = MakePurchase({ 1,0,0,0 }, assets, pricelist);
					ExploreAllTrajectories(new_assets, pricelist, t + 1, purchase_options, true);
				}
			}
			if (purchase_options.CLA > 0) {
				bool silly_purchase = (!previous_purchase_made && previous_purchase_options.CLA > 0) || assets.robots.CLA > max_cla_needed;
				if (!silly_purchase) {
					Assets new_assets = MakePurchase({ 0,1,0,0 }, assets, pricelist);
					ExploreAllTrajectories(new_assets, pricelist, t + 1, purchase_options, true);
				}
			}
			if (purchase_options.OBS > 0) {
				bool silly_purchase = (!previous_purchase_made && previous_purchase_options.OBS > 0) || assets.robots.OBS > max_obs_needed;
				if (!silly_purchase) {
					Assets new_assets = MakePurchase({ 0,0,1,0 }, assets, pricelist);
					ExploreAllTrajectories(new_assets, pricelist, t + 1, purchase_options, true);
				}
			}
			// Purchase nothing
			Assets new_assets = MakePurchase({ 0,0,0,0 }, assets, pricelist);
			ExploreAllTrajectories(new_assets, pricelist, t + 1, purchase_options, false);

			return;
		}
		void Test(const RobotAccounting& pricelist) const {
			aoc::units wallet = aoc::units(0, 0, 0, 0);
			aoc::units owned = aoc::units(1, 0, 0, 0);
			Assets assets = { wallet, owned };
			std::vector<aoc::units> purchases;
			purchases.push_back({ 0, 0, 0, 0 });//1
			purchases.push_back({ 0, 0, 0, 0 });
			purchases.push_back({ 0, 1, 0, 0 });
			purchases.push_back({ 0, 0, 0, 0 });
			purchases.push_back({ 0, 1, 0, 0 });//5
			purchases.push_back({ 0, 0, 0, 0 });
			purchases.push_back({ 0, 1, 0, 0 });
			purchases.push_back({ 0, 0, 0, 0 });
			purchases.push_back({ 0, 0, 0, 0 });
			purchases.push_back({ 0, 0, 0, 0 });//10
			purchases.push_back({ 0, 0, 1, 0 });
			purchases.push_back({ 0, 1, 0, 0 });
			purchases.push_back({ 0, 0, 0, 0 });
			purchases.push_back({ 0, 0, 0, 0 });
			purchases.push_back({ 0, 0, 1, 0 });//15
			for (auto p : purchases) {
				wallet -= pricelist.ORErobot * p.ORE;
				wallet -= pricelist.CLArobot * p.CLA;
				wallet -= pricelist.OBSrobot * p.OBS;
				wallet -= pricelist.GEOrobot * p.GEO;
				wallet += owned;
				owned += p;
			}
			return;
		}
		void Solve() {
			//Test(blueprints[0]);
			for (const RobotAccounting& pricelist : blueprints) {
				max_ore_needed = std::max(std::max(pricelist.ORErobot.ORE, pricelist.CLArobot.ORE), std::max(pricelist.OBSrobot.ORE, pricelist.GEOrobot.ORE));
				max_cla_needed = std::max(std::max(pricelist.ORErobot.CLA, pricelist.CLArobot.CLA), std::max(pricelist.OBSrobot.CLA, pricelist.GEOrobot.CLA));
				max_obs_needed = std::max(std::max(pricelist.ORErobot.OBS, pricelist.CLArobot.OBS), std::max(pricelist.OBSrobot.OBS, pricelist.GEOrobot.OBS));
				aoc::units owned = aoc::units(1, 0, 0, 0);
				aoc::units wallet = aoc::units(0, 0, 0, 0);
				Assets assets = { wallet, owned };
				previous_buying_options = { false,false,false,false };
				ExploreAllTrajectories(assets, pricelist, 0, {0,0,0,0}, false);
			}
			int sumprod = 0;
			for (auto e : max_geodes) {
				std::cout << e.first << ',' << e.second << '\n';
				sumprod += e.first * e.second;
			}
			std::cout << "Total score: " << sumprod;
			std::cin.get();
		}
	private:
		int counter=0;
		std::vector<RobotAccounting> blueprints;
		std::string filename_;
		std::map<int, int> max_geodes;
		bool have_been_saving = false;
		std::vector<bool> previous_buying_options = {false,false,false,false};
		RobotAccounting purchase_unit = RobotAccounting{ 0, { 1,0,0,0 }, { 1,0,0,0 }, { 1,0,0,0 }, { 1,0,0,0 } };
		int max_ore_needed = 0;
		int max_cla_needed = 0;
		int max_obs_needed = 0;
	};
}

namespace Day22 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{}
		void Solve() {
			LoadData();
			Init_part1();
			Run();

			LoadData();
			Init_part2();
			Run();
			std::cin.get();
		}
	private:
		void clear() {
			x_pos = 0;
			y_pos = 0;
			field.clear();
			steps.clear();
			turns.clear();
			first_xcells.clear();
			first_ycells.clear();
			last_ycells.clear();
			cubes.clear();
		}
		void LoadData() {
			std::ifstream in(filename_);
			std::string str;
			bool firstline = true;
			size_t linecount = 0;
			clear();
			while (std::getline(in, str)) {
				if (str.size() > 0) {
					max_width = std::max(max_width, str.size());
					std::vector<char> line;
					bool newline = true;
					for (size_t i = 0; i < str.size(); i++) {
						if (firstline || first_ycells.size() == i) {
							first_ycells.push_back(99999);
							last_ycells.push_back(99999);
						}
						if (str[i] == '.') {
							if (newline) {
								first_xcells.push_back(i);
								newline = false;
							}
							line.push_back('.');
							if (firstline) {
								x_pos = i;
								firstline = false;
							}
							if (first_ycells[i] == 99999) {
								first_ycells[i] = linecount;
							}
							last_ycells[i] = linecount;
						}
						else if (str[i] == '#') {
							if (newline) {
								first_xcells.push_back(i);
								newline = false;
							}
							line.push_back('#');
							if (first_ycells[i] == 99999) {
								first_ycells[i] = linecount;
							}
							last_ycells[i] = linecount;
						}
						else {
							line.push_back(' ');
						}

					}
					field.push_back(line);
					linecount++;
				}
				else {
					std::getline(in, str);
					std::string number;
					for (char c : str) {
						if (c == 'R' || c == 'L') {
							steps.push_back(stoi(number));
							number.clear();
							turns.push_back(c);
						}
						else {
							number += c;
						}
					}
					steps.push_back(stoi(number));
				}
			}
			// Determine size of cubes
			for (size_t i = 0; i < first_xcells.size(); i++) {
				cube_size = std::min(cube_size, int(field[i].size() - first_xcells[i]));
			}
			for (size_t i = 0; i < max_width; i++) {
				cube_size = std::min(cube_size, int(last_ycells[i]) - int(first_ycells[i]) + 1);
			}

			// Load cubemap
			for (size_t y = 0; y < field.size(); y += cube_size) {
				for (size_t x = 0; x < field[y].size(); x += cube_size) {
					Cube c = GetCube(y, x);
					cubes[c.ID] = c;
				}
			}



			// Init pos
			//y_pos = 5;
			//x_pos = 11;
			//direction = aoc::directions::R; 
			//y_pos = 11;
			//x_pos = 10;
			//direction = aoc::directions::D;
			//y_pos = 4;
			//x_pos = 6;
			//direction = aoc::directions::U;
		}
		struct Cube {
			int ID;
			size_t tl_y;
			size_t tl_x;
		};
		struct Relcoords {
			Cube cube;
			size_t y_rel;
			size_t x_rel;
		};
		struct Abscoords {
			size_t y;
			size_t x;
		};
		struct Morphinfo {
			int target_cube;
			char side;
			aoc::directions dir;
			bool reverse;
		};
		void DrawField() {
			system("CLS");
			for (size_t row = 0; row < field.size(); row++) {
				for (size_t col = 0; col < field[row].size(); col++) {
					if (row == y_pos && col == x_pos) {
						std::cout << '*';
					}
					else {
						std::cout << field[row][col];
					}
				}
				std::cout << std::endl;
			}
		}
		std::pair<Relcoords, aoc::directions> ExploreOutOfBounds(Relcoords rc, aoc::directions d) {
			size_t rel_x = 0;
			size_t rel_y = 0;
			std::string id = std::to_string(rc.cube.ID) + std::to_string(d);
			size_t offset = 0;
			if (d == aoc::directions::R || d == aoc::directions::L) {
				offset = rc.y_rel;
			}
			else {
				offset = rc.x_rel;
			}
			auto target_info = wrapmap[id];
			if (target_info.side == 'T') {
				rel_y = 0;
				if (target_info.reverse) {
					rel_x = cube_size - offset - 1;
				}
				else {
					rel_x = offset;
				}
			}
			else if (target_info.side == 'D') {
				rel_y = cube_size - 1;
				if (target_info.reverse) {
					rel_x = cube_size - offset - 1;
				}
				else {
					rel_x = offset;
				}
			}
			else if (target_info.side == 'L') {
				rel_x = 0;
				if (target_info.reverse) {
					rel_y = cube_size - offset - 1;
				}
				else {
					rel_y = offset;
				}
			}
			else if (target_info.side == 'R') {
				rel_x = cube_size - 1;
				if (target_info.reverse) {
					rel_y = cube_size - offset - 1;
				}
				else {
					rel_y = offset;
				}
			}
			Relcoords tco = { cubes[wrapmap[id].target_cube], rel_y, rel_x };
			return { tco, wrapmap[id].dir };
		}
		bool MoveOutOfBounds() {
			auto relco = GetRelCoord({ y_pos, x_pos });
			std::pair<Relcoords, aoc::directions> new_state = ExploreOutOfBounds(relco, direction);
			Abscoords test = GetAbsCoord(new_state.first);
			if (field[test.y][test.x] == '.') {
				y_pos = test.y;
				x_pos = test.x;
				direction = new_state.second;
				return true;
			}
			return false;
		}
		void Walk(int num_steps) {
			for (size_t i = 0; i < num_steps; i++) {
				if (direction == aoc::directions::R) {
					if (x_pos < field[y_pos].size() - 1) {
						if (field[y_pos][x_pos + 1] == '#') {
							return;
						}
						else if (field[y_pos][x_pos + 1] == '.') {
							x_pos += 1;
						}
					}
					else { // manage out of bounds to the right
						if (!MoveOutOfBounds()) {
							return;
						}
					}
				}
			
				else if (direction == aoc::directions::L) {
					if (x_pos == 0 || field[y_pos][x_pos - 1] == ' ') {
						if (!MoveOutOfBounds()) {
							return;
						}
					}
					else if (field[y_pos][x_pos - 1] == '.') {
						x_pos -= 1;
					}
					else {
						//draw_field();
						return;
					}
				}
			
				else if (direction == aoc::directions::D) {
					if (y_pos < last_ycells[x_pos]) {
						if (field[y_pos + 1][x_pos] == '#') {
							//draw_field();
							return;
						}
						else if (field[y_pos + 1][x_pos] == '.') {
							y_pos += 1;
						}
					}
					else { // manage out of bounds to the right
						if (!MoveOutOfBounds()) {
							return;
						}
					}
					
				}
				else if (direction == aoc::directions::U) {
					if (y_pos == 0 || field[y_pos - 1][x_pos] == ' ') {
						if (!MoveOutOfBounds()) {
							return;
						}
					}
					else if (field[y_pos - 1][x_pos] == '.') {
						y_pos -= 1;
					}
					else {
						return;
					}
				}
				else {
					assert(false);
				}
			}
		}
		void Turn(char turndir) {
			if (turndir == 'R') {
				direction = aoc::directions((direction + 1) % 4);
			}
			else {
				if (direction == 0) {
					direction = aoc::directions::U;
				}
				else {
					direction = aoc::directions(direction - 1);
				}
			}
		}
		Cube GetCube(size_t y, size_t x) {
			size_t tl_y = 0;
			size_t tl_x = 0;
			size_t cuberow = y / cube_size;
			size_t cubecol = x / cube_size;
			int cubeID = -1;
			for (size_t row = 0; row <= cuberow; row++) {
				for (size_t col = 0; col < field[0 + cube_size * row].size() / cube_size; col++) {
					cubeID++;
					if (row == cuberow && col == cubecol) {
						tl_y = cuberow * cube_size;
						tl_x = cubecol * cube_size;
						break;
					}
				}
			}
			return { cubeID, tl_y, tl_x };
		}
		Relcoords GetRelCoord(Abscoords ac) {
			return { GetCube(ac.y, ac.x), ac.y - (ac.y / cube_size) * cube_size, ac.x - (ac.x / cube_size) * cube_size};
		}
		Abscoords GetAbsCoord(Relcoords rc) {
			return { rc.cube.tl_y + rc.y_rel, rc.cube.tl_x + rc.x_rel };
		}
		void Init_test() {
			// works on test input only
			assert(GetCube(2, 9).ID  == 2);
			assert(GetCube(5, 9).ID  == 5);
			assert(GetCube(5, 1).ID  == 3);
			assert(GetCube(9, 5).ID  == 7);
			assert(GetCube(9, 13).ID == 9);
			auto test1 = GetRelCoord({ 2, 9 });
			auto test2 = GetRelCoord({ 5, 5 });
			auto test3 = GetRelCoord({ 1, 1 });
			auto test4 = GetRelCoord({ 11, 13 });
			auto test5 = GetAbsCoord(test1);
			auto test6 = GetAbsCoord(test2);
			auto test7 = GetAbsCoord(test3);
			auto test8 = GetAbsCoord(test4);
			// Define a map that handles wrapping
			wrapmap["22"] = { 4, 'T', aoc::directions::D, false};
			wrapmap["23"] = { 3, 'T', aoc::directions::D, true };
			wrapmap["20"] = { 9, 'R', aoc::directions::L, true };

			wrapmap["31"] = { 8, 'D', aoc::directions::U, true };
			wrapmap["32"] = { 9, 'D', aoc::directions::U, true };
			wrapmap["33"] = { 2, 'T', aoc::directions::D, true };
			
			wrapmap["41"] = { 8, 'L', aoc::directions::R, true }; // cube 4, down
			wrapmap["43"] = { 2, 'L', aoc::directions::R, false }; // cube 4, up
			
			wrapmap["50"] = { 9, 'T', aoc::directions::D, true };
			
			wrapmap["82"] = { 4, 'D', aoc::directions::U, true };
			wrapmap["81"] = { 3, 'D', aoc::directions::U, true };

			wrapmap["93"] = { 5, 'R', aoc::directions::L, true };
			wrapmap["90"] = { 2, 'R', aoc::directions::L, true };
			wrapmap["91"] = { 3, 'L', aoc::directions::R, true };
		}
		void Init_part1() {
			// Defines a map that handles wrapping based on 2D topololy of the cube
			// R=0 D=1 L=2 U=3
			wrapmap["12"] = { 2, 'R', aoc::directions::L, false };
			wrapmap["13"] = { 6, 'D', aoc::directions::U, false };

			wrapmap["23"] = { 2, 'D', aoc::directions::U, false };
			wrapmap["20"] = { 1, 'L', aoc::directions::R, false };
			wrapmap["21"] = { 2, 'T', aoc::directions::D, false };

			wrapmap["40"] = { 4, 'L', aoc::directions::R, false };
			wrapmap["42"] = { 4, 'R', aoc::directions::L, false };

			wrapmap["52"] = { 6, 'R', aoc::directions::L, false };
			wrapmap["53"] = { 7, 'D', aoc::directions::U, false };

			wrapmap["60"] = { 5, 'L', aoc::directions::R, false };
			wrapmap["61"] = { 1, 'T', aoc::directions::D, false };

			wrapmap["70"] = { 7, 'L', aoc::directions::R, false };
			wrapmap["71"] = { 5, 'T', aoc::directions::D, false };
			wrapmap["72"] = { 7, 'R', aoc::directions::L, false };
		}
		void Init_part2() {
			// Defines a map that handles wrapping
			// R=0 D=1 L=2 U=3
			wrapmap["12"] = { 5, 'L', aoc::directions::R, true };
			wrapmap["13"] = { 7, 'L', aoc::directions::R, false };

			wrapmap["23"] = { 7, 'D', aoc::directions::U, false };
			wrapmap["20"] = { 6, 'R', aoc::directions::L, true };
			wrapmap["21"] = { 4, 'R', aoc::directions::L, false };

			wrapmap["40"] = { 2, 'D', aoc::directions::U, false }; 
			wrapmap["42"] = { 5, 'T', aoc::directions::D, false }; 

			wrapmap["52"] = { 1, 'L', aoc::directions::R, true };
			wrapmap["53"] = { 4, 'L', aoc::directions::R, false };

			wrapmap["60"] = { 2, 'R', aoc::directions::L, true };
			wrapmap["61"] = { 7, 'R', aoc::directions::L, false };

			wrapmap["70"] = { 6, 'D', aoc::directions::U, false };
			wrapmap["71"] = { 2, 'T', aoc::directions::D, false };
			wrapmap["72"] = { 1, 'T', aoc::directions::D, false };
		}
		void Run() {
			for (size_t i = 0; i < turns.size(); i++) {
				Walk(steps[i]);
				Turn(turns[i]);
			}
			Walk(steps.back());
			std::cout << "final row (y)=" << y_pos + 1 << ", final col (x)=" << x_pos + 1 << ", dir=" << direction << '\n';
			std::cout << "final password: " << 1000 * (y_pos + 1) + 4 * (x_pos + 1) + direction << "\n\n";
		}
	private:
		std::string filename_;
		std::vector<std::vector<char>> field;
		int cube_size = 9999999;
		size_t max_width = 0;
		std::vector<int> steps;
		std::vector<char> turns;
		size_t x_pos = 0;
		size_t y_pos = 0;
		std::vector<size_t> first_xcells;
		std::vector<size_t> first_ycells;
		std::vector<size_t> last_ycells;
		aoc::directions direction = aoc::directions::R;
		std::map<int, Cube> cubes;
		std::map<std::string, Morphinfo> wrapmap;
	};
}

namespace Day24 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		struct Pos {
			Pos()
			{}
			Pos(int y, int x)
				:
				y(y),
				x(x)
			{}
			bool operator==(const Pos& rhs) const
			{
				return x == rhs.x && y == rhs.y;
			}
			bool operator!=(const Pos& rhs) const
			{
				return !(*this == rhs);
			}
			int y;
			int x;
		};
		struct State {
			Pos pos;
			aoc::directions dir;
		};
		struct FullState {
			FullState()
			{}
			FullState(
				Pos pos, 
				int t, 
				std::vector<std::vector<int>> fieldvals, 
				std::vector<State> storms, 
				std::vector<std::vector<int>> visited, 
				std::string path
				)
				:
				pos(pos),
				t(t),
				fieldvals(fieldvals),
				storms(storms),
				visited(visited),
				path(path)
			{}
			Pos pos;
			int t;
			std::vector<std::vector<int>> fieldvals;
			std::vector<State> storms;
			std::vector<std::vector<int>> visited;
			std::string path;
		};
		FullState LoadData() {
			std::ifstream in(filename_);
			std::string str;
			size_t linecount = 0;
			Pos curpos;
			std::vector<std::vector<int>> fieldvals;
			std::vector<State> storms;
			std::vector<std::vector<int>> visited;
			while (std::getline(in, str)) {
				if (str[2] == '#') {
					width = (int)str.size();
					height = (int)linecount + 1;
					curpos = { 0,1 };
					endpos = { (int)linecount, width - 2 };
				}
			std::vector<int> linevals;
				for (size_t i = 0; i < width; i++) {
					if (str[i] == '.') {
						linevals.push_back(0);
					}
					else if (str[i] == '#') {
						linevals.push_back(1);
					}
					else {
						linevals.push_back(1);
						switch (str[i]) {
						case '<':
							storms.push_back({ Pos(linecount,i), aoc::directions::L});
							break;
						case '>':
							storms.push_back({ Pos(linecount,i), aoc::directions::R });
							break;
						case 'v':
							storms.push_back({ Pos(linecount,i), aoc::directions::D });
							break;
						case '^':
							storms.push_back({ Pos(linecount,i), aoc::directions::U });
							break;
						assert(false);
						}
					}
				}
				fieldvals.push_back(linevals);
				linecount++;
			}
			visited = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
			visited[0][1] = 1;
			std::set<long long int> visits_in_full_cycle;
			if (width == height) {
				repeat_interval = width - 2;
			}
			else {
				repeat_interval = (width - 2) * (height - 2);
			}
			visits_in_full_cycle.insert(Hash_Time_and_Pos(0, curpos));
			return FullState(curpos, 0, fieldvals, storms, visited, "");
		}
		void DrawField(FullState fs) {
			system("CLS");
			std::cout << "end of minute " << fs.t << ", path taken " << fs.path << '\n';
			for (size_t row = 0; row < height; row++) {
				for (size_t col = 0; col < width; col++) {
					if (Pos(row, col) == fs.pos) {
						std::cout << 'E';
					}
					else {
						std::cout << fs.fieldvals[row][col];
					}
				}
				std::cout << std::endl;
			}
		}
		void MoveField(FullState& fs) {
			for (State& storm : fs.storms) {
				fs.fieldvals[storm.pos.y][storm.pos.x] -= 1;
				switch (storm.dir) {
				case aoc::directions::D:
					fs.visited[storm.pos.y][storm.pos.x] = 0;
					storm.pos.y = std::max(1, (storm.pos.y + 1) % (height - 1));
					break;
				case aoc::directions::L:
					fs.visited[storm.pos.y][storm.pos.x] = 0;
					storm.pos.x = (storm.pos.x - 1) % (width - 1);
					if (storm.pos.x < 1) {
						storm.pos.x = width- 2;
					}
					break;
				case aoc::directions::R:
					fs.visited[storm.pos.y][storm.pos.x] = 0;
					storm.pos.x = std::max(1, (storm.pos.x + 1) % (width - 1));
					break;
				case aoc::directions::U:
					fs.visited[storm.pos.y][storm.pos.x] = 0;
					storm.pos.y = (storm.pos.y - 1 ) % (height - 1);
					if (storm.pos.y < 1) {
						storm.pos.y = height - 2;
					}
					break;
				assert(false);
				}
				fs.fieldvals[storm.pos.y][storm.pos.x] += 1;
			}
		}
		std::vector<FullState> GetMoveOptions(FullState& fs) {
			std::vector<FullState> new_states;
			int new_t = fs.t + 1;
			if (fs.fieldvals[fs.pos.y][fs.pos.x - 1] == 0 && fs.visited[fs.pos.y][fs.pos.x - 1] == 0) { // check left
				Pos new_pos = { fs.pos.y, fs.pos.x - 1 };
				long long int tpos_hash = Hash_Time_and_Pos(new_t, new_pos);
				if (visits_in_full_cycle.find(tpos_hash) == visits_in_full_cycle.end()) {
					visits_in_full_cycle.insert(tpos_hash);
					fs.visited[new_pos.y][new_pos.x] = 1;
					FullState ns = FullState(new_pos, new_t, fs.fieldvals, fs.storms, fs.visited, fs.path + 'L');
					new_states.push_back(ns);
					fs.visited[new_pos.y][new_pos.x] = 0;
				}
			}
			if (fs.fieldvals[fs.pos.y][fs.pos.x + 1] == 0 && fs.visited[fs.pos.y][fs.pos.x + 1] == 0) { // check right
				Pos new_pos = Pos(fs.pos.y, fs.pos.x + 1);
				long long int tpos_hash = Hash_Time_and_Pos(new_t, new_pos);
				if (visits_in_full_cycle.find(tpos_hash) == visits_in_full_cycle.end()) {
					visits_in_full_cycle.insert(tpos_hash);
					fs.visited[new_pos.y][new_pos.x] = 1;
					FullState ns = FullState(new_pos, new_t, fs.fieldvals, fs.storms, fs.visited, fs.path + 'R');
					new_states.push_back(ns);
					fs.visited[new_pos.y][new_pos.x] = 0;
					}
			}
			if (fs.pos.y > 0 && fs.fieldvals[fs.pos.y - 1][fs.pos.x] == 0 && fs.visited[fs.pos.y - 1][fs.pos.x] == 0) { // check up
				Pos new_pos = Pos(fs.pos.y - 1, fs.pos.x);
				long long int tpos_hash = Hash_Time_and_Pos(new_t, new_pos);
				if (visits_in_full_cycle.find(tpos_hash) == visits_in_full_cycle.end()) {
					visits_in_full_cycle.insert(tpos_hash);
					fs.visited[new_pos.y][new_pos.x] = 1;
					FullState ns = FullState(new_pos, new_t, fs.fieldvals, fs.storms, fs.visited, fs.path + 'U');
					new_states.push_back(ns);
					fs.visited[new_pos.y][new_pos.x] = 0;
				}
			}
			if (fs.pos.y < (height - 1) && fs.fieldvals[fs.pos.y + 1][fs.pos.x] == 0 && fs.visited[fs.pos.y + 1][fs.pos.x] == 0) { // check down
				Pos new_pos = Pos(fs.pos.y + 1, fs.pos.x);
				long long int tpos_hash = Hash_Time_and_Pos(new_t, new_pos);
				if (visits_in_full_cycle.find(tpos_hash) == visits_in_full_cycle.end()) {
					visits_in_full_cycle.insert(tpos_hash);
					fs.visited[new_pos.y][new_pos.x] = 1;
					FullState ns = FullState(new_pos, new_t, fs.fieldvals, fs.storms, fs.visited, fs.path + 'D');
					new_states.push_back(ns);
					fs.visited[new_pos.y][new_pos.x] = 0;
				}
			}
			if (fs.fieldvals[fs.pos.y][fs.pos.x] == 0) { // stay put
				Pos new_pos = fs.pos;
				long long int tpos_hash = Hash_Time_and_Pos(new_t, new_pos);
				if (visits_in_full_cycle.find(tpos_hash) == visits_in_full_cycle.end()) {
					visits_in_full_cycle.insert(tpos_hash);
					FullState ns = FullState(new_pos, new_t, fs.fieldvals, fs.storms, fs.visited, fs.path + '.');
					new_states.push_back(ns); 
				}
			}
			return new_states;
		}
		void Solve() {
			FullState fs = LoadData();
			std::queue<FullState> queue;
			
			queue.push(fs);
			while (!queue.empty()) {
				fs = queue.front();
				queue.pop();
				MoveField(fs);
				for (auto new_state : GetMoveOptions(fs)) {
					if (new_state.pos == endpos) {
						std::cout << "End position reached after minute " << new_state.t << ", path taken: " << new_state.path << '\n';
						fs = new_state;
						while (!queue.empty()) {
							queue.pop();
						}
						break;
					}
					queue.push(new_state);
				}
			}

			fs.visited.clear();
			fs.visited = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
			fs.visited[height - 1][width - 2] = 1;
			visits_in_full_cycle.clear();
			visits_in_full_cycle.insert(Hash_Time_and_Pos(fs.t, fs.pos));
			queue.push(fs);
			while (!queue.empty()) {
				fs = queue.front();
				queue.pop();
				MoveField(fs);
				for (auto new_state : GetMoveOptions(fs)) {
					if (new_state.pos == startpos) {
						std::cout << "Start position reached after minute " << new_state.t << ", path taken: " << new_state.path << '\n';
						fs = new_state;
						while (!queue.empty()) {
							queue.pop();
						}
						break;
					}
					queue.push(new_state);
				}
			}
			
			fs.visited.clear();
			fs.visited = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
			fs.visited[0][1] = 0;
			visits_in_full_cycle.clear();
			visits_in_full_cycle.insert(Hash_Time_and_Pos(fs.t, fs.pos));
			queue.push(fs);
			while (!queue.empty()) {
				fs = queue.front();
				queue.pop();
				MoveField(fs);
				for (auto new_state : GetMoveOptions(fs)) {
					if (new_state.pos == endpos) {
						std::cout << "End position reached after minute " << new_state.t << ", path taken: " << new_state.path << '\n';
						fs = new_state;
						while (!queue.empty()) {
							queue.pop();
						}
						break;
					}
					queue.push(new_state);
				}
			}			
			std::cin.get();
		}
		long long int Hash_Time_and_Pos(int t, Pos pos) {
			long long int t_ = (long long int)(t % repeat_interval);
			long long int posidx = (long long int)(pos.y * width + pos.x);
			long long int vis = (t_ << 32) | posidx;
			return vis;
		}
	private:
		std::string filename_;
		std::set<long long int> visits_in_full_cycle;
		Pos startpos = Pos(0,1);
		Pos endpos;
		int width;
		int height;
		int repeat_interval;
	};
}

namespace Day25 {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		void LoadData() {
			std::ifstream in(filename_);
			std::string str;
			size_t linecount = 0;
			while (std::getline(in, str)) {
				input.push_back(str);
			}
			char2int['='] = -2;
			char2int['-'] = -1;
			char2int['0'] = 0;
			char2int['1'] = 1;
			char2int['2'] = 2;
			int2char[-2] = '=';
			int2char[-1] = '-';
			int2char[0] = '0';
			int2char[1] = '1';
			int2char[2] = '2';
			maxcovermap[0] = 2;
			auto test = GetExpVal(16);

			for (size_t exp = 1; exp < 20; exp++) {
				maxcovermap[exp] = 2*GetExpVal(exp) + maxcovermap[exp - 1];
			}
		}
		aoc::ULL GetExpVal(size_t exp) {
			aoc::ULL expval_;
			auto pt1 = expmap.find(exp);
			if (pt1 == expmap.end()) {
				expval_ = aoc::powi(5, exp);
				expmap[exp] = expval_;
				prodmap[expval].insert({0,0});
			}
			else {
				expval_ = pt1->second;
			}
			return expval_;
		}
		aoc::LLI Quin2Dec(std::string qnum) {
			aoc::LLI result = 0;
			for (size_t exp = 0; exp< qnum.size() ; exp++) {
				char mult_char = qnum[qnum.size() - 1 - exp];
				int mult = char2int[mult_char];
				expval = GetExpVal(exp);
				auto pt2 = prodmap[expval].find(mult);
				if (pt2 == prodmap[expval].end()) {
					toadd = expval * mult;
					prodmap[expval].insert({ mult, toadd });
				}
				else {
					toadd = prodmap[expval][mult];
				}
				result += toadd;
			}
			return result;
		}
		std::string Dec2Quin(long long int decval) {
			std::string retval;
			size_t maxexp = std::ceil(std::log(double(std::abs(decval))) / std::log(double(5)));
			
			for (size_t exp = maxexp; exp >= 0; --exp) {
				expval = GetExpVal(exp);
				for (int mult : std::vector<int>{ -2,-1,0,1,2 }) {
					aoc::LLI to_be_bridged = decval - expval * mult;
					aoc::LLI max_cover;
					if (exp == 0) { //end state reached
						retval += int2char[decval];
						while (retval[0] == '0') {
							retval.erase(0,1);
						}
						return retval;
					}
					else {
						max_cover = maxcovermap[exp - 1];
					}
					bool can_cover = std::abs(to_be_bridged) <= max_cover;
					if (can_cover) {
						retval += int2char[mult];
						decval = to_be_bridged;
						break;
					}
				}
			}
			return retval;
		}
		void Solve() {
			LoadData();
			aoc::LLI runsum = 0;
			for (std::string qnum : input) {
				runsum += Quin2Dec(qnum);
			}
			std::cout << "sum=" << runsum <<"\n";
			std::string qnum = Dec2Quin(runsum);
			std::cout << qnum << "\n";
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::string> input;
		std::map<char, int> char2int;
		std::map<int, char> int2char;
		std::map<size_t, aoc::ULL> expmap;
		std::map<aoc::ULL, std::map<aoc::LLI, aoc::LLI>> prodmap;
		std::map<size_t, aoc::ULL> maxcovermap;
		aoc::ULL expval;
		aoc::LLI toadd;
	};
}

namespace Day23 {
	aoc::LLI Pos2Hash(int y, int x) {
		return (aoc::LLI(y) << 32 | aoc::LLI(x)); // Beware: fails for negative coords, used workaround but need to fix this
	}
	struct Pos {
		Pos() {}
		Pos(int y, int x)
			:
			y(y),
			x(x)
		{
			hash = Pos2Hash(y, x);
		}
		int y;
		int x;
		aoc::LLI hash;
	};
	Pos Hash2Pos(aoc::ULL hash) {
		aoc::ULL hash2 = hash;
		int y = int(hash2 >> 32);
		int x = int(hash << 32 >> 32);
		return Pos(y,x);
	}
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		struct LocationInfo {
			LocationInfo() {};
			LocationInfo(int y, int x, bool occupied) 
				:
				y(y),
				x(x),
				occupied(occupied),
				poshash(Pos2Hash(y,x))
			{
				neighbors['N'] = {};
				neighbors['E'] = {};
				neighbors['S'] = {};
				neighbors['W'] = {};
				neighbors['N'].push_back(Pos2Hash(y - 1, x - 1));
				neighbors['N'].push_back(Pos2Hash(y - 1, x    ));
				neighbors['N'].push_back(Pos2Hash(y - 1, x + 1));
				neighbors['E'].push_back(Pos2Hash(y - 1, x + 1));
				neighbors['E'].push_back(Pos2Hash(y    , x + 1));
				neighbors['E'].push_back(Pos2Hash(y + 1, x + 1));
				neighbors['S'].push_back(Pos2Hash(y + 1, x - 1));
				neighbors['S'].push_back(Pos2Hash(y + 1, x    ));
				neighbors['S'].push_back(Pos2Hash(y + 1, x + 1));
				neighbors['W'].push_back(Pos2Hash(y - 1, x - 1));
				neighbors['W'].push_back(Pos2Hash(y    , x - 1));
				neighbors['W'].push_back(Pos2Hash(y + 1, x - 1));
			}
			int y = 0;
			int x = 0;
			bool occupied = false;
			aoc::LLI poshash = 0;
			std::map<char,std::vector<aoc::LLI>> neighbors;
		};
		void UpdateBoundaries() {
			for (const Pos& elve : elve_positions) {
				minx = std::min(minx, elve.x);
				maxx = std::max(maxx, elve.x);
				miny = std::min(miny, elve.y);
				maxy = std::max(maxy, elve.y);
			}
		}
		void AddCellToFieldMap(int y, int x, bool has_elve) {
			if (has_elve) {
				fieldmap.insert(std::pair<aoc::LLI, LocationInfo>(Pos2Hash(y, x), { y, x, true }));
			}
			else {
				fieldmap.insert(std::pair<aoc::LLI, LocationInfo>(Pos2Hash(y, x), { y, x, false }));
			}
			UpdateBoundaries();
		}
		void LoadData() {
			std::ifstream in(filename_);
			std::string str;
			int offset = 100000; // workaround to deal with hasing issue (avoid negative coords)
			int y = 0;
			while (std::getline(in, str)) {
				std::vector<char> line;
				for (size_t x = 0; x < str.size();x++) {
					line.push_back(str[x]);
					if (str[x] == '#') {
						elve_positions.push_back(Pos(y + offset, x + offset));
						AddCellToFieldMap(y+offset, x + offset, true);
					}
					else {
						AddCellToFieldMap(y + offset, x + offset, false);
					}
				}
				field.push_back(line);
				y++;
			}
		}
		bool HasNeighborsInDirection(Pos elvepos, char lookdir) {
			bool has_neighbors = false;
			for (aoc::LLI n : fieldmap[elvepos.hash].neighbors[lookdir]) {
				if (fieldmap.find(n) != fieldmap.end() && fieldmap[n].occupied) {
					has_neighbors = true;
					return has_neighbors;
				}
			}
			return has_neighbors;
		}
		bool IsNeighborFree(Pos elve) {
			bool free = true;
			for (char dir : std::vector<char>{ 'N','S','W','E' }) {
				for ( aoc::LLI n : fieldmap[elve.hash].neighbors[dir]) {
					if (fieldmap.find(n) != fieldmap.end() && fieldmap[n].occupied) {
						free = false;
						return free;
					}
				}
			}
			return free;
		}
		bool PlanAndExecuteMoves() {
			int static_count = 0;
			std::map<aoc::LLI, aoc::LLI> move_proposals;
			std::map<aoc::LLI, int> occupancy_count;
			std::set<aoc::LLI> eligible_elves;
			for (auto elvepos : elve_positions) {
				if (elvepos.hash == Pos2Hash(5, 0)) {
					int k = 0;
				}
				if (IsNeighborFree(elvepos)) { 
					static_count++;
				}
				else { // plan a move if you have neighbors
					eligible_elves.insert(elvepos.hash);
					for (size_t i = 0; i < 4; i++) {
						char lookdir = lookdirorder[(movecount + i )% 4];
						if (!HasNeighborsInDirection(elvepos, lookdir)) {
							aoc::LLI targetposhash = fieldmap[elvepos.hash].neighbors[lookdir][1];
							move_proposals[elvepos.hash] = targetposhash;
							if (occupancy_count.find(targetposhash) == occupancy_count.end()) {
								occupancy_count[targetposhash] = 1;
							}
							else {
								occupancy_count[targetposhash] += 1;
							}
							break;
						}
					}
				}
			}
			for (Pos& elvepos : elve_positions) {
				if (eligible_elves.find(elvepos.hash) != eligible_elves.end()) {
					aoc::LLI target = move_proposals[elvepos.hash];
					if (occupancy_count[target] == 1) {
						Pos targetpos = Hash2Pos(target);
						fieldmap[elvepos.hash].occupied = false;
						elvepos.y = targetpos.y;
						elvepos.x = targetpos.x;
						elvepos.hash = targetpos.hash;
						if (fieldmap.find(target) == fieldmap.end()) {
							AddCellToFieldMap(targetpos.y, targetpos.x, true);
						};
						fieldmap[target].occupied = true;
					}
				}
			}
			movecount++;
			return static_count < (int)elve_positions.size();
		}
		int DrawField() {
			int count = 0;
			UpdateBoundaries();
			for (int y = miny; y <= maxy; y++) {
				for (int x = minx; x <= maxx; x++) {
					auto it = fieldmap.find(Pos2Hash(y, x));
					if (it != fieldmap.end() && it->second.occupied) {
						std::cout << "#";
					}
					else {
						std::cout << ".";
						count++;
					}
				}
				std::cout << '\n';
			}
			std::cout << '\n';
			return count;
		}
		void Solve() {
			LoadData();
			DrawField();
			std::cout << "Initial positions on the field\n" << divider;
			while (PlanAndExecuteMoves()) {
				if (movecount == 10) {
					num_open_positions = DrawField();
					std::cout << "PART 1: After " << movecount << " moves, the numer of empty positions is: " << num_open_positions << "\n" << divider;
				}
			}
			num_open_positions = DrawField();
			std::cout << "PART 2: All elves have found their steady state position at movecount: " << movecount << " (with " << num_open_positions << " empty positions)" << '\n' << divider;
			std::cin.get();
		}
	private:
		std::string filename_;
		std::vector<std::vector<char>> field;
		std::vector<Pos> elve_positions;
		std::map<aoc::LLI, LocationInfo> fieldmap;
		int minx= 1000000000;
		int maxx=-1000000000;
		int miny= 1000000000;
		int maxy=-1000000000;
		std::vector<char> lookdirorder = { 'N','S','W','E' };
		size_t movecount = 0;
		int num_open_positions = 0;
		std::string divider = "==============================================================================\n\n\n";
	};
}


namespace DayX {
	class Solution {
	public:
		Solution(std::string filename)
			:
			filename_(filename)
		{
		}
		void Solve() {
			std::cin.get();
		}
	private:
		std::string filename_;

	};
}


int main() {
	Day23::Solution("day23_input.txt").Solve();
	return 0;
}