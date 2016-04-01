/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 14:58:06 by vlize             #+#    #+#             */
/*   Updated: 2016/03/30 16:05:09 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	hyperboloid_normal(t_vector3 *norm, t_obj *hit_obj, \
								t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj->crd, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->x = 2 * norm->x / hit_obj->a2;
	norm->y = 2 * norm->y / hit_obj->b2;
	norm->z = -2 * norm->z / hit_obj->c2;
	vector_rotation(norm, hit_obj, 0);
	normalise(norm);
}

static void	ellipsoid_normal(t_vector3 *norm, t_obj *hit_obj, t_vector3 *hit_pt)
{
	set_vec(norm, hit_obj->crd, hit_pt);
	vector_rotation(norm, hit_obj, 1);
	norm->x = 2 * norm->x / hit_obj->a2;
	norm->y = 2 * norm->y / hit_obj->b2;
	norm->z = 2 * norm->z / hit_obj->c2;
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
	else if (hit_obj->type == PARABOLOID)
		paraboloid_normal(norm, hit_obj, hit_pt);
	else if (hit_obj->type == HYPERBOLOID)
		hyperboloid_normal(norm, hit_obj, hit_pt);
	else if (hit_obj->type == ELLIPSOID)
		ellipsoid_normal(norm, hit_obj, hit_pt);
}

void		check_normal(t_csg *csg_lst, t_vector3 *normal, \
					t_vector3 *ori, t_obj *hit_obj)
{
	t_csg		*tmp_csg;
	t_vector3	tmp_crd;

	tmp_csg = csg_lst;
	while (tmp_csg)
	{
		if (tmp_csg->id == hit_obj->id)
		{
			vec_cpy(&tmp_crd, ori);
			csg_rotation(&tmp_crd, tmp_csg, 1);
			get_normal(normal, hit_obj, &tmp_crd);
			return (csg_rotation(normal, tmp_csg, 0));
		}
		tmp_csg = tmp_csg->next;
	}
	return (get_normal(normal, hit_obj, ori));
}
