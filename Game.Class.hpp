#ifndef GAME_CLASS_HPP
# define GAME_CLASS_HPP

# include "GameEntity.Class.hpp"
# include "Player.Class.hpp"
# include "Enemy.Class.hpp"
# include "Window.Class.hpp"
# include "Asteroid.Class.hpp"
# include "Projectile.Class.hpp"
# include <cstdlib>
# include <iostream>

# define WIN	this->_window->getWin()
# define WIN_HEIGHT	this->_window->getHeight()
# define WIN_WIDTH	this->_window->getWidth()

# define PLAYER_CHAR	this->_player->getObj()
# define PLAYER_X	this->_player->getX()
# define PLAYER_Y	this->_player->getY()

# define PLAYER_START_X	10
# define PLAYER_START_Y	WIN_HEIGHT / 2

typedef struct	s_list
{
	GameEntity	*entity;
	s_list		*next;
}				t_list;

// state: 0 = main menu; 1 = game loop; 2 = death screen; 3 = pause menu;
class Game
{
private:
	Window	*_window;
	Player	*_player;
	t_list	*_enemies;
	t_list	*_projectiles;
	t_list	*_asteroids;
	int	_score;
	int	_state;
	int	_tick;
public:
	Game();
	Game(const Game &src);
	~Game();

	Game	&operator=(const Game &rhs);

	void	mainMenu();
	void	gameLoop();
	void	deathScreen();
	void	pauseMenu();

	void	restart();

	void	drawHUD();

	void	drawEntities();
	void	drawPlayer();
	void	drawEnemies();
	void	drawProjectiles();
	void	drawAsteroids();

	void	moveEnemies();
	void	moveProjectiles();
	void	moveAsteroids();

	void	spawnProjectile(Projectile *p);
	void	spawnEnemy(Enemy *e);
	void	spawnAsteroid(Asteroid *a);

	void	enemyShoot();

	void	detectCollision();

	void	displayState();

	void	setState(int state);

	void	pew(std::string sound);
};

#endif
