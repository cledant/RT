/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_light_interrupt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/27 10:23:36 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:39:57 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_init_val(double vector[3], double *norm,
		double (*norm_light)[3], double *dist)
{
	*dist = 1000000;
	*norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] +
			vector[2] * vector[2]);
	(*norm_light)[0] = -vector[0] / *norm;
	(*norm_light)[1] = -vector[1] / *norm;
	(*norm_light)[2] = -vector[2] / *norm;
}

int				ft_is_light_interrupt(t_light *light, t_list *list,
					double int_coord[3])
{
	double	vector[3];
	double	norm;
	double	norm_light[3];
	double	dist;

	vector[0] = int_coord[0] - light->coord[0];
	vector[1] = int_coord[1] - light->coord[1];
	vector[2] = int_coord[2] - light->coord[2];
	ft_init_val(vector, &norm, &norm_light, &dist);
	if (list->content_size == 0)
		ft_calc_int_sphere_light(list->content, light, norm_light, &dist);
	else if (list->content_size == 1)
		ft_calc_int_plane_light(list->content, light, norm_light, &dist);
	else if (list->content_size == 2)
		ft_calc_int_cylinder_light(list->content, light, norm_light, &dist);
	else if (list->content_size == 3)
		ft_calc_int_cone_light(list->content, light, norm_light, &dist);
	if (dist < norm)
		return (1);
	else
		return (0);
}
