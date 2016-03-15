/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:40:22 by cledant           #+#    #+#             */
/*   Updated: 2016/03/14 20:16:35 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_checker_xy(double int_coord[3])
{
	double	x;
	double	y;
	double	size;
	int		color_1;
	int		color_2;

	color_1 = 0x00FF0000;
	color_2 = 0x00FFFFFF;
	size = 2;
	if (int_coord[0] < 0)
		int_coord[0] = -int_coord[0] + size / 2;
	if (int_coord[1] < 0)
		int_coord[1] = -int_coord[1] + size / 2;
	x = fmod(int_coord[0], size);
	y = fmod(int_coord[1], size);
	if ((x >= 0 && x <= size / 2) && (y >= 0 && y <= size / 2))
		return (color_1);
	else if ((x > size / 2  && x <= size) && (y >= 0 && y <= size / 2))
		return (color_2);
	else if ((x >= 0 && x <= size / 2) && (y > size / 2 && y <= size))
		return (color_2);
	else
		return (color_1);
}
