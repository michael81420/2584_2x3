#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "board2x3.h"
#include "type.h"
#include <vector>
#include <algorithm>

class solver {
public:
	typedef float value_t;

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
		tran_tables.resize(8 * 8 * 8 * 8 * 8 * 8, -1);

		board2x3 init;
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; i < 5; j++) {
				board2x3 b[4];
				for (int k = 0; k < length; k++) { b[k] = init; }
				b[0](i) = 1; b[0](j) = 1;
				b[1](i) = 1; b[1](j) = 2;
				b[2](i) = 2; b[2](j) = 1;
				b[3](i) = 2; b[3](j) = 2;
				tran_table[board_index(b[0])] = calculateValue_before(b[0]);
				tran_table[board_index(b[1])] = calculateValue_before(b[1]);
				tran_table[board_index(b[2])] = calculateValue_before(b[2]);
				tran_table[board_index(b[3])] = calculateValue_before(b[3]);
			} 
		}

		std::cout << "feel free to display some messages..." << std::endl;
		std::cout << "solver is initialized." << std::endl << std::endl;
	}

	answer solve2x3(const board2x3& state, state_type type = state_type::before) {
		// TODO: find the answer in the lookup table and return it
		return -1;
	}

	int board_index(board2x3 b) {
		return (b(0) << 15) + (b(1) << 12) + (b(2) << 9) + (b(3) << 6) + (b(4) << 3) + b(5);
	}

	double calculateValue_before(board2x3 before) {
		board2x3 all_move[4];
		int all_reward[4];
		double all_value[4];

		for (int i = 0; i < 4; i++) {
			board2x3 b = before;
			all_reward[i] = b.move(i);
			all_move[i] = b;
			all_value[i] = calculateValue_after(b) + all_reward[i];
		}

		return (std::max_element(all_value, all_value + 4) != -1) ? std::max_element(all_value, all_value + 4) : 0;
	}


	double calculateValue_after(board2x3 after) {
		int empty_block = 0;
		vector<double> all_value;
		vector<double> 

		for (int i = 0; i < 5; i++) {
			if (after(i) == 0)
				empty_block++;
		}

		
	}

private:
	// TODO: place your transposition table here
	vector<double> tran_tables;
};
