#ifndef ASTEROID_CLASS_HPP
# define ASTEROID_CLASS_HPP

# include "GameEntity.Class.hpp"

class Asteroid : public GameEntity
{
private:

public:
	Asteroid();
	Asteroid(int y, int x);
	Asteroid(const Asteroid &src);
	~Asteroid();

	Asteroid     &operator= (const Asteroid &rhs);
};

#endif
