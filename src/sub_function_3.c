/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_function_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:03:20 by cledant           #+#    #+#             */
/*   Updated: 2016/03/30 18:06:22 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			seek_uv_plane(t_hit_pt *hit_pt, t_obj *obj,
		double *x, double *y)
{
	t_vector3	int_coord;
	double		size;

	size = obj->tex->size;
	int_coord.z = hit_pt->crd->z;
	int_coord.x = hit_pt->crd->x;
	int_coord.y = hit_pt->crd->y;
	vector_rotation(&int_coord, obj, 1);
	if (int_coord.x < 0)
		*x = (fmod(int_coord.x, size) + size);
	else
		*x = fmod(int_coord.x, size);
	if (int_coord.y < 0)
		*y = (fmod(int_coord.y, size) + size);
	else
		*y = fmod(int_coord.y, size);
}

void			seek_uv_plane_img(t_hit_pt *hit_pt,
		t_obj *obj, double (*uv)[4])
{
	t_vector3	int_coord;

	int_coord.z = hit_pt->crd->z;
	int_coord.x = hit_pt->crd->x;
	int_coord.y = hit_pt->crd->y;
	vector_rotation(&int_coord, obj, 1);
	int_coord.x = int_coord.x / obj->size_x + obj->tr_x;
	int_coord.y = int_coord.y / obj->size_y + obj->tr_y;
	if (int_coord.x < -0.001)
		(*uv)[2] = (fmod(int_coord.x, (*uv)[0]) + (*uv)[0]);
	else
		(*uv)[2] = fmod(int_coord.x, (*uv)[0]);
	if (int_coord.y < -0.001)
		(*uv)[3] = (fmod(int_coord.y, (*uv)[1]) + (*uv)[1]);
	else
		(*uv)[3] = fmod(int_coord.y, (*uv)[1]);
}

void			seek_uv_sph(t_hit_pt *hit_pt, t_obj *obj,
		double *u, double *v)
{
	t_vector3	vec;

	vec.x = hit_pt->crd->x - obj->crd->x;
	vec.y = hit_pt->crd->y - obj->crd->y;
	vec.z = hit_pt->crd->z - obj->crd->z;
	normalise(&vec);
	vector_rotation(&vec, obj, 1);
	*u = 0.5 + (atan2(vec.x, vec.z) / PI2);
	*v = 0.5 - (asin(vec.y) / M_PI);
}

void			seek_uv_cyl_cone(t_hit_pt *hit_pt, t_obj *obj,
		double *u, double *v)
{
	t_vector3	vec;
	t_vector3	vec2;
	t_vector3	tmp;
	t_vector3	test;
	double		size;

	size = obj->tex->size * 16;
	vec_cpy(&test, obj->crd);
	vec_cpy(&tmp, hit_pt->crd);
	vector_rotation(&tmp, obj, 1);
	vector_rotation(&test, obj, 1);
	vec.x = tmp.x - test.x;
	vec.y = tmp.y - test.y;
	vec.z = 0;
	vec2.x = 0;
	vec2.y = 0;
	vec2.z = tmp.z;
	*u = 0.5 + (atan2(vec.y, vec.x) / PI2);
	if (vec2.z < 0)
		*v = (fmod(vec2.z, size) + size) / size;
	else
		*v = fmod(vec2.z, size) / size;
}

void			seek_uv_cyl_cone_img(t_hit_pt *hit_pt, t_obj *obj,
		double (*uv)[4], int width)
{
	t_vector3	vec;
	t_vector3	vec2;
	t_vector3	tmp;
	t_vector3	test;
	float		size;

	size = width * obj->size_z;
	vec_cpy(&test, obj->crd);
	vec_cpy(&tmp, hit_pt->crd);
	vector_rotation(&tmp, obj, 1);
	vector_rotation(&test, obj, 1);
	vec.x = tmp.x - test.x;
	vec.y = tmp.y - test.y;
	vec.z = 0;
	vec2.x = 0;
	vec2.y = 0;
	vec2.z = tmp.z + obj->tr_z;
	(*uv)[0] = 0.5 + (atan2(vec.y, vec.x) / PI2);
	if (vec2.z <= 0)
		(*uv)[1] = 1 - (fmod(vec2.z, size) + size) / size;
	else
		(*uv)[1] = 1 - fmod(vec2.z, size) / size;
}
