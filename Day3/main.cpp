#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

string getLargestJoltageSubsequence(string powerbank, int length = 2){
  string result = "";
  
  string monotonicString;
  stack<int> indexStack;

  for (int i = 0; i < powerbank.length(); i++){
    char joltage = powerbank.at(i);

    while (monotonicString.length() != 0 && monotonicString.back() < joltage){
      monotonicString.pop_back();
      indexStack.pop();
    }

    indexStack.push(i);
    monotonicString += joltage;
  }

  result = monotonicString;
  if (result.length() < length){
    int remainingLength = length - result.length();
    monotonicString + getLargestJoltageSubsequence(powerbank.substr(indexStack.top() + 1, ))
  }

  return result.substr(0, length);;
}

int solvePuzzleOne(){
  string powerBank;
  ifstream powerBanksFile("powerBanks.txt");
  int totalPower = 0;

  while (powerBanksFile >> powerBank){
    string largestJoltageSubsequence = getLargestJoltageSubsequence(powerBank, 2);
    
    cout << stoi(largestJoltageSubsequence) << endl;

    totalPower += stoi(largestJoltageSubsequence);
  }

  powerBanksFile.close();

  return totalPower;
}

int main()
{
  cout << "Total: " << solvePuzzleOne();

  return 0;
}