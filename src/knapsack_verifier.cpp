#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

void CheckFile(std::string input_filename, std::string output_filename){
  std::cout << "\nFILE: "<< input_filename << "\n";
  ifstream input;
  input.open(input_filename.data());
  assert(input.is_open());
  ifstream output;
  output.open(output_filename.data());
  assert(output.is_open());
  int n;
  input >> n;
  int k;
  input >> k;
  int claimed_profit;
  output >> claimed_profit;
  cout << "Claimed profit: " << claimed_profit << endl;
  int output_profit = 0;
  int weight_used = 0;
  for(int i = 0; i < n; i++){
    int cur_profit, cur_weight, taken;
    input >> cur_profit;
    input >> cur_weight;
    output >> taken;
    if(taken == 1){
      output_profit += cur_profit;
      weight_used += cur_weight;
    }
  }
  if(weight_used > k)
    cout << "ERROR: weight of " << weight_used << " exceeds capacity of " << k  << endl;
  else if(claimed_profit != output_profit)
    cout << "ERROR: Claimed profit of " << claimed_profit << " does not match actual profit of " << output_profit << endl;
  else
    cout << "OK" << endl;
}


int main(int argc, char* args[]) {
    for (int fileIndex = 1; fileIndex < argc; fileIndex+=2) {  
      CheckFile(args[fileIndex], args[fileIndex + 1]);
    }
}
