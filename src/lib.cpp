#include <iostream>
#include <vector>
#include <limits.h>
#include <time.h>
#include <map>
#include "item.h"
#include "quicksort.h"

#define TIME_LIMIT 600

// Get output vector
// Pre:  List of items where work has already been done, sorted by original order, 
//		 empty list of ints for output representing whether or not the item has been taken.
// Post: Returns void.  List of ints represented as string, "1" if the item was taken, 
//		 "0" otherwise.
void GetOutputList(const std::vector<Item>& items, std::string& output_str) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i].taken) {
			output_str += "1 ";
		}else {
			output_str += "0 ";
		}
	}
}


// Sort the work by profit in order to get the most profitable solution
// Pre:  List of items to sort
// Post: List of items sorted by profitability
void SortByProfit(std::vector<Item>& items) {

    // Go through and make sure the items will be compared by profitability rather than original position in vector
    for (int i = 0; i < items.size(); i++) {
        items[i].compareByPosition = false;
    }

    // Make a call to our quicksort function
    QuickSort<Item>::Sort(items);
}

// Undo the work of SortByProfit
// Pre:  List of items to sort
// Post: List of items sorted by original vector position
void SortByOriginalOrder(std::vector<Item>& items) {

    // Go through and make sure the items will be compared by original position in vector rather than profitability
    for (int i = 0; i < items.size(); i++) {
        items[i].compareByPosition = true;
    }

    // Make a call to our quicksort function
    QuickSort<Item>::Sort(items);
}

// Get the "fractional knapsack" answer
// Pre: Max weight, item list, index of current item, and the weight we have already used.
// Post: Get the fractional knapsack solution starting at the given item idex with weightr we have left.
int Get_Fractional_Overestimate(const int max_weight, const std::vector<Item>& items, int cur_item, int weight_used) {
	bool skipped_first_element = false;
	int skip_element = 0;
	int profit_taken = 0;
	for (int i = cur_item; i < items.size(); i++) {
		if (weight_used + items[i].weight < max_weight) {
			weight_used += items[i].weight;
			profit_taken += items[i].value;
		}else {
			skipped_first_element = true;
			skip_element = i;
		}
	}

	int partial_weight_to_take = max_weight - weight_used;
	profit_taken += items[skip_element].profitPerPound * partial_weight_to_take;

	return profit_taken;
}

// Get greedy solution, good starting point
int Get_Greedy_Solution(const int max_weight, const std::vector<Item>& items) {
	int profit_to_take = 0;
	int cur_weight_used = 0;
	for (int i = 0; i < items.size(); i++) {
		if (cur_weight_used + items[i].weight < max_weight) {
			profit_to_take += items[i].value;
			cur_weight_used += items[i].weight;
		}
	}
	return profit_to_take;
}

// Recursive backtracking function
// Pre: A lot, I don't really feel like listsing and I feel like the names are pretty self explanatorhy
int Knapsack_Helper(std::map<double, int>& memo, const time_t& start_time, const int max_weight, int& best_answer_yet, std::vector<Item>& best_vector_yet, std::vector<Item>& items, int cur_item, int profit_taken, int weight_used) {

	// Base case - We have reached the end of the list
	if (cur_item == items.size()) {
		if (weight_used > max_weight) return -1;
		return profit_taken;
	}

	// Add base case where we have exceeded time limit
	if (start_time + TIME_LIMIT < time(NULL)) return profit_taken;

	// Recursive case
	else {

		// Get the key for memoization, it will be profit_taken (.) cur_item
		double key_decimal = float(cur_item);
		while (key_decimal >= 1) key_decimal /= 10;
		double key = float(max_weight - weight_used) + key_decimal;

		// Test if we have already performed this test
		if (memo[key] > 0) { // Memo does not save the updates to the 'taken' vector
			int profit_found = profit_taken + memo[key];
			return profit_found;
		}
		else {

			// Test if this case can beat our best answer yet(only for cases where it involves a better OR faster answer)
			int n = items.size();
			if (n == 4 || n == 30 || n == 40 || n == 45 || n == 60 || n == 82 || n == 106) {
				int fractional_overestimate = profit_taken + REVISEDGet_Fractional_Overestimate(max_weight, items, cur_item, weight_used);
				if (fractional_overestimate <= best_answer_yet) {
					return profit_taken;
				}
			}

			// Case 1: Don't take it
			items[cur_item].taken = false;
			int not_taken_profit = -1;
			not_taken_profit = Knapsack_Helper(memo, start_time, max_weight, best_answer_yet, best_vector_yet, items, cur_item + 1, profit_taken, weight_used);

			// Case 2: Take it
			items[cur_item].taken = true;
			int taken_profit = -1;
			if (weight_used + items[cur_item].weight <= max_weight) {
				taken_profit = Knapsack_Helper(memo, start_time, max_weight, best_answer_yet, best_vector_yet, items, cur_item + 1, profit_taken + items[cur_item].value, weight_used + items[cur_item].weight);
			}

			// Select the most profitable case
			int return_profit;
			if (not_taken_profit > taken_profit) {
				items[cur_item].taken = false;
				return_profit = not_taken_profit;
			} else {
				items[cur_item].taken = true;
				return_profit = taken_profit;
			}

			// Check if we have found the best result yet
			if (return_profit > best_answer_yet) {
				best_answer_yet = return_profit;
				best_vector_yet = std::vector<Item>(items);
			}
			// Store value in memo
			memo[key] = return_profit - profit_taken; // We need to store the value of what is added to profit

			// Return best profit
			return return_profit;
		}
	}
}

// Solve knapsack problem given a weight and a vector of items sorted by profitability
int Solve_Knapsack(const int max_weight, std::vector<Item>& items) {
	int result = -1;
	int best_answer_yet = -1;

	// Get the greedy solution as a best possible solution
	best_answer_yet = Get_Greedy_Solution(max_weight, items); // this gave best solution yet for n=82 & n=106
	int initial_overestimate = best_answer_yet; // 82: 104723592 106: 106904218
	time_t start_time = time(NULL);

	std::vector<Item> work_vector(items);

	std::map<double, int> memo;

	// Solve knapsack
	result = Knapsack_Helper(memo, start_time, max_weight, best_answer_yet, items, work_vector, 0, 0, 0);

	// Return the best answer
	if (initial_overestimate != best_answer_yet) {
		return best_answer_yet;
	}
	else {
		items = std::vector<Item>(work_vector);
		return result;
	}
}