#include <iostream>
#include <fstream>
#include<string>

using namespace std;

class SafeDial{
  private:
    int wheelPosition = 50;
    int maxWheelPosition = 100;

  public:
    int moveWheel(int amount){
      wheelPosition = (wheelPosition + amount) % maxWheelPosition;
      if (wheelPosition < 0){
        wheelPosition = maxWheelPosition - (wheelPosition * -1);
      }
      return wheelPosition;
    }

    int getWheelPosition(){
      return wheelPosition;
    }

    int getMaxWheelPosition(){
      return maxWheelPosition;
    }
};

/*
Puzzle one is to find the amount of times the wheel ends at position 0 given the input
*/
int solvePuzzleOne(){
  SafeDial safeDial;
  ifstream attachedDocument("attachedDocument.txt");
  int zeroCount = 0;

  string instruction = "";
  while (attachedDocument >> instruction){
    char direction = instruction[0];
    int amount = stoi(instruction.substr(1));
    if (direction == 'L'){
      amount *= -1;
    }

    if (safeDial.moveWheel(amount) == 0){
      zeroCount++;
    }
  }

  return(zeroCount);
}

/*
Puzzle two is to find the amount of times the wheel is passes or ends at position 0 given the input
*/
int solvePuzzleTwoBruteForce(){
  SafeDial safeDial;
  ifstream attachedDocument("attachedDocument.txt");
  int zeroCount = 0;

  string instruction = "";
  while (attachedDocument >> instruction){
    int direction = instruction[0] == 'L' ? -1 : 1;
    int amount = stoi(instruction.substr(1));

    for (int i = 0; i < amount; i++){
      if (safeDial.moveWheel(1 * direction) == 0){
        zeroCount++;
      }
    }
  }

  return(zeroCount);
}

int solvePuzzleTwoMaths(){
  SafeDial safeDial;
  ifstream attachedDocument("attachedDocument.txt");
  int zeroCount = 0;
  int maxWheelPosition = safeDial.getMaxWheelPosition();

  string instruction = "";
  while (attachedDocument >> instruction){
    int direction = instruction[0] == 'L' ? -1 : 1;
    int amount = stoi(instruction.substr(1));
    int wheelPosition = safeDial.getWheelPosition(); 
    
    int directionalPosition = (maxWheelPosition + (wheelPosition * direction)) % maxWheelPosition;
    int zerosToAdd = (directionalPosition + amount) / maxWheelPosition;
    
    zeroCount += zerosToAdd;
    safeDial.moveWheel(amount * direction);
  }

  return(zeroCount);
}

int main()
{
  cout << solvePuzzleTwoMaths() << endl;
  cout << solvePuzzleTwoBruteForce();
  
  return 0;
}
