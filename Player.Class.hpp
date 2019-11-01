/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.Class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:57:00 by valeriiamur       #+#    #+#             */
/*   Updated: 2019/10/27 21:42:11 by rcross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_CLASS_HPP
# define PLAYER_CLASS_HPP

# include <string>
# include "GameEntity.Class.hpp"

class Player : public GameEntity
{
    private:
        int _lives;
    public:
        Player();
        Player(const Player &src);
        ~Player();

        Player  &operator=(const Player &rhs);

        int getLives();

        void    loseLife(int y);

        bool    isTouched(int y, int x);
};

#endif
