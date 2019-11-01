/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.Class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:57:06 by valeriiamur       #+#    #+#             */
/*   Updated: 2019/10/27 22:54:24 by rcross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.Class.hpp"

Player::Player() : GameEntity('E'), _lives(3)
{
}

Player::Player(const Player &src)
{
	*this = src;
}

Player  &Player::operator=(const Player &rhs)
{
	if (this != &rhs)
	{
		this->_gameObj = rhs._gameObj;
		this->_current_x = rhs._current_x;
		this->_current_y = rhs._current_y;
		this->_lives = rhs._lives;
	}
	return *this;
}

Player::~Player()
{
}

void	Player::loseLife(int y)
{
	this->_lives--;
	this->setX(10);
	this->setY(y);
}

int		Player::getLives()
{
	return this->_lives;
}

bool	Player::isTouched(int y, int x)
{
	// E
	//  E
	// E

	// top character
	if (this->getX() - 1 == x && this->getY() -1 == y)
	{
		return true;
	}
	// middle character
	if (this->getX() == x && this->getY() == y)
	{
		return true;
	}
	// bottom character
	if (this->getX() - 1 == x && this->getY() + 1 == y)
	{
		return true;
	}
	return false;
}
