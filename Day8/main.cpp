#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>

using namespace std;

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

vector<vector<int>> getPositionsFromFile(string fileName){
	ifstream fileContent(fileName);
	vector<vector<int>> allPositions; 
	string line;
	while (fileContent >> line){
		vector<int> position;
		for (string segment : splitString(line, ',')){
			position.push_back(stoi(segment));
		}
		allPositions.push_back(position);
	}
	
	return allPositions;
}

int main(){
	
	vector<vector<int>> allPositions = getPositionsFromFile("input.txt");

	for (vector<int> position : allPositions){
		for (int coordinate : position){
			cout << coordinate << endl;
		}
	}

	return 0;
}