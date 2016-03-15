/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_int_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 09:33:09 by cledant           #+#    #+#             */
/*   Updated: 2016/02/29 10:42:46 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int		ft_calc_int_cylinder(t_cylinder *cyl, t_camera *camera,
								double cur_dir[3], double *dist)
{
	double		var[3];
	double		det;
	double		length[2];

//	printf("CUR_DIR[0] = %f\n", cur_dir[0]);
//	printf("CUR_DIR[1] = %f\n", cur_dir[1]);
//	printf("CUR_DIR[2] = %f\n", cur_dir[2]);
//	printf("light pos %f\n", camera->coord[0]);
//	printf("light pos %f\n", camera->coord[1]);
//	printf("light pos %f\n", camera->coord[2]);
//	printf("cyl[0] = %f\n", cyl->coord[0]);
//	printf("cyl[1] = %f\n", cyl->coord[1]);
//	printf("cyl[2] = %f\n", cyl->coord[2]);
	var[0] = ((cur_dir[0] * cur_dir[0]) + (cur_dir[1] * cur_dir[1]) +
		(cur_dir[2] * cur_dir[2])) - (((cur_dir[0] * cyl->dir[0]) + 
		(cur_dir[1] * cyl->dir[1]) + (cur_dir[2] * cyl->dir[2])) *
		 ((cur_dir[0] * cyl->dir[0]) + (cur_dir[1] * cyl->dir[1]) + 
		  (cur_dir[2] * cyl->dir[2])));
	var[1] = 2 * ((cur_dir[0] * -(camera->coord[0] - cyl->coord[0]) +
		cur_dir[1] * -(camera->coord[1] - cyl->coord[1]) +cur_dir[2] *
		-(camera->coord[2] - cyl->coord[2])) - (((cur_dir[0] * cyl->dir[0]) + 
		(cur_dir[1] * cyl->dir[1]) + (cur_dir[2] * cyl->dir[2])) * 
		((cyl->dir[0] * -(camera->coord[0] - cyl->coord[0]) +
		cyl->dir[1] * -(camera->coord[1] - cyl->coord[1]) + cyl->dir[2] *
		-(camera->coord[2] - cyl->coord[2])))));
	var[2] = ((camera->coord[0] - cyl->coord[0]) * (camera->coord[0] -
		cyl->coord[0]) + (camera->coord[1] - cyl->coord[1]) *
		(camera->coord[1] - cyl->coord[1]) + (camera->coord[2] -
		cyl->coord[2]) * (camera->coord[2] - cyl->coord[2])) - (cyl->radius *
		cyl->radius) - (((cyl->dir[0] * -(camera->coord[0] - cyl->coord[0]) +
		cyl->dir[1] * -(camera->coord[1] - cyl->coord[1]) + cyl->dir[2] *
		-(camera->coord[2] - cyl->coord[2])) * (cyl->dir[0] * 
		-(camera->coord[0] - cyl->coord[0]) + cyl->dir[1] *
		-(camera->coord[1] - cyl->coord[1]) + cyl->dir[2] *
		-(camera->coord[2] - cyl->coord[2]))));
	det = var[1] * var[1] - (4 * var[0] * var[2]);
//	printf("DET = : %f\n", det);
	if (det < 0)
		return (0);
	else if (det == 0)
	{
		length[0] = (-var[1] / (2 * var[0]));
		if (length[0] < *dist)
		{
			if (length[0] < 0)
				return (0);
			*dist = length[0];
			return (1);
		}
		return (0);
	}
	else
	{
		length[0] = (-var[1] + sqrt(det)) / (2 * var[0]);
		length[1] = (-var[1] - sqrt(det)) / (2 * var[0]);
//		printf("length 0 = %f\n", length[0]);
//		printf("length 1 = %f\n", length[1]);
		if (length[1] < length[0])
		{
			if (length[1] < *dist)
			{
				if (length[1] < 0)
					return (0);
				else
				{
					*dist = length[1];
					return(1);
				}
			}
		}
		else
		{
			if (length[0] < *dist)
			{
				if (length[0] < 0)
					return (0);
				else
				{
					*dist = length[0];
					return(1);
				}
			}
		}
		return (0);
	}
}
