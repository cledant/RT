/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 14:43:26 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 19:30:43 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		key_hook_2(int keycode, t_camera *camera, t_mlx *e)
{
	if (keycode == MLX_KEY_U)
	{
		camera->coord[0] = 100;
		camera->coord[1] = 100;
		camera->coord[2] = 10;
		camera->camera_look_at[0] = 0;
		camera->camera_look_at[1] = 0;
		camera->camera_look_at[2] = 0;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_I)
	{
		camera->coord[0] = 75;
		camera->coord[1] = 0;
		camera->coord[2] = 10;
		camera->camera_look_at[0] = 0;
		camera->camera_look_at[1] = 0;
		camera->camera_look_at[2] = 5;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	key_hook_21(keycode, camera, e);
}

void		key_hook_21(int keycode, t_camera *camera, t_mlx *e)
{
	if (keycode == MLX_KEY_O)
	{
		camera->coord[0] = 100;
		camera->coord[1] = 0;
		camera->coord[2] = 10;
		camera->camera_look_at[0] = 0;
		camera->camera_look_at[1] = 0;
		camera->camera_look_at[2] = 0;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_P)
	{
		camera->coord[0] = 0;
		camera->coord[1] = 100;
		camera->coord[2] = 10;
		camera->camera_look_at[0] = 0;
		camera->camera_look_at[1] = 0;
		camera->camera_look_at[2] = 0;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	key_hook_22(keycode, camera, e);
}

void		key_hook_22(int keycode, t_camera *camera, t_mlx *e)
{
	if (keycode == MLX_KEY_D)
	{
		camera->camera_look_at[1] = camera->camera_look_at[1] + MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_Q)
	{
		camera->camera_look_at[0] = camera->camera_look_at[0] + MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	else if (keycode == MLX_KEY_E)
	{
		camera->camera_look_at[0] = camera->camera_look_at[0] - MLX_CAM_STEP;
		ft_camera_init(camera);
		e->render = 0;
		expose_hook(e);
	}
	key_hook_23(keycode, e);
}

void		key_hook_23(int keycode, t_mlx *e)
{
	if (keycode == MLX_KEY_1)
	{
		if (e->cam != NULL)
			free(e->cam);
		e->cam = NULL;
		if (e->obj_list != NULL)
			ft_lstdel(&(e->obj_list), &ft_lstfree_malloc);
		if (e->light_list != NULL)
			ft_lstdel(&(e->light_list), &ft_lstfree_malloc);
		ft_init_scene(e);
		e->render = 0;
		expose_hook(e);
	}
	key_hook_24(keycode, e);
}

void		key_hook_24(int keycode, t_mlx *e)
{
	if (keycode == MLX_KEY_2)
	{
		if (e->cam != NULL)
			free(e->cam);
		e->cam = NULL;
		if (e->obj_list != NULL)
			ft_lstdel(&(e->obj_list), &ft_lstfree_malloc);
		if (e->light_list != NULL)
			ft_lstdel(&(e->light_list), &ft_lstfree_malloc);
		ft_init_scene_2(e);
		e->render = 0;
		expose_hook(e);
	}
}
