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


int main() {
	Day4::Solution("day4_input.txt").Solve();
	return 0;
}