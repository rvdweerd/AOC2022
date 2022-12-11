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
	Day10::Solution("day10_input.txt").Solve();
	return 0;
}