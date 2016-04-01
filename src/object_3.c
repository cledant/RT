/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:54:28 by vlize             #+#    #+#             */
/*   Updated: 2016/03/30 14:24:38 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	hyperboloid_0_inter(double *tmp, double *k)
{
	if (tmp[1] >= tmp[0])
		return (0);
	k[1] = DBL_MAX;
	return (1);
}

static int	hyperboloid_inters(double vec_z, double *tmp, double *k)
{
	if (tmp[1] >= tmp[0])
		return (1);
	if (k[1] != k[0])
	{
		k[3] = DBL_MAX;
		k[2] = k[1];
		k[1] = k[0];
		k[0] = -DBL_MAX;
		return (1);
	}
	if (vec_z < 0)
	{
		if (tmp[2] < 0)
			k[1] = DBL_MAX;
		else
			k[0] = -DBL_MAX;
		return (1);
	}
	if (tmp[2] < 0)
		k[0] = -DBL_MAX;
	else
		k[1] = DBL_MAX;
	return (1);
}

int			hyperboloid(t_obj *obj, t_ray *ray, double *k)
{
	t_vector3	pt0;
	t_vector3	vec;
	double		deg[3];
	double		tmp[4];

	vec_cpy(&vec, ray->vec);
	vector_rotation(&vec, obj, 1);
	set_vec(&pt0, obj->crd, ray->crd);
	vector_rotation(&pt0, obj, 1);
	tmp[0] = vec.x * vec.x;
	tmp[1] = vec.y * vec.y;
	tmp[2] = pt0.x * pt0.x;
	tmp[3] = pt0.y * pt0.y;
	deg[2] = tmp[0] / obj->a2 + tmp[1] / obj->b2 - vec.z * vec.z / obj->c2;
	deg[1] = (vec.x * pt0.x / obj->a2 + vec.y * pt0.y / obj->b2 \
			- vec.z * pt0.z / obj->c2) * 2;
	deg[0] = tmp[2] / obj->a2 + tmp[3] / obj->b2 - pt0.z * pt0.z / obj->c2 \
			+ obj->sign * obj->r2;
	tmp[1] = sqrt(tmp[0] + tmp[1]) / fabs(vec.z);
	tmp[0] = hypot(pt0.x / obj->a, pt0.y / obj->b) * obj->c;
	tmp[0] = sqrt(tmp[2] + tmp[3]) / fabs(tmp[0]);
	if (!quadratic_roots(deg, k))
		return (hyperboloid_0_inter(tmp, k));
	tmp[2] = vec.z * k[0] + pt0.z;
	return (hyperboloid_inters(vec.z, tmp, k));
}

int			ellipsoid(t_obj *obj, t_ray *ray, double *k)
{
	t_vector3	pt0;
	t_vector3	vec;
	double		deg[3];

	vec_cpy(&vec, ray->vec);
	vector_rotation(&vec, obj, 1);
	set_vec(&pt0, obj->crd, ray->crd);
	vector_rotation(&pt0, obj, 1);
	deg[2] = vec.x * vec.x / obj->a2 + vec.y * vec.y / obj->b2 \
			+ vec.z * vec.z / obj->c2;
	deg[1] = (vec.x * pt0.x / obj->a2 + vec.y * pt0.y / obj->b2
			+ vec.z * pt0.z / obj->c2) * 2;
	deg[0] = pt0.x * pt0.x / obj->a2 + pt0.y * pt0.y / obj->b2 \
			+ pt0.z * pt0.z / obj->c2 - obj->r2;
	if (!quadratic_roots(deg, k))
		return (0);
	return (1);
}
