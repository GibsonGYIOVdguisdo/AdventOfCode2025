#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void insertInOrder(vector<int>* vectorPointer, int value){
  for (int i = 0; i < (*vectorPointer).size(); i++) {
    int element = (*vectorPointer).at(i);
    if (element >= value) {
      (*vectorPointer).insert((*vectorPointer).begin() + i, value);
      return;
    }
  }
  (*vectorPointer).push_back(value);
}

vector<int> getLargestJoltage(string bank, int count = 1){
  vector<int> largestJoltages;

  for (char c : bank){
    int joltage = c - '0';
    if (largestJoltages.size() < count || joltage > largestJoltages.at(0)){
      insertInOrder(&largestJoltages, joltage);
    }
    if (largestJoltages.size() > count) {
      largestJoltages.erase(largestJoltages.begin());
    }
  }

  return largestJoltages;
}

int solvePuzzleOne(){
  string powerBank;
  ifstream powerBanksFile("powerBanks.txt");

  while (powerBanksFile >> powerBank){
    vector<int> joltages = getLargestJoltage(powerBank, 2);
    for (int joltage : joltages){
      cout << joltage << endl;
    }
  }

  powerBanksFile.close();
  return 0;
}

int main()
{
  cout << "start";
  cout << "Total: " << solvePuzzleOne();

  return 0;
}