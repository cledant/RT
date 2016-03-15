/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 14:58:06 by vlize             #+#    #+#             */
/*   Updated: 2016/03/11 11:31:53 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	plane_normal(t_vector3 *norm, t_obj *hit_obj)
{
	// n[0] = env->obj_cur->a;
	// n[1] = env->obj_cur->b;
	// n[2] = env->obj_cur->c;
	norm->x = hit_obj->crd->x;
	norm->y = hit_obj->crd->y;
	norm->z = hit_obj->crd->z;
}

static void	sphere_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	norm->x = hit_pt->x - hit_obj->crd->x;
	norm->y = hit_pt->y - hit_obj->crd->y;
	norm->z = hit_pt->z - hit_obj->crd->z;
	normalise(norm);
}

static void	cylinder_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->z = 0;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}

static void	cone_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->z = 0;
	//norm->z = tan(hit_obj->r) * hypot(norm->x, norm->y);
	// printf("%f\n", hit_obj->tan_r);
	// norm->z = hit_obj->tan_r * hypot(norm->x, norm->y);
	// if (norm->z >= 0)
	// 	norm->z *= -1;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}

void		get_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	if (hit_obj->type == PLANE)
		plane_normal(norm, hit_obj);
	else if (hit_obj->type == SPHERE)
		sphere_normal(norm, hit_obj, hit_pt);
	else if (hit_obj->type == CONE)
		cone_normal(norm, hit_obj, hit_pt);
	else if (hit_obj->type == CYLINDER)
		cylinder_normal(norm, hit_obj, hit_pt);
	// else
	// 	normal2(n, env);
	// normal_direction(n, env->ray_cur->vec);
}
