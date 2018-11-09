#include "Vehicle.h"


Vehicle::Vehicle()
{
}

Vehicle::Vehicle(int id) : m_position(Position(0, 0)), m_id(id), m_state(0), duration(0)
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::update(std::vector<Direction> path)
{
	switch (path[0])
	{
		case UP:
			m_position.x += 1;
		case DOWN:
			m_position.x -= 1;
		case RIGHT:
			m_position.y += 1;
		case LEFT:
			m_position.y -= 1;

	}
	path.erase(path.begin());
}

void Vehicle::setState(int state)
{
	m_state = state;
}

void Vehicle::setPosition(Position p)
{
	m_position = p;
}

int Vehicle::getState()
{
	return m_state;
}

Position Vehicle::getPosition()
{
	return m_position;
}

void Vehicle::appendRidesID(int rideID)
{
	m_ridesID.push_back(rideID);
}

std::vector<int> Vehicle::getRidesID()
{
	return m_ridesID;
}
