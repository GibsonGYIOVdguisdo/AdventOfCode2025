#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

using namespace std;

class Position{
	public:
		int x;
		int y;
		int z;
	
		float getDistance(Position otherPosition){
			int distanceX = abs(otherPosition.x - x);
			int distanceY = abs(otherPosition.y - y);
			int distanceZ = abs(otherPosition.z - z);
			
			return sqrt(pow(distanceX, 2) + pow(distanceY, 2) + pow(distanceZ, 2));
		}
		
		Position(vector<int> position){
			x = position[0];
			y = position[1];
			z = position[2];
		}
		
		Position(int x, int y, int z){
			this -> x = x;
			this -> y = y;
			this -> z = z;
		}
	
};

vector<string> splitString(string stringToSplit, char deliminator){
	int startOfSegment = 0;
	vector<string> segments;
	
	for (int i = 0; i < stringToSplit.length(); i++){
		char currentChar = stringToSplit[i];
		if (currentChar == deliminator){
			segments.push_back(stringToSplit.substr(startOfSegment, i - startOfSegment));
			startOfSegment = i + 1;
		}
	}
	segments.push_back(stringToSplit.substr(startOfSegment, stringToSplit.length()));
	
	return segments;
}

vector<Position> getPositionsFromFile(string fileName){
	ifstream fileContent(fileName);
	vector<Position> allPositions; 
	string line;
	while (fileContent >> line){
		vector<int> position;
		for (string segment : splitString(line, ',')){
			position.push_back(stoi(segment));
		}
		allPositions.push_back(Position(position));
	}
	
	return allPositions;
}


int main(){
	
	vector<Position> allPositions = getPositionsFromFile("input.txt");
	cout << Position(0, 0 ,0).getDistance(Position(2,2,2));

	return 0;
}