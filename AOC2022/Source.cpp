#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <algorithm>

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

int main() {
	Day2::Solution("day2_input.txt").Solve();
	return 0;
}