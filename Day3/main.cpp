#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class BigInt{
  private:
    std::string value = "0";
    
  public:
    BigInt(std::string value="0"){
      value = value;
    }
    
    void add(std::string num){
      int carryDigit = 0;
      int i = 0;
      while (i < num.length() || carryDigit > 0){
        int fromNum = i < num.length() ? num.at(num.length() - 1 - i) + carryDigit - '0': carryDigit;

        if (value.length() < i + 1){
          value = '0' + value;
        }

        carryDigit = 0;
        int fromValue = value.at(value.length() - 1 - i) - '0';
        int sum = fromNum + fromValue;
        int newDigit = sum % 10;

        carryDigit = sum / 10;
        
        value[value.length() - 1 - i] = to_string(newDigit)[0];

        i++;
      }
    }

    std::string get(){
      return value;
    }
};

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

BigInt solvePuzzleTwo(){
  string powerBank;
  ifstream powerBanksFile("powerBanks.txt");

  // std::wcout << std::filesystem::current_path() << L'\n';

  BigInt totalPower;

  while (powerBanksFile >> powerBank){
    string largestJoltageSubsequence = getLargestJoltageSubsequence(powerBank, 12);
    totalPower.add(largestJoltageSubsequence);
  }

  powerBanksFile.close();

  return totalPower;
}

int main()
{
  cout << "Total: " << solvePuzzleTwo().get();

  return 0;
}

