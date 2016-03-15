/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_difflight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 18:26:32 by cledant           #+#    #+#             */
/*   Updated: 2016/02/22 18:57:12 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		ft_plane_difflight(t_plane *obj, t_light *light, double int_coord[3])
{
	double	vector[3];
	double	norm;
	double	norm_vec_light[3];
	double	norm_vec_normal[3];
	double	angle;

	vector[0] = int_coord[0] - light->coord[0];
	vector[1] = int_coord[1] - light->coord[1];
	vector[2] = int_coord[2] - light->coord[2];
	norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + 
			vector[2] * vector[2]);
	norm_vec_light[0] = vector[0] / norm;
	norm_vec_light[1] = vector[1] / norm;
	norm_vec_light[2] = vector[2] / norm;
	vector[0] = obj->coord[0];
	vector[1] = obj->coord[1];
	vector[2] = obj->coord[2];
	norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + 
			vector[2] * vector[2]);
	norm_vec_normal[0] = vector[0] / norm;
	norm_vec_normal[1] = vector[1] / norm;
	norm_vec_normal[2] = vector[2] / norm;
	angle = norm_vec_normal[0] * norm_vec_light[0] + 
				norm_vec_normal[1] * norm_vec_light[1] +
					norm_vec_normal[2] * norm_vec_light[2];
	if (angle < 0)
		return (0x00000000);
	else
		return (light->color * obj->diffuse * angle);
}
