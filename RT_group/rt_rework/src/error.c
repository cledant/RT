/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibautpierron <thibautpierron@student.42.fr>+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:54:26 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/06 11:41:07 by thibautpierron   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void malloc_error()
{
  ft_putstr("Malloc error");
  exit(0);
}

void	arg_error(int ac)
{
	if (ac < 2)
    ft_putstr("File name missing");
	else if (ac > 2)
    ft_putstr("Too many arguments");
	exit(0);
}
