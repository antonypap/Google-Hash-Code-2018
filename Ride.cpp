#include "Ride.h"


Ride::Ride()
{
}

Ride::Ride(int id, Position start, Position end, int startTime, int endTime) 
	: m_id(id), m_startPosition(start), m_endPosition(end), m_startTime(startTime), m_endTime(endTime)
{
}


Ride::~Ride()
{
}

void Ride::setRidePosition(Position start, Position end)
{
	m_startPosition = start;
	m_endPosition = end;
}

void Ride::setTime(int start, int end)
{
	m_startTime = start;
	m_endTime = end;
}

void Ride::setId(int id)
{
	m_id = id;
}

Position Ride::getStartPosition()
{
	return m_startPosition;
}

Position Ride::getEndPosition()
{
	return m_endPosition;
}

int Ride::getStartTime()
{
	return m_startTime;
}

int Ride::getEndTime()
{
	return m_endTime;
}

int Ride::getId()
{
	return m_id;
}

bool compareRidesTime(Ride& r1, Ride& r2)
{
	return r1.getStartTime() < r2.getStartTime();
}
