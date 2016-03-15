/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_spec_angle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 12:40:47 by cledant           #+#    #+#             */
/*   Updated: 2016/03/10 11:31:01 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		ft_calc_spec_angle(double cam_vector[3], double norm_vec[2][3],
				double angle)
{
	double	spec_angle;
	double	norm_spec[3];

	norm_spec[0] = 2 * angle * norm_vec[1][0] - norm_vec[0][0];
	norm_spec[1] = 2 * angle * norm_vec[1][1] - norm_vec[0][1];
	norm_spec[2] = 2 * angle * norm_vec[1][2] - norm_vec[0][2];
	spec_angle = norm_spec[0] * cam_vector[0] + norm_spec[1] *
		cam_vector[1] + norm_spec[2] * cam_vector[2];
	return (spec_angle);
}
