/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:18:18 by vlize             #+#    #+#             */
/*   Updated: 2016/03/30 18:09:10 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	dot_product(t_vector3 *v1, t_vector3 *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector3		*refle_vec(t_vector3 *normal, t_vector3 *src_vec)
{
	t_vector3	*refle;
	double		dot_produc;

	if (!(refle = (t_vector3*)malloc(sizeof(t_vector3))))
		malloc_error();
	dot_produc = dot_product(src_vec, normal);
	refle->x = src_vec->x - 2 * dot_produc * normal->x;
	refle->y = src_vec->y - 2 * dot_produc * normal->y;
	refle->z = src_vec->z - 2 * dot_produc * normal->z;
	normalise(refle);
	return (refle);
}

t_vector3		*refre_vec(t_vector3 *normal, t_vector3 *incident,
		double ind_prev, double ind_next)
{
	t_vector3	*refre;
	double		dot_produc;
	double		n;

	n = ind_prev / ind_next;
	if (n == 1.0)
		return (incident);
	dot_produc = dot_product(normal, incident);
	if (!(refre = (t_vector3*)malloc(sizeof(t_vector3))))
		malloc_error();
	refre->x = (n * incident->x) + (n * dot_produc - sqrtf(1 - n * n *
				(1 - dot_produc * dot_produc))) * normal->x;
	refre->y = (n * incident->y) + (n * dot_produc - sqrtf(1 - n * n *
				(1 - dot_produc * dot_produc))) * normal->y;
	refre->z = (n * incident->z) + (n * dot_produc - sqrtf(1 - n * n *
				(1 - dot_produc * dot_produc))) * normal->z;
	normalise(refre);
	return (refre);
}

void			vec_cpy(t_vector3 *dst, t_vector3 *src)
{
	if (!dst || !src)
		seg_fault();
	dst->x = src->x;
	dst->y = src->y;
	dst->z = src->z;
}

double			get_dist(t_vector3 *p1, t_vector3 *p2)
{
	return (sqrt(powf(p1->x - p2->x, 2) + powf(p1->y - p2->y, 2) \
				+ powf(p1->z - p2->z, 2)));
}
