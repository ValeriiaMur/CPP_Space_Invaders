/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Window.Class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcross <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:54:45 by valeriiamur       #+#    #+#             */
/*   Updated: 2019/10/27 03:06:16 by rcross           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_CLASS_HPP
# define WINDOW_CLASS_HPP

#include <ncurses.h>
#include <iostream>
#include <string>
#include <unistd.h>

class Window
{
    public:

        Window();
        Window(const Window &src);
        ~Window();

        Window  &operator=(const Window &rhs);

        int getWidth();
        int getHeight();
        WINDOW *getWin();

    private:
        int _width;
        int _height;
        WINDOW *_w;
};

#endif
