/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_norm_vec_cone.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 10:37:43 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:34:28 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_next(double (*norm_vec)[2][3])
{
	double	norm;

	norm = sqrt((*norm_vec)[1][0] * (*norm_vec)[1][0] + (*norm_vec)[1][1] *
		(*norm_vec)[1][1] + (*norm_vec)[1][2] * (*norm_vec)[1][2]);
	(*norm_vec)[1][0] = (*norm_vec)[1][0] / norm;
	(*norm_vec)[1][1] = (*norm_vec)[1][1] / norm;
	(*norm_vec)[1][2] = (*norm_vec)[1][2] / norm;
}

void			ft_calc_norm_vec_cone(t_cone *obj, double (*norm_vec)[2][3],
					double int_coord[3], t_light *light)
{
	double	vector[3];
	double	norm;
	double	tmp_norm;

	vector[0] = int_coord[0] - light->coord[0];
	vector[1] = int_coord[1] - light->coord[1];
	vector[2] = int_coord[2] - light->coord[2];
	norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] +
		vector[2] * vector[2]);
	(*norm_vec)[0][0] = vector[0] / norm;
	(*norm_vec)[0][1] = vector[1] / norm;
	(*norm_vec)[0][2] = vector[2] / norm;
	tmp_norm = (((*norm_vec)[0][0] * obj->dir[0] * norm + (*norm_vec)[0][1] *
		obj->dir[1] * norm + (*norm_vec)[0][2] * obj->dir[2] * norm)) +
		(((light->coord[0] - obj->coord[0]) * obj->dir[0]) + ((light->coord[1] -
		obj->coord[1]) * obj->dir[1]) + ((light->coord[2] - obj->coord[2])
		* obj->dir[2]));
	(*norm_vec)[1][0] = int_coord[0] - obj->coord[0] - ((obj->dir[0] *
		tmp_norm) * (1 + obj->k * obj->k));
	(*norm_vec)[1][1] = int_coord[1] - obj->coord[1] - ((obj->dir[1] *
		tmp_norm) * (1 + obj->k * obj->k));
	(*norm_vec)[1][2] = int_coord[2] - obj->coord[2] - ((obj->dir[2] *
		tmp_norm) * (1 + obj->k * obj->k));
	ft_next(norm_vec);
}
