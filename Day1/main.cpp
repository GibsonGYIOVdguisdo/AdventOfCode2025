#include <iostream>
#include <fstream>

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
    cout << instruction << endl;
  }

  cout << safeDial.moveWheel(-51);
  
  return 0;
}
