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

    bool notEnoughElements = false;

    while (monotonicString.length() != 0 && monotonicString.back() < joltage){
      monotonicString.pop_back();
      int topIndex = indexStack.top();
      indexStack.pop();

      int remainingJoltages = powerbank.length() - i;
      int joltagesNeeded = length - monotonicString.length();
      
      if (remainingJoltages < joltagesNeeded){
        indexStack.push(topIndex);
        monotonicString += powerbank.at(topIndex);

        notEnoughElements = true;
        break;
      }

    }

    if (notEnoughElements){
      break;
    }
    indexStack.push(i);
    monotonicString += joltage;
  }

  result = monotonicString;
  if (result.length() < length){
    int remainingLength = length - result.length();
    if (remainingLength == 0){
      return result;
    }
    int topIndex = indexStack.size() > 0 ? indexStack.top() : 0;
    result += getLargestJoltageSubsequence(powerbank.substr(topIndex + 1), remainingLength);
  }

  return result.substr(0, length);;
}

int solvePuzzleOne(){
  string powerBank;
  ifstream powerBanksFile("powerBanks.txt");
  int totalPower = 0;

  while (powerBanksFile >> powerBank){
    string largestJoltageSubsequence = getLargestJoltageSubsequence(powerBank, 2);
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