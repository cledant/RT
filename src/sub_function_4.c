/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_function_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:07:17 by cledant           #+#    #+#             */
/*   Updated: 2016/03/31 15:34:29 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			set_vec(t_vector3 *vec, t_vector3 *p1, t_vector3 *p2)
{
	vec->x = p2->x - p1->x;
	vec->y = p2->y - p1->y;
	vec->z = p2->z - p1->z;
}

t_vector3		*rot_pt1(t_vector3 *pt1, t_obj *obj)
{
	if (!pt1 || !obj)
		seg_fault();
	vector_rotation(pt1, obj, 0);
	pt1->x += obj->crd->x;
	pt1->y += obj->crd->y;
	pt1->z += obj->crd->z;
	return (pt1);
}

void			small_malloc(t_ray *light_ray)
{
	if (!(light_ray->crd = (t_vector3*)malloc(sizeof(t_vector3))))
		malloc_error();
	if (!(light_ray->vec = (t_vector3*)malloc(sizeof(t_vector3))))
		malloc_error();
}
