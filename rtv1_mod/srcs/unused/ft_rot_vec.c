/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rot_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:47:22 by cledant           #+#    #+#             */
/*   Updated: 2016/03/02 14:47:31 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_rot_vec(double (*vec)[3], double r_vec[3], double angle)
{
	double	tmp[3];

	angle = M_PI * angle / (double)180;
	tmp[0] = ((r_vec[0] * r_vec[0]) * (1 - cos(angle)) + cos(angle)) * (*vec)[0] +
		((r_vec[0] * r_vec[1]) * (1 - cos(angle)) - r_vec[2] * sin(angle)) *
			(*vec)[1] + ((r_vec[0] * r_vec[2]) * (1 - cos(angle)) + r_vec[1] *
				sin(angle)) * (*vec)[2];
	tmp[1] = ((r_vec[1] * r_vec[1]) * (1 - cos(angle)) + cos(angle)) * (*vec)[1] +
		((r_vec[0] * r_vec[1]) * (1 - cos(angle)) + r_vec[2] * sin(angle)) *
			(*vec)[0] + ((r_vec[1] * r_vec[2]) * (1 - cos(angle)) - r_vec[0] *
				sin(angle)) * (*vec)[2];
	tmp[2] = ((r_vec[2] * r_vec[2]) * (1 - cos(angle)) + cos(angle)) * (*vec)[2] +
		((r_vec[0] * r_vec[2]) * (1 - cos(angle)) - r_vec[1] * sin(angle)) *
			(*vec)[0] + ((r_vec[1] * r_vec[2]) * (1 - cos(angle)) + r_vec[0] *
				sin(angle)) * (*vec)[1];
	(*vec)[0] = tmp[0];
	(*vec)[1] = tmp[1];
	(*vec)[2] = tmp[2];
}
