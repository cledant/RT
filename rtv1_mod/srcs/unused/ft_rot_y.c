/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rot_xy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 09:48:49 by cledant           #+#    #+#             */
/*   Updated: 2016/03/02 13:14:08 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_rot_y(double (*vec)[3], double angle)
{
	double	tmp[3];

	angle = M_PI * angle / (double)180;
	tmp[0] = (*vec)[0] * cos(angle) + (*vec)[2] * sin(angle);
	tmp[1] = (*vec)[1];
	tmp[2] = -(*vec)[0] * sin(angle) + (*vec)[2] * cos(angle);
	(*vec)[0] = tmp[0];
	(*vec)[1] = tmp[1];
	(*vec)[2] = tmp[2];
}
