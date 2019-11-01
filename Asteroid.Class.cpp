#include "Asteroid.Class.hpp"

Asteroid::Asteroid() : GameEntity('O')
{
}

Asteroid::Asteroid(int y, int x) : GameEntity('O', y, x)
{
}

Asteroid::Asteroid(const Asteroid &src)
{
	*this = src;
}

Asteroid::~Asteroid()
{
}

Asteroid &Asteroid::operator=(const Asteroid &rhs)
{
	if (this != &rhs)
	{
		this->_gameObj = rhs._gameObj;
		this->_current_x = rhs._current_x;
		this->_current_y = rhs._current_y;
	}
	return *this;
}
