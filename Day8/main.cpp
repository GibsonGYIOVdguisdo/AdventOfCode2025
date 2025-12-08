#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <utility>


using namespace std;

class Position{
	public:
		int x;
		int y;
		int z;
	
		float getDistance(Position otherPosition){
			float distanceX = otherPosition.x - x;
			float distanceY = otherPosition.y - y;
			float distanceZ = otherPosition.z - z;
			
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

bool isPositionAlreadyInRoute(unordered_map<Position, Position, PositionHashing> links, Position routeStartPosition, Position position){
	Position currentPosition = routeStartPosition;
	
	while (links.count(currentPosition) != 0){
		currentPosition = links[currentPosition];
		
		if (currentPosition == position){
			return true;
		}
	}
	
	return false;
}

Position getEndOfRoute(unordered_map<Position, Position, PositionHashing> links, Position position){
	Position currentPosition = position;
	cout << currentPosition.toString();
	
	
	while (links.count(currentPosition) != 0){
		currentPosition = links[currentPosition];
		cout << "  -- >  " << currentPosition.toString();
	}
	
	cout << endl;
	
	return currentPosition;
}

int main(){
	vector<Position> allPositions = getPositionsFromFile("input.txt");
	
	unordered_map<float, vector<pair<Position, Position>>> distances;
	vector<float> allDistances;
	
	for (int i = 0; i < allPositions.size(); i++){
		Position position = allPositions[i];
		for (int j = i + 1; j < allPositions.size(); j++){
			Position position2 = allPositions[j];
			pair<Position, Position> posPair = {position, position2};
			float distance = position.getDistance(position2);
			if (distances.count(distance) == 0){
				allDistances.push_back(distance);
			}
			distances[distance].push_back(posPair);
		}
	}
	
	sort(allDistances.begin(), allDistances.end());
	
	vector<set<position> groupedPositions;
	int count = 0;
	int i = 0;
	while (count < 10 && i < allDistances.size()){
		cout << "f" << endl;
		for (pair<Position, Position> posPair: distances[allDistances[i]]){
			count += 1;
			cout << posPair.second.toString() << endl;
			if (!isPositionAlreadyInRoute(links, posPair.second, posPair.first)){
				links[posPair.first] = posPair.second;
			}
			if (count > 10){
				break;
			}
		}
		i++;
	}
	
	unordered_map<Position, int, PositionHashing> finalPositionCount;
	
    for (auto kvpair : links){
		Position currentPosition = kvpair.first;
		Position endOfRoute = getEndOfRoute(links, currentPosition);
		finalPositionCount.insert({endOfRoute, 0});
		finalPositionCount[endOfRoute] += 1;
	}
	
    for (auto kvpair : finalPositionCount){
		cout << kvpair.second << endl;
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