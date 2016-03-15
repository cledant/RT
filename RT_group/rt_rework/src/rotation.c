/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 09:42:26 by vlize             #+#    #+#             */
/*   Updated: 2016/03/09 19:31:19 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotation_matrix(float *absc, float *ord, float angle[3], int neg)
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

void	vector_rotation(t_vector3 *vec, t_obj *obj, int neg)
{
	if (neg)
	{
		rotation_matrix(&vec->x, &vec->y, obj->rz, neg);
		rotation_matrix(&vec->z, &vec->x, obj->ry, neg);
		rotation_matrix(&vec->y, &vec->z, obj->rx, neg);
	}
	else
	{
		rotation_matrix(&vec->y, &vec->z, obj->rx, neg);
		rotation_matrix(&vec->z, &vec->x, obj->ry, neg);
		rotation_matrix(&vec->x, &vec->y, obj->rz, neg);
	}
}

void	vector_equation(t_obj *obj)
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
