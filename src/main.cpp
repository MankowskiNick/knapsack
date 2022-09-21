// Nick Mankowski
// CS 490 - Fall 2022
// Prof. Sean McCulloch
// Knapsack

// Instructions to run
//  1) Build the program
//  2) Run the executable generated with the filenames you 
//     would like to generate outputs for.  For example, 
//     "Knapsack.cpp ks_4_0 ks_200_0 ks_500_0"
//     would generate output files for the the three listed input files.
//  3) The output files will match the names of the input files in the same directory, 
//     but will have "OUTPUT_" before the input file name.  For example, 
//     "Knapsack.cpp ks_4_0 ks_200_0 ks_500_0"
//     will generate OUTPUT_ks_4_0, OUTPUT_ks_200_0, OUTPUT_ks_500_0

#include <iostream>
#include <fstream>

#include <time.h>

#include "item.h"
#include "lib.h"
#include "iolib.h"

// Take arguments from command line
int main(int argc, char* args[]) {

    // Look at each file listed in the command line arguments(did this so I don't have to keep running again and typing different file names)
    // Argument 1 is the "./Knapsack" command, so we have to start looking at args[1] to get file names
    for (int fileIndex = 1; fileIndex < argc; fileIndex++) {    

        // Declare a file input stream & file output stream
        std::ifstream fin;
        std::ofstream fout;

        // Assign a name to the output file, it will match the input file  
        // but with "OUTPUT_" at the beginning as to not overwrite it.
        // We need to find the file name WITHOUT the directory
        std::string inputFile, outputFile;

        // Supply with the file name from console, and the inputFile & outputFile to set
        SetIOFiles(args[fileIndex], inputFile, outputFile); 

        // Open the input file
        fin.open(inputFile.data());

        // Assert that the input file successfully opened
        AssertInputFileOpenSuccess(fin.fail(), inputFile);

        // Get the number of inputs from the file
        int num_of_items;
        fin >> num_of_items;

        // Get the max weight from the file
        int max_weight;
        fin >> max_weight;

        // Declare the vector where we will hold the the inputs
        std::vector<Item> items;

        // Read in inputs from file & construct a vector of Items
        for (int i = 0; i < num_of_items; i++) {

            // Declare two ints to store the value & weight of the current item
            int cur_item_value;
            int cur_item_weight;

            // Read the current item's value & weight from the file
            fin >> cur_item_value;
            fin >> cur_item_weight;

            // Append a new item to the list of inputs, storing the 
            // value, weight, as well as the original position in 
            // the input vector
            items.push_back(Item(cur_item_value, cur_item_weight, i));
        }

        // Sort items in order of profitability
        SortByProfit(items);

        //TEMP time the function call
        time_t beforeTime = time(NULL);

        // TODO: Recursive call to find optimal solution
        int result = Solve_Knapsack(max_weight, items);

        //TEMP time the function call
        time_t afterTime = time(NULL);
        int callTime = afterTime - beforeTime;

        // Undo the sort we did previously
        SortByOriginalOrder(items);

        // Open the output file
        fout.open(outputFile.data());

        // TODO: output data
        std::cout << inputFile << ": Possible Optimal Max - " << result << "\nTime taken to get max - " << callTime << "\n"; 
        std::string output_list = "";
        GetOutputList(items, output_list);
        fout << result << "\n" << output_list << "\n";

        // Close the input & output files
        fin.close();
        fout.close();
    }

    return 0;
}