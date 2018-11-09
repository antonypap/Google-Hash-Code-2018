#pragma once

#include "Position.h"

class Ride
{
private:
	int m_id;
	Position m_startPosition, m_endPosition;
	int m_startTime, m_endTime;
public:
	Ride();
	Ride(int id, Position start, Position end, int startTime, int endTime);
	~Ride();
	void setRidePosition(Position start, Position end);
	void setTime(int start, int end);
	void setId(int id);
	Position getStartPosition();
	Position getEndPosition();
	int getStartTime();
	int getEndTime();
	int getId();
};

bool compareRidesTime(Ride& r1, Ride& r2);
