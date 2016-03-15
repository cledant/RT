/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_has_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 19:31:01 by cledant           #+#    #+#             */
/*   Updated: 2016/02/26 18:41:54 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		ft_plane_has_int(t_plane *plane, t_light *light, double int_coord[3])
{
	double	norm;
	double	norm_vec[3];
	double	angle;
	double	light_vec[3];
	double	norm_light_vec[3];
	double	dist;

	dist = 1000000;
//	norm = sqrt(plane->coord[0] * plane->coord[0] + plane->coord[1] *
//			plane->coord[1] + plane->coord[2] * plane->coord[2]);
//	norm_vec[0] = plane->coord[0] / norm;
//	norm_vec[1] = plane->coord[1] / norm;
//	norm_vec[2] = plane->coord[2] / norm;
	light_vec[0] = light->coord[0] - int_coord[0];
	light_vec[1] = light->coord[1] - int_coord[1];
	light_vec[2] = light->coord[2] - int_coord[2];
	norm = sqrt(light_vec[0] * light_vec[0] + light_vec[1] *
			light_vec[1] + light_vec[2] * light_vec[2]);
	norm_light_vec[0] = light_vec[0] / norm;
	norm_light_vec[1] = light_vec[1] / norm;
	norm_light_vec[2] = light_vec[2] / norm;
	ft_calc_int_plane_light(plane, light, norm_light_vec, &dist);
	if (norm < dist)
		return (0);
	else
		return (1);
}
