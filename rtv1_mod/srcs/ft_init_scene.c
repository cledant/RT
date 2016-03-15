/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 09:25:57 by cledant           #+#    #+#             */
/*   Updated: 2016/03/10 12:09:03 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_init_light(t_mlx *e)
{
	t_list	*begin;
	double	tmp_coord[3];
	t_light	*light;

	if ((begin = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	e->light_list = begin;
	tmp_coord[0] = 20;
	tmp_coord[1] = 20;
	tmp_coord[2] = 5;
	if ((light = ft_light_new(tmp_coord, 0x00330000)) == NULL)
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
	cam_scene->coord[0] = 100;
	cam_scene->coord[1] = 100;
	cam_scene->coord[2] = 10;
	cam_scene->camera_look_at[0] = 0;
	cam_scene->camera_look_at[1] = 0;
	cam_scene->camera_look_at[2] = 0;
	ft_camera_init(cam_scene);
}

static void		ft_init_obj(t_mlx *e)
{
	t_list		*begin;
	double		tmp_coord[3];
	t_sphere	*sphere;

	if ((begin = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	e->obj_list = begin;
	tmp_coord[0] = 0;
	tmp_coord[1] = 0;
	tmp_coord[2] = 0;
	if ((sphere = ft_sphere_new(0x00FF0000, tmp_coord, 8)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_sphere_material(0.25, 0.4, 0.8, sphere);
	sphere->shiny = 100;
	begin->content = sphere;
	begin->content_size = 0;
}

/*static void		ft_init_next(t_mlx *e)
{
	double		tmp_coord[3];
	double		tmp_vec[3];
	t_cone		*cone;

	cone = NULL;
	tmp_coord[0] = 0;
	tmp_coord[1] = 5;
	tmp_coord[2] = 5;
	tmp_vec[0] = 2;
	tmp_vec[1] = 0;
	tmp_vec[2] = 1;
	ft_normalize_vec(&tmp_vec);
	ft_add_obj_15(e, tmp_coord, tmp_vec, cone);
}
*/
void			ft_init_scene(t_mlx *e)
{
//	double		tmp_coord[3];
//	double		tmp_vec[3];
	t_cylinder	*cyl;

	cyl = NULL;
	ft_init_light(e);
	ft_init_cam(e);
	ft_init_obj(e);
/*	ft_add_obj_11(e, tmp_coord, tmp_vec);
	ft_add_obj_12(e, tmp_coord, tmp_vec);
	ft_add_obj_13(e, tmp_coord, tmp_vec);
	tmp_coord[0] = 1;
	tmp_coord[1] = -1;
	tmp_coord[2] = 5;
	tmp_vec[0] = 2;
	tmp_vec[1] = 2;
	tmp_vec[2] = 1;
	ft_normalize_vec(&tmp_vec);
	ft_add_obj_14(e, tmp_coord, tmp_vec, cyl);
	ft_init_next(e);
*/}
