#include <iostream>
#include <string>

using namespace std;

long long getSumOfInvalidIdsInRange(long long start, long long end){
  long long sumOfInvalidIds = 0;

  for (long long currentId = start; currentId <= end; currentId++){
    string idString = to_string(currentId);
    int midPoint = idString.length() / 2;
    if (idString.substr(0, midPoint) == idString.substr(midPoint)){
      sumOfInvalidIds += currentId;
    }
  }

  return sumOfInvalidIds;
}

long long solvePuzzleOne(){
  string input;
  cin >> input;
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

  cout << "total: " << sumOfInvalidIds;
}

int main()
{
  string input;
  cin >> input;
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

    for (long long currentId = start; currentId <= end; currentId++){
      string idString = to_string(currentId);
      int midPoint = idString.length() / 2;
      if (idString.substr(0, midPoint) == idString.substr(midPoint)){
        sumOfInvalidIds += currentId;
      }
    }
  }

  cout << "total: " << sumOfInvalidIds;
  return 0;
}