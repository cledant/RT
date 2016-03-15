/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 09:25:57 by cledant           #+#    #+#             */
/*   Updated: 2016/03/10 17:19:32 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_init_light(t_mlx *e)
{
	t_list	*begin;
	t_light	*light;
	double	tmp_coord[3];

	if ((begin = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	e->light_list = begin;
	tmp_coord[0] = 5;
	tmp_coord[1] = 5;
	tmp_coord[2] = 5;
	if ((light = ft_light_new(tmp_coord, 0x00FFFFFF)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	begin->content = light;
	begin->content_size = 0;
}

static void		ft_init_cam(t_mlx *e)
{
	t_camera	*cam_scene;

	if ((e->cam = (t_camera *)malloc(1 * sizeof(t_camera))) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	cam_scene = e->cam;
	cam_scene->coord[0] = 10;
	cam_scene->coord[1] = 10;
	cam_scene->coord[2] = 10;
	cam_scene->camera_look_at[0] = 0;
	cam_scene->camera_look_at[1] = 0;
	cam_scene->camera_look_at[2] = 0;
	ft_camera_init(cam_scene);
}

static void		ft_init_obj(t_mlx *e)
{
	t_list		*begin;
	t_plane		*plane;
	double		tmp_coord[3];
	double		tmp_vec[3];

	if ((begin = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	e->obj_list = begin;
	tmp_coord[0] = -300;
	tmp_coord[1] = -300;
	tmp_coord[2] = -300;
	tmp_vec[0] = 1;
	tmp_vec[1] = 0;
	tmp_vec[2] = 0;
	if ((plane = ft_plane_new(0x00AA00AA, tmp_coord,tmp_vec)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_plane_material(0.25, 0.4, 0.8, plane);
	plane->shiny = 100;
	begin->content = plane;
	begin->content_size = 1;
}

void			ft_init_scene_2(t_mlx *e)
{
	double		tmp_coord[3];
	double		tmp_vec[3];

	ft_init_cam(e);
	ft_init_light(e);
	ft_init_obj(e);
	ft_add_obj_21(e, tmp_coord, tmp_vec);
	ft_add_obj_22(e, tmp_coord, tmp_vec);
	ft_add_obj_23(e, tmp_coord, tmp_vec);
}
