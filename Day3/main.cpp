#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int solvePuzzleOne(){
  string powerBank;
  ifstream powerBanksFile("powerBanks.txt");
  
  while (powerBanksFile >> powerBank){
    
  }

  powerBanksFile.close();
}

int main()
{
  cout << "Total: " << solvePuzzleOne();

  return 0;
}