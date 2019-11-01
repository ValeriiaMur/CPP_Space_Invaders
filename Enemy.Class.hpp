#ifndef ENEMY_CLASS_HPP
# define ENEMY_CLASS_HPP

#include "GameEntity.Class.hpp"

class Enemy : public GameEntity
{
private:

public:
	Enemy();
	Enemy(int y, int x);
	Enemy(const Enemy &src);
	~Enemy();

	Enemy     &operator= (const Enemy &rhs);
};

#endif
