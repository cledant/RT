/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 14:52:54 by vlize             #+#    #+#             */
/*   Updated: 2016/03/10 10:50:24 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector3 *plane(t_obj *obj, t_ray *ray)
{
	t_vector3	vec;
	t_vector3	*hit_pt;
	float			k[2];
	float a, b, c, d;

	a = obj->ry[2];
	b = - obj->rx[2] * obj->ry[1];
	c = obj->rx[1] * obj->ry[1];
	d = - (a * obj->crd->x + b * obj->crd->y + c * obj->crd->z);
	hit_pt = (t_vector3 *)malloc(sizeof(t_vector3));
	vec_cpy(&vec, ray->crd);
	k[1] = a * ray->vec->x + b * ray->vec->y + c * ray->vec->z;
	if (fabs(k[1]) < EPSILON)
		return (NULL);
	k[0] = a * vec.x + b * vec.y + c * vec.z + d;
	if ((k[0] = - (k[0] / k[1])) < EPSILON)
		return (NULL);
	hit_pt->x = ray->vec->x * k[0] + ray->crd->x;
	hit_pt->y = ray->vec->y * k[0] + ray->crd->y;
	hit_pt->z = ray->vec->z * k[0] + ray->crd->z;
	return (hit_pt);
}

t_vector3 *sphere(t_obj *obj, t_ray *ray)
{
	t_vector3	*hit_pt;
	t_vector3 vec;
	float			deg[3];
	float			*k;

	hit_pt = (t_vector3 *)malloc(sizeof(t_vector3));
	set_vec(&vec, obj, ray->crd);
	deg[2] = ray->vec->x * ray->vec->x + ray->vec->y * ray->vec->y + ray->vec->z * ray->vec->z;
	deg[1] = ray->vec->x * vec.x + ray->vec->y * vec.y;
	deg[1] = (deg[1] + ray->vec->z * vec.z) * 2;
	deg[0] = powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) - obj->r * obj->r;
	if (!(k = find_det(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	hit_pt->x = ray->vec->x * k[0] + ray->crd->x;
	hit_pt->y = ray->vec->y * k[0] + ray->crd->y;
	hit_pt->z = ray->vec->z * k[0] + ray->crd->z;
	return (hit_pt);
}

t_vector3 *cylinder(t_obj *obj, t_ray *ray)
{
	t_vector3	*hit_pt;
	t_vector3	pt0;
	t_vector3	vec;
	float			deg[3];
	float			*k;

	hit_pt = (t_vector3 *)malloc(sizeof(t_vector3));
	vec_cpy(&vec, ray->vec);
	vector_rotation(&vec, obj, 1);
	set_vec(&pt0, obj, ray->crd);
	vector_rotation(&pt0, obj, 1);
	deg[2] = vec.x * vec.x + vec.y * vec.y;
	deg[1] = (vec.x * pt0.x + vec.y * pt0.y) * 2;
	deg[0] = pt0.x * pt0.x + pt0.y * pt0.y - obj->r * obj->r;
	if (!(k = find_det(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	hit_pt->x = vec.x * k[0] + pt0.x;
	hit_pt->y = vec.y * k[0] + pt0.y;
	hit_pt->z = vec.z * k[0] + pt0.z;
	return (rot_pt1(hit_pt, obj));
}

t_vector3 *cone(t_obj *obj, t_ray *ray)
{
	t_vector3	*hit_pt;
	t_vector3	pt0;
	t_vector3	vec;
	float			deg[3];
	float			*k;

	hit_pt = (t_vector3 *)malloc(sizeof(t_vector3));
	vec_cpy(&vec, ray->vec);
	vector_rotation(&vec, obj, 1);
	set_vec(&pt0, obj, ray->crd);
	vector_rotation(&pt0, obj, 1);
	deg[2] = vec.x * vec.x + vec.y * vec.y - vec.z * vec.z * powf(tan(obj->r * RADIAN), 2);
	deg[1] = 2 * (vec.x * pt0.x + vec.y * pt0.y - vec.z * pt0.z * powf(tan(obj->r * RADIAN), 2));
	deg[0] = pt0.x * pt0.x + pt0.y * pt0.y - pt0.z * pt0.z * powf(tan(obj->r * RADIAN), 2);
	if (!(k = find_det(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	hit_pt->x = vec.x * k[0] + pt0.x;
	hit_pt->y = vec.y * k[0] + pt0.y;
	hit_pt->z = vec.z * k[0] + pt0.z;
	return (rot_pt1(hit_pt, obj));
}
