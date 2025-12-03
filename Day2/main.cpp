#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool isTwoRepeatingHalves(string value){
  int midPoint = value.length() / 2;

  string firstHalf = value.substr(0, midPoint);
  string lastHalf = value.substr(midPoint);

  return firstHalf == lastHalf;
}

long long getSumOfInvalidIdsInRange(long long start, long long end){
  long long sumOfInvalidIds = 0;

  for (long long currentId = start; currentId <= end; currentId++){
    string idString = to_string(currentId);
    
    if (isTwoRepeatingHalves(idString)){
      sumOfInvalidIds += currentId;
    }
  }

  return sumOfInvalidIds;
}



long long solvePuzzleOne(string input){
  long long sumOfInvalidIds = 0;

  while (input.length() != 0){
    int endOfSegmentIndex = input.find(',');

    string currentSegment;
    if (endOfSegmentIndex == -1){
      currentSegment = input;
      input = "";
    } else {
      currentSegment = input.substr(0, endOfSegmentIndex);
      input = input.substr(endOfSegmentIndex + 1);
    }

    int dividerPos = currentSegment.find('-');
    long long start = stoll(currentSegment.substr(0, dividerPos));
    long long end = stoll(currentSegment.substr(dividerPos + 1));

    sumOfInvalidIds += getSumOfInvalidIdsInRange(start, end);
  }

  return sumOfInvalidIds;
}

long long solvePuzzleTwo(string input){
  return 0;
}

int main()
{
  ifstream inputStream("idRanges.txt");
  string idRanges;
  inputStream >> idRanges;
  inputStream.close();

  cout << solvePuzzleTwo(idRanges);

  return 0;
}