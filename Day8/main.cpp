#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

class Position{
	public:
		int x;
		int y;
		int z;
	
		float getDistance(Position otherPosition){
			int distanceX = otherPosition.x - x;
			int distanceY = otherPosition.y - y;
			int distanceZ = otherPosition.z - z;
			
			return sqrt(pow(distanceX, 2) + pow(distanceY, 2) + pow(distanceZ, 2));
		}
		
		string toString() {
			std::string stringForm = std::to_string(x);
			stringForm += ",";
			stringForm += std::to_string(y);
			stringForm += ",";
			stringForm += std::to_string(z);
			return stringForm;
		}
		
		Position(){
			x = 0;
			y = 0;
			z = 0;
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
		
		
		bool operator==(const Position& otherPosition) const {
			bool result = x == otherPosition.x;
			result = result && y == otherPosition.y;
			result = result && z == otherPosition.z;
			return result;
		}
		
		bool operator!=(const Position& otherPosition) const {
			return !(*this == otherPosition);
		}
		
};

class PositionHashing{
	public:
		size_t operator()(const Position& position) const
		{
			string valueToHash = to_string(position.x) + "," + to_string(position.y) + "," + to_string(position.z);
			return hash<string>()(valueToHash);
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

Position getClosestPosition(Position position, vector<Position> positions){
	Position closestPosition;
	float smallestDistance = 0;
	bool notSet = true;
	
	for (Position currentPosition : positions){
		float currentDistance = currentPosition.getDistance(position);
		if (currentPosition != position && (notSet || (currentDistance < smallestDistance))){
			notSet = false;
			smallestDistance = currentDistance;
			closestPosition = currentPosition;
		}
	}
	
	return closestPosition;
}


int main(){
	vector<Position> allPositions = getPositionsFromFile("input.txt");
	
	unordered_map<int, vector<Position>> distances;
	vector<int> allDistances;
	
	for (Position position : allPositions){
		int distance = position.getDistance(getClosestPosition(position, allPositions));
		if (distances.find(distance) == distances.end()){
			allDistances.push_back(distance);
		}

		distances[distance].push_back(position);
	}
	
	sort(allDistances.begin(), allDistances.end());
	
	int count = 0;
	int i = 0;
	while (count < 10 && i < distances.size()){
		for (Position position : distances[allDistances[i]]){
			cout << count << ": " << position.toString() << endl;
			count += 1;
		}6
		i++;
	}
	

	
	
	
	
	// for (Position position : allPositions){
	// 	Position lastPosition;
	// 	bool revisited = false;
	// 	Position currentPosition = position;
	// 	
	// 	while (revisited == false){
	// 		currentPosition = closestPositions[currentPosition];
	// 		if (closestPositions[currentPosition] == lastPosition){
	// 			revisited = true;
	// 			currentPosition = lastPosition;
	// 		}
	// 		lastPosition = currentPosition;
	// 	}
	// 	circuitSizes.insert({currentPosition, 1});
	// 	circuitSizes[currentPosition] += 1;
	// }
	

	return 0;
}