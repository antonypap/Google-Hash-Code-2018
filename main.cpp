#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Ride.h"
#include "Vehicle.h"

#define MAX_RIDES 10000
#define MAX_FLEET 1000

int sign(int x)
{
	return (x > 0) - (x < 0);
}

int calculateDistance(const Position& p1, const Position& p2)
{
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

bool compareRidesDistance(Ride& r1, Ride& r2)
{
	return calculateDistance(r1.getStartPosition(), r1.getEndPosition()) > calculateDistance(r2.getStartPosition(), r2.getEndPosition());
}

std::vector<Direction> findShortestPath(const Position& start, const Position& end)
{
	std::vector<Direction> shortestPath;
	int dx = start.x - end.x;
	int dy = start.y - end.y;
	while (dx != 0 && dy != 0)
	{
		if (abs(dx) >= abs(dy))
		{
			shortestPath.push_back((Direction)sign(dx));
			dx -= sign(dx);
		}
		else
		{
			shortestPath.push_back((Direction)(sign(dy) * 2));
			dy -= sign(dy);
		}
	}
	return shortestPath;
}

Ride findBestRide(std::vector< std::vector<Ride> > rides, Vehicle v, int T, int bonus)
{
	std::vector<Ride>::iterator minRideIt;

	if (rides[1].size() != 0)
	{
		minRideIt = std::min_element(rides[1].begin(), rides[1].end(), compareRidesTime);
	}
	else
	{
		minRideIt = std::min_element(rides[0].begin(), rides[0].end(), compareRidesTime);

	}

	if (minRideIt->getStartTime() == 0)
	{
		rides[1].insert(rides[1].end(), rides[0].begin(), rides[0].end());
		//minRideIt = std::min_element(rides[1].begin(), rides[1].end(), compareRidesDistance);
		int minDistance = calculateDistance(v.getPosition(), rides[1][0].getStartPosition());
		Ride minRide = rides[1][0];
		for (int i = 0; i < rides[1].size(); i++)
		{
			int currentDist = calculateDistance(v.getPosition(), rides[1][i].getStartPosition());
			if (currentDist < minDistance)
			{
				minDistance = currentDist;
				minRide = rides[1][i];
			}
		}
		return minRide;
	}

	return *minRideIt;
}

Ride findLongestRide(Vehicle v, std::vector<Ride> rides)
{
	int maxDistance = calculateDistance(v.getPosition(), rides[0].getStartPosition());
	Ride maxRide = rides[0];

	for (int i = 1; i < rides.size(); i++)
	{
		int distance = calculateDistance(v.getPosition(), rides[i].getStartPosition());
		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxRide = rides[i];
		}
	}

	return maxRide;
}

std::vector<std::vector<Ride> > isPossible(Vehicle v, std::vector<Ride> rides, int time)
{	
	std::vector<Ride> possibleRides;
	std::vector<Ride> bonusRides;
	bool bonus_p = false;
	for (int i = 0; i < rides.size(); i++)
	{
		Ride r = rides[i];
		int dist = calculateDistance(v.getPosition(), r.getStartPosition());
		int rideDistance = calculateDistance(r.getStartPosition(), r.getEndPosition());

		int waitingTime = r.getStartTime() - (dist + time);

		if (waitingTime >= 0)
		{
			bonus_p = true;
		}

		if (waitingTime < 0)
			waitingTime = 0;

		if (dist + waitingTime + rideDistance <= r.getEndTime() - time)
		{
			if(bonus_p == true)
				bonusRides.push_back(r);
			else
				possibleRides.push_back(r);
		}
		bonus_p = false;
	}

	std::vector< std::vector<Ride> > allrides = { possibleRides, bonusRides };
	return allrides;
}


int main() {

	unsigned int fileIndex = 4;
	std::string inputFilePath[5] = { "Files/a.in", "Files/b.in", "Files/c.in", "Files/d.in", "Files/e.in" };
	std::ifstream file(inputFilePath[fileIndex]);

	std::string line;
	std::stringstream buffer;


	while (getline(file, line))
	{
		buffer << line << '\n';
	}


	int rows, columns, F, N, bonus, T;

	std::cout << buffer.str() << std::endl;
	buffer >> rows >> columns >> F >> N >> bonus >> T;

	int data[MAX_RIDES][6];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			buffer >> data[i][j];
		}
	}

	std::vector<Ride> rides;
	rides.resize(N);
	for (int i = 0; i < N; i++)
	{
		rides[i] = Ride(i, Position(data[i][0], data[i][1]), Position(data[i][2], data[i][3]), data[i][4], data[i][5]);
	}

	Vehicle fleet[MAX_FLEET];
	for (int i = 0; i < F; i++)
	{
		fleet[i] = Vehicle(i);
	}

	// MAIN LOOP
	for (int time = 0; time < T; time++)
	{ 
		for (int v = 0; v < F; v++)
		{
			if (fleet[v].getState() == 0)
			{
				std::vector< std::vector<Ride> > allRides = isPossible(fleet[v], rides, time);
				if (allRides[0].size() == 0 && allRides[1].size() == 0)
				{

					//Ride longestRide = findLongestRide(fleet[v], rides);
					//fleet[v].update(findShortestPath(fleet[v].getPosition(), longestRide.getStartPosition()));
					continue;
				}
				Ride bestRide = findBestRide(allRides, fleet[v], T, bonus); 
				fleet[v].setState(1);
				fleet[v].appendRidesID(bestRide.getId());

				for (int i = 0; i < rides.size(); i++)
				{
					if (bestRide.getId() == rides[i].getId())
					{
						rides.erase(rides.begin() + i);
					}
				}

				int dist = calculateDistance(fleet[v].getPosition(), bestRide.getStartPosition());
				int rideDistance = calculateDistance(bestRide.getStartPosition(), bestRide.getEndPosition());

				int waitingTime = bestRide.getStartTime() - (dist + time);
				if (waitingTime < 0)
					waitingTime = 0;

				fleet[v].duration = dist + rideDistance + waitingTime;

				fleet[v].setPosition(bestRide.getEndPosition());
			}
			else
			{
				fleet[v].duration -= 1;
				if (fleet[v].duration == 1)
				{
					fleet[v].setState(0);
				}
			}
		}
	}


	std::ofstream output;
	std::string outputFilePaths[5] = { "Files/output_a.out" ,"Files/output_b.out" ,"Files/output_c.out" ,"Files/output_d.out", "Files/output_e.out" };
	output.open(outputFilePaths[fileIndex]);
	for (int v = 0; v < F; v++)
	{
		std::vector<int> finalRides = fleet[v].getRidesID();
		output << finalRides.size() << " ";
		for (auto it : finalRides)
		{
			output << it << " ";
		}
		output << '\n';
	}
	output.close();


	return 0;
}
