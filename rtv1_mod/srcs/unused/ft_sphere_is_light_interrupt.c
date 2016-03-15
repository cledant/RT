/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_is_light_interrupt.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 17:50:44 by cledant           #+#    #+#             */
/*   Updated: 2016/02/26 18:17:21 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		ft_sphere_is_light_interrupt(t_light *light, t_sphere *sph,
				double int_coord[3])
{
	double	vector[3];
	double	norm;
	double	norm_light[3];
	double	dist;

	dist = 1000000;
//	printf("int coord %f\n", int_coord[0]);
//	printf("int coord %f\n", int_coord[1]);
//	printf("int coord %f\n", int_coord[2]);
//	printf("int coord %f\n", light->coord[0]);
//	printf("int coord %f\n", light->coord[1]);
//	printf("int coord %f\n", light->coord[2]);
	vector[0] = int_coord[0]  - light->coord[0];
	vector[1] = int_coord[1]  - light->coord[1];
	vector[2] = int_coord[2]  - light->coord[2];
	norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + 
			vector[2] * vector[2]);
	norm_light[0] = -vector[0] / norm;
	norm_light[1] = -vector[1] / norm;
	norm_light[2] = -vector[2] / norm;
//	ft_putendl("TEST LIGHT");
	if (ft_calc_int_sphere_light(sph, light,
				norm_light, &dist) == 1)
	{
//		printf("norm = %f\n", norm);
//		printf("dist = %f\n", dist);
		if (norm < dist)
			return (0);
		else
			return (1);
	}
	else
	{
		return (0);
	}
}
