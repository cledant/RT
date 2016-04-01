/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 09:42:26 by vlize             #+#    #+#             */
/*   Updated: 2016/03/30 12:59:46 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotation_matrix(double *absc, double *ord, double angle[3], int neg)
{
	double	k;

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

void	csg_rotation(t_vector3 *vec, t_csg *csg, int neg)
{
	if (neg)
	{
		rotation_matrix(&vec->x, &vec->y, csg->rz, neg);
		rotation_matrix(&vec->z, &vec->x, csg->ry, neg);
		rotation_matrix(&vec->y, &vec->z, csg->rx, neg);
	}
	else
	{
		rotation_matrix(&vec->y, &vec->z, csg->rx, neg);
		rotation_matrix(&vec->z, &vec->x, csg->ry, neg);
		rotation_matrix(&vec->x, &vec->y, csg->rz, neg);
	}
}
