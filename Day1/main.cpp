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
};

int main()
{
  SafeDial safeDial;
  ifstream attachedDocument("attachedDocument.txt");

  string instruction = "";
  while (attachedDocument >> instruction){
    char direction = instruction[0];
    int amount = stoi(instruction.substr(1));
  }

  cout << safeDial.moveWheel(-51);
  
  return 0;
}
