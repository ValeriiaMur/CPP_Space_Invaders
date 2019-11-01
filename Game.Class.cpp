#include "Game.Class.hpp"

Game::Game() : _enemies(NULL), _projectiles(NULL), _asteroids(NULL), _score(0), _state(0), _tick(0)
{
	this->_window = new Window();
	while (this->_window)
		this->displayState();
}

Game::Game(const Game &src)
{
	*this = src;
}

Game::~Game()
{
}

Game	&Game::operator=(const Game &rhs)
{
	if (this != &rhs)
	{
		this->_window = rhs._window;
		this->_player = rhs._player;
		this->_score = rhs._score;
		this->_state = rhs._state;
		this->_tick = rhs._tick;
	}
	return *this;
}

void	Game::setState(int state)
{
	this->_state = state;
}

typedef struct	s_dispatch
{
	void	(Game::*f)();
}				t_dispatch;

void	Game::displayState()
{
	t_dispatch states[4] =
	{
		{&Game::mainMenu},
		{&Game::gameLoop},
		{&Game::deathScreen},
		{&Game::pauseMenu}
	};

	(this->*states[this->_state].f)();
	this->_tick++;
}

void	Game::mainMenu()
{
	// display main menu
	clear();
	attron(COLOR_PAIR(1));
	mvaddstr(WIN_HEIGHT / 2 - 3, WIN_WIDTH / 2 - 15, "<SAD SPACE INVADERS>");
	mvaddstr(WIN_HEIGHT / 2, WIN_WIDTH / 2 - 17, "Press 'SPACEBAR' to start");
	attroff(COLOR_PAIR(1));
	refresh();

	char	in;

	while (this->_window)
	{
		in = getch();
		if (in == ' ')
		{
			this->setState(1);
			this->_player = new Player;
			this->_player->setY(PLAYER_START_Y);
			this->_player->setX(PLAYER_START_X);
			break ;
		}
	}
}

void	Game::gameLoop()
{
	nodelay(stdscr, true);
	char	in;

	if (!this->_player->getLives())
	{
		this->setState(2);
		return ;
	}
	in = std::tolower(getch());
	switch (in)
	{
	case 'w':
		this->_player->moveup(WIN_HEIGHT);
		break;

	case 'a':
		this->_player->moveleft(WIN_WIDTH);
		break;

	case 'd':
		this->_player->moveright(WIN_WIDTH);
		break;

	case 's':
		this->_player->movedown(WIN_HEIGHT);
		break;

	case 27:// ESC key
		this->setState(3);
		break;

	case 'k':
		this->setState(2);
		return;

	case ' ':
		this->spawnProjectile(new Projectile('>', this->_player->getY(), this->_player->getX() + 1));
		this->pew("sounds/pew.wav");
		break;

	default:
		break;
	}

	if (this->_tick % 500 == 0)
		this->moveProjectiles();

	if (this->_tick % 800 == 0)
		this->moveEnemies();

	if (this->_tick % 1400 == 0)
		this->moveAsteroids();

	if (this->_tick % 10000 == 0)
		this->spawnEnemy(new Enemy((std::rand() % WIN_HEIGHT - 5), WIN_WIDTH - 1));

	if (this->_tick % 17000 == 0)
		this->spawnAsteroid(new Asteroid((std::rand() % WIN_HEIGHT - 5), WIN_WIDTH - 1));

	if (this->_tick % 12000 == 0)
		this->enemyShoot();

	this->detectCollision();

	clear();
	this->drawHUD();
	this->drawEntities();
	refresh();
}

void	Game::pew(std::string sound)
{
	std::string command = "afplay " + sound + " &";
	std::system(command.c_str());
}

void	Game::detectCollision()
{
	t_list	*tmp;
	t_list	*tmp2;

	// collision between player projs and enemies
	tmp = this->_projectiles;
	while (tmp)
	{
		if (tmp->entity->getVisible())
		{
			tmp2 = this->_enemies;
			while (tmp2)
			{
				if (tmp->entity->getObj() == '>')
				{
					if ((tmp->entity->getX() == tmp2->entity->getX() && tmp->entity->getY() == tmp2->entity->getY())
						|| (tmp->entity->getX() == tmp2->entity->getX() - 1 && tmp->entity->getY() == tmp2->entity->getY()))
					{
						if (tmp2->entity->getVisible())
						{
							tmp->entity->setVisible(false);
							tmp2->entity->setVisible(false);
							this->_score += 500;
						}
					}
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}

	// collision between player projs and asteroids
	tmp = this->_projectiles;
	while (tmp)
	{
		if (tmp->entity->getVisible())
		{
			tmp2 = this->_asteroids;
			while (tmp2)
			{
				if (tmp->entity->getObj() == '>')
				{
					if ((tmp->entity->getX() == tmp2->entity->getX() && tmp->entity->getY() == tmp2->entity->getY())
						|| (tmp->entity->getX() == tmp2->entity->getX() - 1 && tmp->entity->getY() == tmp2->entity->getY()))
					{
						if (tmp2->entity->getVisible())
						{
							tmp->entity->setVisible(false);
							tmp2->entity->setVisible(false);
							this->_score += 100;
						}
					}
				}
				tmp2 = tmp2->next;
			}
		}
		tmp = tmp->next;
	}

	// collision between player and enemies
	tmp = this->_enemies;
	while (tmp)
	{
		if (tmp->entity->getVisible())
		{
			if (this->_player->isTouched(tmp->entity->getY(), tmp->entity->getX()))
			{
				tmp->entity->setVisible(false);
				this->_player->loseLife(PLAYER_START_Y);
			}
		}
		tmp = tmp->next;
	}

	// collision between player and asteroids
	tmp = this->_asteroids;
	while (tmp)
	{
		if (tmp->entity->getVisible())
		{
			if (this->_player->isTouched(tmp->entity->getY(), tmp->entity->getX()))
			{
				tmp->entity->setVisible(false);
				this->_player->loseLife(PLAYER_START_Y);
				break;
			}
		}
		tmp = tmp->next;
	}

	// collision between enemy projs and player
	tmp = this->_projectiles;
	while (tmp)
	{
		if (tmp->entity->getVisible())
		{
			if (tmp->entity->getObj() == '<')
			{
				if ((this->_player->isTouched(tmp->entity->getY(), tmp->entity->getX()))
					|| (this->_player->isTouched(tmp->entity->getY(), tmp->entity->getX())))
				{
					tmp->entity->setVisible(false);
					this->_player->loseLife(this->_player->getLives() - 1);
					break;
				}
			}
		}
		tmp = tmp->next;
	}
}

void	Game::enemyShoot()
{
	t_list	*tmp;

	tmp = this->_enemies;
	while (tmp)
	{
		if (tmp->entity->getVisible())
			spawnProjectile(new Projectile('<', tmp->entity->getY(), tmp->entity->getX() - 1));
		tmp = tmp->next;
	}
}

void	Game::spawnEnemy(Enemy *e)
{
	t_list      *current;
    t_list      *node = new t_list;

	node->entity = e;
    node->next = NULL;

    if (!this->_enemies)
        this->_enemies = node;
    else
	{
        current = this->_enemies;
        while (current->next)
            current = current->next;
        current->next = node;
    }
}

void	Game::spawnAsteroid(Asteroid *a)
{
	t_list      *current;
    t_list      *node = new t_list;

	node->entity = a;
    node->next = NULL;

    if (!this->_asteroids)
        this->_asteroids = node;
    else
	{
        current = this->_asteroids;
        while (current->next)
            current = current->next;
        current->next = node;
    }
}

void	Game::spawnProjectile(Projectile *p)
{
	t_list      *current;
    t_list      *node = new t_list;

	node->entity = p;
    node->next = NULL;

    if (!this->_projectiles)
        this->_projectiles = node;
    else
	{
        current = this->_projectiles;
        while (current->next)
            current = current->next;
        current->next = node;
    }
}

void	Game::drawHUD()
{
	std::string	s;

	attron(COLOR_PAIR(1));

	mvaddstr(WIN_HEIGHT - 2, 2, "LIVES: ");// draw lives
	s = std::to_string(this->_player->getLives());
	mvaddstr(WIN_HEIGHT - 2, 9, s.c_str());

	mvaddstr(WIN_HEIGHT - 2, 11, "SCORE: ");// draw score
	s =  std::to_string(this->_score);
	mvaddstr(WIN_HEIGHT - 2, 18, s.c_str());

	attroff(COLOR_PAIR(1));
}

void	Game::drawEntities()
{
	this->drawPlayer();
	this->drawEnemies();
	this->drawProjectiles();
	this->drawAsteroids();
}

void	Game::moveProjectiles()
{
	t_list	*tmp;

	tmp = this->_projectiles;
	while (tmp)
	{
		if (tmp->entity->getObj() == '>')
			tmp->entity->setX(tmp->entity->getX() + 2);
		else
			tmp->entity->setX(tmp->entity->getX() - 2);
		tmp = tmp->next;
	}
}

void	Game::moveEnemies()
{
	t_list      *tmp;

	tmp = this->_enemies;
	while (tmp)
	{
		tmp->entity->setX(tmp->entity->getX() - 1);
		tmp = tmp->next;
	}
}

void	Game::moveAsteroids()
{
	t_list      *tmp;

	tmp = this->_asteroids;
	while (tmp)
	{
		tmp->entity->setX(tmp->entity->getX() - 1);
		tmp = tmp->next;
	}
}

void	Game::drawEnemies()
{
	t_list	*current;

	current = this->_enemies;
	while (current)
	{
		if (current->entity->getVisible())
		{
			attron(COLOR_PAIR(3));
			mvaddch(current->entity->getY(), current->entity->getX(), current->entity->getObj());
			attroff(COLOR_PAIR(3));
		}
		current = current->next;
	}
}

void	Game::drawPlayer()
{
	attron(COLOR_PAIR(2));
	mvaddch(PLAYER_Y - 1, PLAYER_X -1, PLAYER_CHAR);
	mvaddch(PLAYER_Y, PLAYER_X, PLAYER_CHAR);
	mvaddch(PLAYER_Y + 1, PLAYER_X - 1, PLAYER_CHAR);
	attroff(COLOR_PAIR(2));
}

void	Game::drawAsteroids()
{
	t_list	*current;

	current = this->_asteroids;
	while (current)
	{
		if (current->entity->getVisible())
		{
			attron(COLOR_PAIR(1));
			mvaddch(current->entity->getY(), current->entity->getX(), current->entity->getObj());
			attroff(COLOR_PAIR(1));
		}
		current = current->next;
	}
}

void	Game::drawProjectiles()
{
	t_list	*current;

	current = this->_projectiles;
	while (current)
	{
		if (current->entity->getVisible())
		{
			attron(COLOR_PAIR(1));
			mvaddch(current->entity->getY(), current->entity->getX(), current->entity->getObj());
			attroff(COLOR_PAIR(1));
		}
		current = current->next;
	}
}

void	Game::deathScreen()
{
	delete this->_player;

	char	in;
	std::string	s;

	// display death screen
	clear();
	attron(COLOR_PAIR(1));
	mvaddstr(WIN_HEIGHT / 2 - 3, WIN_WIDTH / 2 - 14, "<GAME OVER>");
	mvaddstr(WIN_HEIGHT / 2, WIN_WIDTH / 2 - 17, "Final Score: ");
	s =  std::to_string(this->_score);
	mvaddstr(WIN_HEIGHT / 2, WIN_WIDTH / 2 - 2, s.c_str());
	mvaddstr(WIN_HEIGHT / 2 + 3, WIN_WIDTH / 2 - 19, "Press 'R' to play again");
	mvaddstr(WIN_HEIGHT / 2 + 5, WIN_WIDTH / 2 - 17, "Press 'Q' to quit");
	attroff(COLOR_PAIR(1));
	refresh();

	while (this->_window)
	{
		in = std::tolower(getch());
		if (in == 'r')
		{
			this->restart();
			this->setState(1);
			break ;
		}
		else if (in == 'q')
		{
			delete this->_window;
			std::exit(1);
		}
	}
}

void	Game::pauseMenu()
{
	char	in;

	// display pause menu
	refresh();
	attron(COLOR_PAIR(1));
	mvaddstr(WIN_HEIGHT / 2 - 6, WIN_WIDTH / 2 - 15, "=PAUSE=");
	mvaddstr(WIN_HEIGHT / 2 - 4, WIN_WIDTH / 2 - 18, "<WASD> to move");
	mvaddstr(WIN_HEIGHT / 2 - 2, WIN_WIDTH / 2 - 20, "<SPACEBAR> to shoot");
	mvaddstr(WIN_HEIGHT / 2 + 3, WIN_WIDTH / 2 - 23, "Press <SPACEBAR> to resume");
	mvaddstr(WIN_HEIGHT / 2 + 5, WIN_WIDTH / 2 - 21, "Press <R> to restart");
	mvaddstr(WIN_HEIGHT / 2 + 7, WIN_WIDTH / 2 - 19, "Press <Q> to quit");
	attroff(COLOR_PAIR(1));
	refresh();

	while (this->_window)
	{
		in = std::tolower(getch());
		if (in == ' ')
			break;
		else if(in == 'r')
		{
			this->restart();
			this->setState(1);
			break;
		}
		else if (in == 'q')
		{
			delete this->_window;
			std::exit(1);
		}
	}
	this->setState(1);
}

void	Game::restart()
{
	this->_player = new Player;
	this->_player->setY(PLAYER_START_Y);
	this->_player->setX(PLAYER_START_X);
	this->_enemies = NULL;
	this->_projectiles = NULL;
	this->_asteroids = NULL;
	this->_score = 0;
	this->_tick = 0;
	refresh();
	mvaddch(PLAYER_Y, PLAYER_X, PLAYER_CHAR);
}
