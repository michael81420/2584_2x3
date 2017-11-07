#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "board2x3.h"
#include "type.h"
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>

using namespace std;

class solver {
public:
	typedef double value_t;

public:
	class answer {
	public:
		answer(value_t value) : value(value) {}
	    friend std::ostream& operator <<(std::ostream& out, const answer& ans) {
	    	return out << (std::isnan(ans.value) ? -1 : ans.value);
		}
	public:
		const value_t value;
	};

public:
	solver(const std::string& args) {
		// TODO: explore the tree and save the result
		/*before_table.resize(10 * 10 * 10 * 10 * 10 * 10, -1);
		after_table.resize(10 * 10 * 10 * 10 * 10 * 10, -1);
		before_hasFound.resize(10 * 10 * 10 * 10 * 10 * 10, false);
		after_hasFound.resize(10 * 10 * 10 * 10 * 10 * 10, false);*/
		before_table.resize(16 * 16 * 16 * 16 * 16 * 16, -1);
		after_table.resize(16 * 16 * 16 * 16 * 16 * 16, -1);
		before_hasFound.resize(16 * 16 * 16 * 16 * 16 * 16, false);
		after_hasFound.resize(16 * 16 * 16 * 16 * 16 * 16, false);
		board2x3 init;
		for (int i = 0; i < 5; i++) {
			for (int j = i + 1; j < 6; j++) {
				board2x3 b[4];
				for (int k = 0; k < 4; k++) { b[k] = init; }
				b[0](i) = 1; b[0](j) = 1;
				b[1](i) = 1; b[1](j) = 2;
				b[2](i) = 2; b[2](j) = 1;
				b[3](i) = 2; b[3](j) = 2;
				calculateValue_before(b[0]);
				//cout << b[0];
				//cout << before_table[board_index(b[0])] << endl;
				calculateValue_before(b[1]);
				calculateValue_before(b[2]);
				calculateValue_before(b[3]);
			} 
		}

		std::cout << "feel free to display some messages..." << std::endl;
		std::cout << "solver is initialized." << std::endl << std::endl;
	}

	answer solve2x3(const board2x3& state, state_type type = state_type::before) {
		// TODO: find the answer in the lookup table and return it
		for (int i = 0; i < 6; i++) {
			if (state(i) > 15) {
				return -1;
			}
		}

		if (type.is_after()) {
			return after_table[board_index(state)];
		} else if (type.is_before()){
			return before_table[board_index(state)];
		} else {
			return -1;
		}
	}

	int board_index(board2x3 b) {
		return (b(0) << 20) + (b(1) << 16) + (b(2) << 12) + (b(3) << 8) + (b(4) << 4) + b(5);
	}

	double calculateValue_before(board2x3 before) {
		board2x3 all_move[4];
		int all_reward[4];
		int max_index = -1;
		double all_value[4];
		double value;

		if (before_hasFound[board_index(before)]) {
			return before_table[board_index(before)];
		} else {
			for (int i = 0; i < 4; i++) {
				board2x3 b = before;
				all_reward[i] = b.move(i);
				all_move[i] = b;
				if (all_reward[i] == -1) {
					all_value[i] = -1;
				} else {
					all_value[i] = calculateValue_after(b) + all_reward[i];
				}
			}

			for (int i = 0; i < 4; ++i) {
				if (all_reward[i] != -1) {
					if (max_index == -1) {
						max_index = i;
					} else if ( all_value[i] > all_value[max_index] ) {
						max_index = i;
					}
				}
			}

			value = (max_index == -1) ? 0 : all_value[max_index];
			save_to_table(before, value, 'b');
			return value;
		}
	}


	double calculateValue_after(board2x3 after) {
		double empty_block = 0.0;
		double value = 0.0;

		if (after_hasFound[board_index(after)]) {
			return after_table[board_index(after)];
		} else {
			for (int i = 0; i < 6; ++i) {
				if (after(i) == 0) {
					//pop tile1
					board2x3 b = after;
					b(i) = 1;
					value += calculateValue_before(b) * 0.9;
					//pop tile2
					b = after;
					b(i) = 2;
					value += calculateValue_before(b) * 0.1;
					empty_block++;
				}
			}
			value /= empty_block;
			save_to_table(after, value, 'a');
			return value;
		}
	}

	void save_to_table(board2x3 board, double value, char type) {

		if (value > 0)
		{
			//cout << board ;
		}

		for (int i = 0; i < 4; ++i) {
			board2x3 b = board;
			switch(i) {
				case 0:
					break;
				case 1:
					b.reflect_horizontal();
					break;
				case 2:
					b.reflect_vertical();
					break;
				case 3:
					b.reverse();
					break;
			}
			if (type == 'b') {
				before_table[board_index(b)] = value;
				before_hasFound[board_index(b)] = true;
			} else {
				after_table[board_index(b)] = value;
				after_hasFound[board_index(b)] = true;
			}
		}
	}

private:
	// TODO: place your transposition table here
	vector<double> before_table;
	vector<double> after_table;
	vector<bool> before_hasFound;
	vector<bool> after_hasFound;
};
