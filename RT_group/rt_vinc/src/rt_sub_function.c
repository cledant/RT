/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sub_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:18:18 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 08:39:48 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_set_v0(float *v0, t_vec *vec)
{
	if (!v0 || !vec)
		return ;
	v0[0] = vec->x;
	v0[1] = vec->y;
	v0[2] = vec->z;
}

void	ft_set_pt0(float *pt0, t_obj *obj, t_crd *crd)
{
	if (!pt0 || !crd)
		return ;
	if (obj)
	{
		pt0[0] = crd->x - obj->crd->x;
		pt0[1] = crd->y - obj->crd->y;
		pt0[2] = crd->z - obj->crd->z;
		return ;
	}
	pt0[0] = crd->x;
	pt0[1] = crd->y;
	pt0[2] = crd->z;
}

void	ft_rot_v0_pt0(float *v0, float *pt0, t_obj *obj, t_crd *crd)
{
	if (!v0 || !pt0 || !obj || !crd)
		return ;
	ft_vector_rotation(v0, NULL, obj, 1);
	ft_vector_rotation(pt0, crd, obj, 1);
	v0[3] = powf(v0[0], 2);
	v0[4] = powf(v0[1], 2);
	v0[5] = powf(v0[2], 2);
	pt0[3] = powf(pt0[0], 2);
	pt0[4] = powf(pt0[1], 2);
	pt0[5] = powf(pt0[2], 2);
}

float	*ft_rot_pt1(float *pt1, t_obj *obj)
{
	if (!pt1 || !obj)
		return (pt1);
	ft_vector_rotation(pt1, NULL, obj, 0);
	pt1[0] += obj->crd->x;
	pt1[1] += obj->crd->y;
	pt1[2] += obj->crd->z;
	return (pt1);
}

void	ft_normal_direction(float *n, t_vec *vec)
{
	float	k;

	k = (vec->x * n[0]) + (vec->y * n[1]) + (vec->z * n[2]);
	if (k <= 0)
		return ;
	n[0] = 0 - n[0];
	n[1] = 0 - n[1];
	n[2] = 0 - n[2];
}
