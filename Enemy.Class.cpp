#include "Enemy.Class.hpp"

Enemy::Enemy() : GameEntity('X')
{
}

Enemy::Enemy(int y, int x) : GameEntity('X', y, x)
{

}

Enemy::~Enemy()
{
}

Enemy::Enemy(const Enemy &src)
{
    *this = src;
}

Enemy &Enemy::operator=(const Enemy &rhs)
{
    if (this != &rhs)
	{
		this->_gameObj = rhs._gameObj;
		this->_current_x = rhs._current_x;
		this->_current_y = rhs._current_y;
	}
	return *this;
}
