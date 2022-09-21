#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <vector>
#include "item.h"


// Get output vector
void GetOutputList(const std::vector<Item>& items, std::string& output_str);

// Sort the work by profit in order to get the most profitable solution
void SortByProfit(std::vector<Item>& items);

// Undo the work of SortByProfit
void SortByOriginalOrder(std::vector<Item>& items);

// Solve the knapsack problem
int Solve_Knapsack(const int max_weight, std::vector<Item>& items);

#endif