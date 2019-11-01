/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEntity.Class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:58:44 by valeriiamur       #+#    #+#             */
/*   Updated: 2019/10/27 21:41:58 by rcross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameEntity.Class.hpp"

GameEntity::GameEntity() : _gameObj('^'), _current_y(0), _current_x(0), _visible(true)
{
    return;
}

GameEntity::GameEntity(char gameObj) : _gameObj(gameObj), _current_y(0), _current_x(0), _visible(true)
{
    return;
}

GameEntity::GameEntity(char gameObj, int y, int x) : _gameObj(gameObj), _current_y(y), _current_x(x), _visible(true)
{
}

GameEntity::~GameEntity()
{
    return;
}

GameEntity::GameEntity(const GameEntity &src)
{
    *this = src;
    return ;
}

GameEntity &GameEntity::operator=(const GameEntity &rhs)
{
	if (this != &rhs)
	{
		this->_gameObj = rhs._gameObj;
		this->_current_x = rhs._current_x;
		this->_current_y = rhs._current_y;
	}
	return (*this);
}

void GameEntity::moveleft(int max)
{
	(void)max;
	if (this->_current_x > 1)
		this->_current_x--;
}

void GameEntity::moveright(int max)
{
	if (this->_current_x < max - 1)
		this->_current_x++;
}

void GameEntity::moveup(int max)
{
	(void)max;
	if (this->_current_y > 1)
		this->_current_y--;
}

void GameEntity::movedown(int max)
{
	if (this->_current_y < max - 2)
		this->_current_y++;
}

char	GameEntity::getObj()
{
	return this->_gameObj;
}

int GameEntity::getX()
{
	return this->_current_x;
}

int GameEntity::getY()
{
	return this->_current_y;
}

bool    GameEntity::getVisible()
{
	return this->_visible;
}

void    GameEntity::setVisible(bool b)
{
	this->_visible = b;
}

void    GameEntity::setX(int x)
{
	this->_current_x = x;
}

void    GameEntity::setY(int y)
{
	this->_current_y = y;
}
