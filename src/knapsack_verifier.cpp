#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;



int main(){
  cout << "Enter the input file name: ";
  string input_filename;
  cin >> input_filename;
  ifstream input;
  input.open(input_filename.data());
  assert(input.is_open());
  cout << "Enter the output file name: ";
  string output_filename;
  cin >> output_filename;
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
  return 0;
}
