/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 18:06:02 by vlize             #+#    #+#             */
/*   Updated: 2016/03/28 10:01:54 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		make_tmp_ray(t_ray *tmp_ray, t_vector3 *vec, \
						t_vector3 *crd, t_vector3 *ori)
{
	if (!tmp_ray || !vec || !crd || !ori)
		seg_fault();
	if (!(tmp_ray->vec = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	if (!(tmp_ray->crd = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	vec_cpy(tmp_ray->vec, vec);
	set_vec(tmp_ray->crd, ori, crd);
}

t_vector3	*new_point(t_vector3 *pt, t_vector3 *vec, t_vector3 *crd, double k)
{
	if (!vec || !crd)
		seg_fault();
	if (!pt && !(pt = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	pt->x = vec->x * k + crd->x;
	pt->y = vec->y * k + crd->y;
	pt->z = vec->z * k + crd->z;
	return (pt);
}

t_interval	*new_interval(double *k, t_obj *obj)
{
	t_interval	*i;

	if (!(i = (t_interval *)malloc(sizeof(t_interval))))
		malloc_error();
	i->next = NULL;
	if (!k || !obj)
		return (i);
	i->min = k[0];
	i->max = k[1];
	i->obj_max = obj;
	i->obj_min = obj;
	return (i);
}

t_node		*new_node(int type)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		malloc_error();
	node->type = type;
	node->obj = NULL;
	node->fork1 = NULL;
	node->fork2 = NULL;
	return (node);
}

t_csg		*new_csg(int id)
{
	t_csg	*csg;

	if (!(csg = (t_csg *)malloc(sizeof(t_csg))))
		malloc_error();
	csg->id = id;
	csg->scale = 100;
	csg->crd = NULL;
	csg->tree = NULL;
	csg->next = NULL;
	return (csg);
}
