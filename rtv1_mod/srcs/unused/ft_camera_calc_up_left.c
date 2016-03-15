/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_calc_up_left.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 18:17:14 by cledant           #+#    #+#             */
/*   Updated: 2016/03/02 18:19:15 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_camera_calc_up_left(t_camera *cam_scene)
{
	cam_scene->up_left_win[0] = cam_scene->coord[0] +
			((cam_scene->norm_dir_vec[0] *
				cam_scene->camera_size[2]) + (cam_scene->up_vec[0] *
					(cam_scene->camera_size[1] / (double)2)) -
						(cam_scene->right_vec[0] * (cam_scene->camera_size[0] /
													(double)2)));
	cam_scene->up_left_win[1] = cam_scene->coord[1] + ((cam_scene->norm_dir_vec[1] *
				cam_scene->camera_size[2]) + (cam_scene->up_vec[1] *
					(cam_scene->camera_size[1] / (double)2)) -
						(cam_scene->right_vec[1] * (cam_scene->camera_size[0] /
													(double)2)));
	cam_scene->up_left_win[2] = cam_scene->coord[2] +
		((cam_scene->norm_dir_vec[2] *
				cam_scene->camera_size[2]) + (cam_scene->up_vec[2] *
					(cam_scene->camera_size[1] / (double)2)) -
						(cam_scene->right_vec[2] * (cam_scene->camera_size[0] /
													(double)2)));
}
