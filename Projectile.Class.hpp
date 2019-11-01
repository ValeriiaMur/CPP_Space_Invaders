#ifndef PROJECTILE_CLASS_HPP
# define PROJECTILE_CLASS_HPP

# include "GameEntity.Class.hpp"

class Projectile : public GameEntity
{
private:

public:
	Projectile();
	Projectile(const Projectile &src);
	Projectile(char gameobj, int y, int x);
	~Projectile();

	Projectile	&operator=(const Projectile &rhs);
};

#endif
