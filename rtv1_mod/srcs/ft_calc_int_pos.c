/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_int_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 20:13:34 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:33:36 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_calc_int_pos(double dist, double cur_vec[3], double coord_cam[3],
			double (*int_coord)[3])
{
	(*int_coord)[0] = -cur_vec[0] * dist + coord_cam[0];
	(*int_coord)[1] = -cur_vec[1] * dist + coord_cam[1];
	(*int_coord)[2] = -cur_vec[2] * dist + coord_cam[2];
}
