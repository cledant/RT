/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:59:37 by cledant           #+#    #+#             */
/*   Updated: 2016/03/30 16:04:08 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	plane_normal(t_vector3 *norm, t_obj *hit_obj)
{
	norm->x = 0;
	norm->y = 0;
	norm->z = 1;
	vector_rotation(norm, hit_obj, 0);
}

void	sphere_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	norm->x = hit_pt->x - hit_obj->crd->x;
	norm->y = hit_pt->y - hit_obj->crd->y;
	norm->z = hit_pt->z - hit_obj->crd->z;
	normalise(norm);
}

void	cylinder_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj->crd, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->z = 0;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}

void	cone_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj->crd, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->z = (norm->x * norm->x + norm->y * norm->y) / -norm->z;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}

void	paraboloid_normal(t_vector3 *norm, t_obj *hit_obj,
				t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj->crd, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->x = 2 * norm->x / hit_obj->a2;
	norm->y = hit_obj->sign * 2 * norm->y / hit_obj->b2;
	norm->z = -1 / hit_obj->c;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}
