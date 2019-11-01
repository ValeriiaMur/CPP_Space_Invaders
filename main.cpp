/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:58:59 by valeriiamur       #+#    #+#             */
/*   Updated: 2019/10/27 23:07:03 by rcross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.Class.hpp"

#include <ncurses.h>
#include <iostream>
#include <string>

int main(void)
{
    Game    *game = new Game;

    delete game;

    return (0);
}
