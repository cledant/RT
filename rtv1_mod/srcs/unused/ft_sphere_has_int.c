/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_has_int.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 19:30:24 by cledant           #+#    #+#             */
/*   Updated: 2016/02/24 11:48:01 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		ft_sphere_has_int(t_sphere *sphere, t_light *light,
								double cur_dir[3])
{
	double		var[3];
	double		det;
	double		length[2];

//	printf("CUR_DIR[0] = %f\n", cur_dir[0]);
//	printf("CUR_DIR[1] = %f\n", cur_dir[1]);
//	printf("CUR_DIR[2] = %f\n", cur_dir[2]);
	var[0] = (cur_dir[0] * cur_dir[0]) + (cur_dir[1] * cur_dir[1]) +
				(cur_dir[2] * cur_dir[2]);
	var[1] = 2 *(cur_dir[0] * -(light->coord[0] - sphere->coord[0]) +
					cur_dir[1] * -(light->coord[1] - sphere->coord[1]) +
						cur_dir[2] * -(light->coord[2] - sphere->coord[2]));
	var[2] = ((light->coord[0] - sphere->coord[0]) * (light->coord[0] -
				sphere->coord[0]) + (light->coord[1] - sphere->coord[1]) *
					(light->coord[1] - sphere->coord[1]) + (light->coord[2] -
							sphere->coord[2]) * (light->coord[2] -
								sphere->coord[2]) - (sphere->radius *
									sphere->radius));
	det = var[1] * var[1] - (4 * var[0] * var[2]);
//	printf("DET = : %f\n", det);
	if (det < 0)
		return (0);
	else if (det == 0)
		return (1);
	else
		return(1);
}
