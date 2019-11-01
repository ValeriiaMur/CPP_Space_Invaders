/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEntity.Class.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:57:11 by valeriiamur       #+#    #+#             */
/*   Updated: 2019/10/27 21:44:33 by rcross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEENTITY_CLASS_HPP
# define GAMEENTITY_CLASS_HPP

#include <string>

//this is a base class for the rest
class GameEntity
{
    protected:
        char    _gameObj;
        int _current_y;
	    int _current_x;
        bool    _visible;

    public:
        //constructors and destructors
        GameEntity();
        GameEntity(const GameEntity &src);
        GameEntity(char gameObj);
        GameEntity(char gameObj, int y, int x);
        virtual ~GameEntity();

        GameEntity &operator=(const GameEntity &rhs);
        //move
        void moveleft(int max);
        void moveright(int max);
        void moveup(int max);
        void movedown(int max);

        char    getObj();
        int getX();
        int getY();
        bool    getVisible();
        // virtual bool    getBool();// only for projectile class

        void    setX(int x);
        void    setY(int y);
        void    setVisible(bool b);
};

#endif
