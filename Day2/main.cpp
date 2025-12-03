#include <iostream>
#include <string>
#include <fstream>
#include <functional>

using namespace std;

bool isTwoRepeatingHalves(string value){
  int midPoint = value.length() / 2;

  string firstHalf = value.substr(0, midPoint);
  string lastHalf = value.substr(midPoint);

  return firstHalf == lastHalf;
}

bool isMadeOfRepeatingSubstring(string value){
  for (int i = 0; i < value.length() / 2; i++){
    if (value.length() % (i + 1) != 0){
      continue;
    }

    string substring = value.substr(0, i + 1);
    bool repeatingSubstringFound = true;
    for (int j = i + 1; j < value.length(); j += i + 1){
      if (value.substr(j, i + 1) != substring){
        repeatingSubstringFound = false;
        break;
      }
    }
    if (repeatingSubstringFound){
      return true;
    }
  }

  return false;
}

long long getSumOfInvalidIdsInRange(long long start, long long end, function<bool (string)> isValid){
  long long sumOfInvalidIds = 0;

  for (long long currentId = start; currentId <= end; currentId++){
    string idString = to_string(currentId);

    if (isValid(idString)){
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

    sumOfInvalidIds += getSumOfInvalidIdsInRange(start, end, isTwoRepeatingHalves);
  }

  return sumOfInvalidIds;
}

long long solvePuzzleTwo(string input){
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

    sumOfInvalidIds += getSumOfInvalidIdsInRange(start, end, isMadeOfRepeatingSubstring);
  }

  return sumOfInvalidIds;
}

int main()
{
  ifstream inputStream("idRanges.txt");
  string idRanges;
  inputStream >> idRanges;
  inputStream.close();

  cout << "2: " << solvePuzzleTwo(idRanges) << endl;

  return 0;
}