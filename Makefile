# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcross <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/26 15:11:15 by valeriiamur       #+#    #+#              #
#    Updated: 2019/10/27 21:44:03 by rcross           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN =		\033[1;32m

RED =		\033[1;31m

RES =		\033[0m

#------------------------------------------------------------------------------#

NAME	:=	ft_retro
DNAME	:=	d_$(NAME)

CC		:=	clang++

CFLAGS	:=	-Wall -Wextra -Werror -lncurses
DFLAGS	:=	-Wall -Wextra -g

FILES	:=	main.cpp\
			Game.Class.cpp\
			Window.Class.cpp\
			GameEntity.Class.cpp\
			Player.Class.cpp\
			Enemy.Class.cpp\
			Projectile.Class.cpp\
			Asteroid.Class.cpp\

$(NAME):
	@$(CC) $(CFLAGS) $(FILES) -o $(NAME)
	@echo "[$(GREEN)$@$(RES)] compiled."

all: $(NAME)

d:	dclean
	@$(CC) $(DFLAGS) $(FILES) -o $(DNAME)
	@echo "[$(GREEN)$(DNAME)$(RES)] compiled."

clean:
	@rm -f $(NAME)
	@echo "[$(GREEN)$(NAME)$(RES)] removed."

dclean:
	@rm -rf $(DNAME) $(DNAME).dSYM/
	@echo "[$(GREEN)$(DNAME)$(RES)] removed."

re: clean all

.PHONY: all d clean dclean re
