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

int main(){
	ifstream fileContent("input.txt");
	
	vector<vector<int>> allPositions; 
	string line;
	while (fileContent >> line){
		vector<int> position;
		for (string segment : splitString(line, ',')){
			position.push_back(stoi(segment));
			cout << segment << endl;
		}
		cout << endl;
		allPositions.push_back(position);
	}

	return 0;
}