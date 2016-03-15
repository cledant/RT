/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:18:18 by vlize             #+#    #+#             */
/*   Updated: 2016/03/11 11:16:48 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector3	*refle_vec(t_vector3 *normal, t_vector3 *src_vec)
{
	t_vector3 *refle;
	float	dot_product;

	refle = (t_vector3*)malloc(sizeof(t_vector3));
	dot_product = src_vec->x * normal->x + src_vec->y * normal->y +
		src_vec->z * normal->z;
	refle->x = src_vec->x - 2 * dot_product * normal->x;
	refle->y = src_vec->y - 2 * dot_product * normal->y;
	refle->z = src_vec->z - 2 * dot_product * normal->z;
	normalise(refle);
	return (refle);
}

float	*find_det(float a, float b, float c)
{
	static float	result[2];
	float			delta;
	float			k[2];

	delta = powf(b, 2) - (a * c * 4);
	if (delta < 0)
		return (NULL);
	k[0] = 2 * a;
	k[1] = 0 - b;
	delta = sqrtf(delta);
	result[0] = (k[1] + delta) / k[0];
	result[1] = (k[1] - delta) / k[0];
	return (result);
}

void	vec_cpy(t_vector3 *dst, t_vector3 *src)
{
	if (!dst || !src)
		return ;
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

void	set_vec(t_vector3 *vec, t_obj *obj, t_vector3 *crd)
{
	if (obj && vec && crd)
	{
		vec->x = crd->x - obj->crd->x;
		vec->y = crd->y - obj->crd->y;
		vec->z = crd->z - obj->crd->z;
	}
}

t_vector3	*rot_pt1(t_vector3 *pt1, t_obj *obj)
{
	if (!pt1 || !obj)
		return (pt1);
	vector_rotation(pt1, obj, 0);
	pt1->x += obj->crd->x;
	pt1->y += obj->crd->y;
	pt1->z += obj->crd->z;
	return (pt1);
}

void	normal_direction(float *n, t_vector3 *vec)
{
	float	k;

	k = (vec->x * n[0]) + (vec->y * n[1]) + (vec->z * n[2]);
	if (k <= 0)
		return ;
	n[0] = - n[0];
	n[1] = - n[1];
	n[2] = - n[2];
}
