/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_object2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/09 14:54:28 by vlize             #+#    #+#             */
/*   Updated: 2016/03/04 10:12:32 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	*ft_tore(t_obj *obj, t_ray *ray)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, ray->vec);
	ft_rot_v0_pt0(v0, pt0, obj, ray->crd);
	deg[2] = v0[3] * pt0[3] + v0[4] * pt0[4] + v0[5] * pt0[5];
	deg[1] = -2 * obj->rt * sqrtf(v0[3] * pt0[3] + v0[4] * pt0[4]);
	deg[0] = obj->pow2_rt * obj->pow2_r;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_paraboloid(t_obj *obj, t_ray *ray)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, ray->vec);
	ft_rot_v0_pt0(v0, pt0, obj, ray->crd);
	deg[2] = v0[3] / obj->pow2_a + obj->sign * v0[4] / obj->pow2_b;
	deg[1] = v0[0] * pt0[0] / obj->pow2_a;
	deg[1] += obj->sign * v0[1] * pt0[1] / obj->pow2_b;
	deg[1] = deg[1] * 2 - v0[2] / obj->c;
	deg[0] = pt0[3] / obj->pow2_a + obj->sign * pt0[4] / obj->pow2_b;
	deg[0] -= pt0[2] / obj->c;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_hyperboloid(t_obj *obj, t_ray *ray)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, ray->vec);
	ft_rot_v0_pt0(v0, pt0, obj, ray->crd);
	deg[2] = v0[3] / obj->pow2_a + v0[4] / obj->pow2_b - v0[5] / obj->pow2_c;
	deg[1] = v0[0] * pt0[0] / obj->pow2_a + v0[1] * pt0[1] / obj->pow2_b;
	deg[1] = (deg[1] - v0[2] * pt0[2] / obj->pow2_c) * 2;
	deg[0] = pt0[3] / obj->pow2_a + pt0[4] / obj->pow2_b;
	deg[0] += obj->sign * obj->pow2_r - pt0[5] / obj->pow2_c;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_ellipsoid(t_obj *obj, t_ray *ray)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[3];
	float			*k;

	ft_set_v0(v0, ray->vec);
	ft_rot_v0_pt0(v0, pt0, obj, ray->crd);
	deg[2] = v0[3] / obj->pow2_a + v0[4] / obj->pow2_b + v0[5] / obj->pow2_c;
	deg[1] = v0[0] * pt0[0] / obj->pow2_a + v0[1] * pt0[1] / obj->pow2_b;
	deg[1] = (deg[1] + v0[2] * pt0[2] / obj->pow2_c) * 2;
	deg[0] = pt0[3] / obj->pow2_a + pt0[4] / obj->pow2_b;
	deg[0] += pt0[5] / obj->pow2_c - obj->pow2_r;
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}

float	*ft_mobius_strip(t_obj *obj, t_ray *ray)
{
	static float	pt1[3];
	float			pt0[6];
	float			v0[6];
	float			deg[4];
	float			*k;

	ft_set_v0(v0, ray->vec);
	ft_rot_v0_pt0(v0, pt0, obj, ray->crd);
	deg[3] = v0[4] * (v0[1] - 2 * v0[2]) + v0[1] * (v0[0] + v0[2]);
	deg[3] -= 2 * (v0[3] * v0[2]);
	deg[0] = pt0[0] * v0[0] - pt0[2] + v0[2];
	deg[2] = v0[1] * deg[0] - v0[3] * (pt0[2] + v0[2]) + v0[0] * v0[2];
	deg[2] = 2 * deg[2] + pt0[1] * (3 * v0[4] + v0[3] - v0[5]);
	deg[1] = pt0[1] * deg[0] - v0[2] * (pt0[3] + pt0[0] + pt0[4]);
	deg[1] -= pt0[2] * v0[0] * (2 * pt0[0] + 1);
	deg[1] = 2 * deg[1] + v0[2] * (3 * pt0[4] + pt0[3] + pt0[5] - obj->pow2_a);
	deg[0] = pt0[4] * (pt0[1] - 2 * pt0[2]);
	deg[0] += pt0[1] * (pt0[3] + pt0[5] - obj->pow2_a);
	deg[0] -= 2 * pt0[0] * pt0[2] * (pt0[0] + 1);
	if (!(k = ft_quadratic_equation(deg[2], deg[1], deg[0])))
		return (NULL);
	if ((k[0] > k[1]) && (k[1] >= EPSILON))
		k[0] = k[1];
	if (k[0] < EPSILON)
		return (NULL);
	pt1[0] = v0[0] * k[0] + pt0[0];
	pt1[1] = v0[1] * k[0] + pt0[1];
	pt1[2] = v0[2] * k[0] + pt0[2];
	return (ft_rot_pt1(pt1, obj));
}
