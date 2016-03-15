/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_norm_vec_plane.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 13:23:51 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:34:52 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_calc_norm_vec_plane(t_plane *obj, double (*norm_vec_normal)[3])
{
	double	norm;

	norm = sqrt(obj->factor[0] * obj->factor[0] + obj->factor[1] *
			obj->factor[1] + obj->factor[2] * obj->factor[2]);
	(*norm_vec_normal)[0] = obj->factor[0] / norm;
	(*norm_vec_normal)[1] = obj->factor[1] / norm;
	(*norm_vec_normal)[2] = obj->factor[2] / norm;
}
