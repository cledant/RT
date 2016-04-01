/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 13:50:14 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:26:21 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_color	*average_color(t_color *dst, int divi)
{
	dst->r /= divi;
	dst->g /= divi;
	dst->b /= divi;
	return (dst);
}

void	add_color(t_color *dst, t_color *col, int fre)
{
	dst->r += col->r;
	dst->g += col->g;
	dst->b += col->b;
	if (fre)
		free(col);
}

void	color_init_null(t_color *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	cap_color(t_color *color)
{
	if (color->r > 1)
		color->r = 1;
	if (color->g > 1)
		color->g = 1;
	if (color->b > 1)
		color->b = 1;
}
