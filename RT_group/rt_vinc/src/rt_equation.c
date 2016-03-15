/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_equation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 09:42:26 by vlize             #+#    #+#             */
/*   Updated: 2016/02/15 11:37:11 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	*ft_quadratic_equation(float a, float b, float c)
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

void	ft_rotation_matrix(float *absc, float *ord, float angle[3], int neg)
{
	float	k;

	if (!absc || !ord || !angle)
		return ;
	k = (*absc);
	if (neg)
	{
		*absc = k * angle[1] + (*ord) * angle[2];
		*ord = (*ord) * angle[1] - k * angle[2];
		return ;
	}
	*absc = k * angle[1] - (*ord) * angle[2];
	*ord = (*ord) * angle[1] + k * angle[2];
}

void	ft_vector_rotation(float v[3], t_crd *crd, t_obj *obj, int neg)
{
	if (!obj)
		return ;
	if (crd)
	{
		v[0] = crd->x - obj->crd->x;
		v[1] = crd->y - obj->crd->y;
		v[2] = crd->z - obj->crd->z;
	}
	if (neg)
	{
		ft_rotation_matrix(&v[0], &v[1], obj->rz, neg);
		ft_rotation_matrix(&v[2], &v[0], obj->ry, neg);
		ft_rotation_matrix(&v[1], &v[2], obj->rx, neg);
		return ;
	}
	ft_rotation_matrix(&v[1], &v[2], obj->rx, neg);
	ft_rotation_matrix(&v[2], &v[0], obj->ry, neg);
	ft_rotation_matrix(&v[0], &v[1], obj->rz, neg);
}

void	ft_vector_equation(t_obj *obj)
{
	if (!obj)
		return ;
	obj->a = obj->ry[2];
	obj->b = 0 - (obj->rx[2] * obj->ry[1]);
	obj->c = obj->rx[1] * obj->ry[1];
	obj->d = 0 - (obj->a * obj->crd->x + obj->b * obj->crd->y + obj->c * obj->crd->z);
	obj->pow2_a = powf(obj->a, 2);
	obj->pow2_b = powf(obj->b, 2);
	obj->pow2_c = powf(obj->c, 2);
}
