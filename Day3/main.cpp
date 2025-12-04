#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int getLargestTotalJoltage(string powerbank){
  int largest = -1;
  char leftValue = powerbank.at(0);
  char rightValue = '0';

  for (int i = 1; i < powerbank.length(); i++){
    char currentJoltage = powerbank.at(i);

    if (leftValue < currentJoltage && i != powerbank.length() - 1) {
      leftValue = currentJoltage;
      rightValue = powerbank.at(i + 1);
    } else {
      rightValue = max(rightValue, currentJoltage);
    }

    string combinedJoltage;
    combinedJoltage += leftValue;
    combinedJoltage += rightValue;

    largest = max(stoi(combinedJoltage), largest);
  }

  return largest;
}

int solvePuzzleOne(){
  string powerBank;
  ifstream powerBanksFile("powerBanks.txt");
  int totalPower = 0;

  while (powerBanksFile >> powerBank){
    totalPower += getLargestTotalJoltage(powerBank);
  }

  powerBanksFile.close();

  return totalPower;
}

int main()
{
  cout << "Total: " << solvePuzzleOne();

  return 0;
}