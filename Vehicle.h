#pragma once

#include <vector>
#include "Position.h"

class Vehicle
{
private:
	Position m_position;
	int m_id;
	int m_state;
	std::vector<int> m_ridesID;
public:
	Vehicle();
	Vehicle(int id);
	~Vehicle();
	void update(std::vector<Direction> path);
	void setState(int state);
	void setPosition(Position p);
	int getState();
	Position getPosition();
	void appendRidesID(int rideID);
	std::vector<int> getRidesID();
	int duration;
};


