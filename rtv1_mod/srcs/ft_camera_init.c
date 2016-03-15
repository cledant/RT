/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 20:55:47 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 12:35:41 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_cam_vec(t_camera *cam)
{
	if (cam->coord[0] == 0 && cam->coord[1] == 0 && cam->coord[2] > 0)
	{
		cam->up_vec[0] = -1;
		cam->up_vec[1] = 0;
		cam->up_vec[2] = 0;
	}
	else if (cam->coord[0] == 0 && cam->coord[1] == 0 && cam->coord[2] < 0)
	{
		cam->up_vec[0] = 1;
		cam->up_vec[1] = 0;
		cam->up_vec[2] = 0;
	}
	else
	{
		cam->up_vec[0] = 0;
		cam->up_vec[1] = 0;
		cam->up_vec[2] = 1;
	}
	cam->right_vec[0] = 0;
	cam->right_vec[1] = 0;
	cam->right_vec[2] = 0;
	ft_scalar_product(cam->norm_dir_vec, cam->up_vec, &cam->right_vec);
	ft_normalize_vec(&cam->right_vec);
	ft_scalar_product(cam->right_vec, cam->norm_dir_vec, &cam->up_vec);
	ft_normalize_vec(&cam->up_vec);
}

static void		ft_cam_value(t_camera *cam)
{
	cam->camera_size[0] = 0.5;
	cam->camera_size[1] = 0.5;
	cam->camera_size[2] = 1;
	cam->dir_vec[0] = cam->camera_look_at[0] - cam->coord[0];
	cam->dir_vec[1] = cam->camera_look_at[1] - cam->coord[1];
	cam->dir_vec[2] = cam->camera_look_at[2] - cam->coord[2];
	cam->norm = sqrt(cam->dir_vec[0] * cam->dir_vec[0] +
		cam->dir_vec[1] * cam->dir_vec[1] + cam->dir_vec[2] *
		cam->dir_vec[2]);
	cam->norm_dir_vec[0] = cam->dir_vec[0] / cam->norm;
	cam->norm_dir_vec[1] = cam->dir_vec[1] / cam->norm;
	cam->norm_dir_vec[2] = cam->dir_vec[2] / cam->norm;
}

void			ft_camera_init(t_camera *cam)
{
	ft_cam_value(cam);
	ft_cam_vec(cam);
	cam->up_left_win[0] = cam->coord[0] + ((cam->norm_dir_vec[0] *
		cam->camera_size[2]) + (cam->up_vec[0] * (cam->camera_size[1] /
			(double)2)) - (cam->right_vec[0] * (cam->camera_size[0] /
				(double)2)));
	cam->up_left_win[1] = cam->coord[1] + ((cam->norm_dir_vec[1] *
		cam->camera_size[2]) + (cam->up_vec[1] * (cam->camera_size[1] /
			(double)2)) - (cam->right_vec[1] * (cam->camera_size[0] /
				(double)2)));
	cam->up_left_win[2] = cam->coord[2] + ((cam->norm_dir_vec[2] *
		cam->camera_size[2]) + (cam->up_vec[2] * (cam->camera_size[1] /
			(double)2)) - (cam->right_vec[2] * (cam->camera_size[0] /
				(double)2)));
	cam->x_inc = cam->camera_size[0] / (double)WIN_X;
	cam->y_inc = cam->camera_size[1] / (double)WIN_Y;
}
