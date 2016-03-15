/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_int_cone_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 12:21:57 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:32:14 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_calc_var(t_cone *cone, t_light *camera,
					double cur_dir[3], double (*var)[3])
{
	(*var)[0] = ((cur_dir[0] * cur_dir[0]) + (cur_dir[1] * cur_dir[1]) +
		(cur_dir[2] * cur_dir[2])) - ((((cur_dir[0] * cone->dir[0]) +
		(cur_dir[1] * cone->dir[1]) + (cur_dir[2] * cone->dir[2])) *
		((cur_dir[0] * cone->dir[0]) + (cur_dir[1] * cone->dir[1]) +
		(cur_dir[2] * cone->dir[2]))) * (1 + cone->k * cone->k));
	(*var)[1] = 2 * ((cur_dir[0] * -(camera->coord[0] - cone->coord[0]) +
		cur_dir[1] * -(camera->coord[1] - cone->coord[1]) + cur_dir[2] *
		-(camera->coord[2] - cone->coord[2])) - ((((cur_dir[0] * cone->dir[0]) +
		(cur_dir[1] * cone->dir[1]) + (cur_dir[2] * cone->dir[2])) *
		((cone->dir[0] * -(camera->coord[0] - cone->coord[0]) +
		cone->dir[1] * -(camera->coord[1] - cone->coord[1]) + cone->dir[2] *
		-(camera->coord[2] - cone->coord[2])))) * (1 + cone->k * cone->k)));
	(*var)[2] = ((camera->coord[0] - cone->coord[0]) * (camera->coord[0] -
		cone->coord[0]) + (camera->coord[1] - cone->coord[1]) *
		(camera->coord[1] - cone->coord[1]) + (camera->coord[2] -
		cone->coord[2]) * (camera->coord[2] - cone->coord[2])) - (cone->radius *
		cone->radius) - (((cone->dir[0] * -(camera->coord[0] - cone->coord[0]) +
		cone->dir[1] * -(camera->coord[1] - cone->coord[1]) + cone->dir[2] *
		-(camera->coord[2] - cone->coord[2])) * (cone->dir[0] *
		-(camera->coord[0] - cone->coord[0]) + cone->dir[1] *
		-(camera->coord[1] - cone->coord[1]) + cone->dir[2] *
		-(camera->coord[2] - cone->coord[2]))) * (1 + cone->k * cone->k));
}

static int		ft_compare_length(double var[3], double length[2], double det,
					double *dist)
{
	if (var[0] == 0)
		return (0);
	length[0] = (-var[1] + sqrt(det)) / (2 * var[0]);
	length[1] = (-var[1] - sqrt(det)) / (2 * var[0]);
	if (length[1] < length[0] && length[1] < *dist)
	{
		if (length[1] < 0)
			return (0);
		else
		{
			*dist = length[1];
			return (1);
		}
	}
	else if (length[0] < *dist)
	{
		if (length[0] < 0)
			return (0);
		else
		{
			*dist = length[0];
			return (1);
		}
	}
	return (0);
}

int				ft_calc_int_cone_light(t_cone *cone, t_light *camera,
					double cur_dir[3], double *dist)
{
	double		var[3];
	double		det;
	double		length[2];

	ft_calc_var(cone, camera, cur_dir, &var);
	det = var[1] * var[1] - (4 * var[0] * var[2]);
	if (det < 0)
		return (0);
	else if (det == 0)
	{
		if (var[0] == 0)
			return (0);
		length[0] = (-var[1] / (2 * var[0]));
		if (length[0] < *dist)
		{
			if (length[0] < 0)
				return (0);
			*dist = length[0];
			return (1);
		}
		return (0);
	}
	else
		return (ft_compare_length(var, length, det, dist));
}
