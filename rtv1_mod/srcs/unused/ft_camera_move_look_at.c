/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_move_look_at.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 10:32:56 by cledant           #+#    #+#             */
/*   Updated: 2016/03/02 10:33:21 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	ft_camera_move_look_at(t_camera *cam_scene)
{
	cam_scene->dir_vec[0] = cam_scene->camera_look_at[0] - cam_scene->coord[0];
	cam_scene->dir_vec[1] = cam_scene->camera_look_at[1] - cam_scene->coord[1];
	cam_scene->dir_vec[2] = cam_scene->camera_look_at[2] - cam_scene->coord[2];
	cam_scene->norm = sqrt(cam_scene->dir_vec[0] * cam_scene->dir_vec[0] +
		cam_scene->dir_vec[1] * cam_scene->dir_vec[1] + cam_scene->dir_vec[2] *
		cam_scene->dir_vec[2]);
	cam_scene->norm_dir_vec[0] = cam_scene->dir_vec[0] / cam_scene->norm;
	cam_scene->norm_dir_vec[1] = cam_scene->dir_vec[1] / cam_scene->norm;
	cam_scene->norm_dir_vec[2] = cam_scene->dir_vec[2] / cam_scene->norm;
	printf("dir_vec = %f\n", cam_scene->norm_dir_vec[0]);
	printf("dir_vec = %f\n", cam_scene->norm_dir_vec[1]);
	printf("dir_vec = %f\n", cam_scene->norm_dir_vec[2]);
	// debut triangle ortho
	if (cam_scene->coord[0] == 0 && cam_scene->coord[1] == 0 &&
			cam_scene->coord[2] > 0)
	{
		cam_scene->up_vec[0] = -1;
		cam_scene->up_vec[1] = 0;
		cam_scene->up_vec[2] = 0;
	}
	else if (cam_scene->coord[0] == 0 && cam_scene->coord[1] == 0 &&
			cam_scene->coord[2] < 0)
	{
		cam_scene->up_vec[0] = 1;
		cam_scene->up_vec[1] = 0;
		cam_scene->up_vec[2] = 0;
	}
	else
	{
		cam_scene->up_vec[0] = 0;
		cam_scene->up_vec[1] = 0;
		cam_scene->up_vec[2] = 1;
	}
	cam_scene->right_vec[0] = 0;
	cam_scene->right_vec[1] = 0;
	cam_scene->right_vec[2] = 0;
	ft_scalar_product(cam_scene->up_vec, cam_scene->norm_dir_vec,
			&cam_scene->right_vec);
	ft_scalar_product(cam_scene->right_vec, cam_scene->norm_dir_vec, 
			&cam_scene->up_vec);
	// fin triangle ortho
	printf("up_vec = %f\n", cam_scene->up_vec[0]);
	printf("up_vec = %f\n", cam_scene->up_vec[1]);
	printf("up_vec = %f\n", cam_scene->up_vec[2]);
	printf("right_vec = %f\n", cam_scene->right_vec[0]);
	printf("right_vec = %f\n", cam_scene->right_vec[1]);
	printf("right_vec = %f\n", cam_scene->right_vec[2]);
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
	printf("up_left = %f\n", cam_scene->up_left_win[0]);
	printf("up_left = %f\n", cam_scene->up_left_win[1]);
	printf("up_left = %f\n", cam_scene->up_left_win[2]);
	cam_scene->x_inc = cam_scene->camera_size[0] / (double)WIN_X;
	cam_scene->y_inc = cam_scene->camera_size[1] / (double)WIN_Y;
	//fin camera
}
