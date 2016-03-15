/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 11:27:39 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 19:30:25 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			expose_hook(t_mlx *e)
{
	if (e->render == 0)
	{
		ft_draw_image(e);
		e->render = 1;
		mlx_clear_window(e->mlx, e->win);
		mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	}
	return (0);
}

void		key_hook_12(int keycode, t_camera *camera, t_mlx *e)
{
	if (keycode == MLX_KEY_UP)
	{
		camera->coord[0] = camera->coord[0] + MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_DOWN)
	{
		camera->coord[0] = camera->coord[0] - MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_RIGHT)
	{
		camera->coord[1] = camera->coord[1] + MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	key_hook_13(keycode, camera, e);
}

void		key_hook_13(int keycode, t_camera *camera, t_mlx *e)
{
	if (keycode == MLX_KEY_LEFT)
	{
		camera->coord[1] = camera->coord[1] - MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_PLUS)
	{
		camera->coord[2] = camera->coord[2] + MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_MINUS)
	{
		camera->coord[2] = camera->coord[2] - MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	key_hook_14(keycode, camera, e);
}

void		key_hook_14(int keycode, t_camera *camera, t_mlx *e)
{
	if (keycode == MLX_KEY_W)
	{
		camera->camera_look_at[2] = camera->camera_look_at[2] + MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_S)
	{
		camera->camera_look_at[2] = camera->camera_look_at[2] - MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_A)
	{
		camera->camera_look_at[1] = camera->camera_look_at[1] - MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	key_hook_2(keycode, camera, e);
}

int			key_hook(int keycode, t_mlx *e)
{
	t_camera	*camera;

	camera = e->cam;
	if (keycode == MLX_KEY_ESC)
	{
		mlx_destroy_image(e->mlx, e->img);
		mlx_clear_window(e->mlx, e->win);
		mlx_destroy_window(e->mlx, e->win);
		if (e->cam != NULL)
			free(e->cam);
		if (e->obj_list != NULL)
			ft_lstdel(&(e->obj_list), &ft_lstfree_malloc);
		if (e->light_list != NULL)
			ft_lstdel(&(e->light_list), &ft_lstfree_malloc);
		free(e->mlx);
		exit(0);
	}
	key_hook_12(keycode, camera, e);
	return (0);
}
