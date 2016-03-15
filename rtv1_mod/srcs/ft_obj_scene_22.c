/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 09:25:57 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 19:02:23 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_add_obj_211(t_mlx *e)
{
	t_list		*member;
	double		tmp_coord[3];
	t_sphere	*sphere;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = -70;
	tmp_coord[1] = 20;
	tmp_coord[2] = -10;
	if ((sphere = ft_sphere_new(0x00AA00AA, tmp_coord, 3)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_sphere_material(0.25, 0.4, 0.8, sphere);
	sphere->shiny = 100;
	member->content = sphere;
	member->content_size = 0;
	ft_lstpushback(e->obj_list, member);
}

void	ft_add_obj_212(t_mlx *e)
{
	t_list		*member;
	t_sphere	*sphere;
	double		tmp_coord[3];

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = -70;
	tmp_coord[1] = 20;
	tmp_coord[2] = 20;
	if ((sphere = ft_sphere_new(0x00AA00AA, tmp_coord, 3)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_sphere_material(0.25, 0.4, 0.8, sphere);
	sphere->shiny = 100;
	member->content = sphere;
	member->content_size = 0;
	ft_lstpushback(e->obj_list, member);
}

void	ft_add_obj_213(t_mlx *e)
{
	t_list		*member;
	t_sphere	*sphere;
	double		tmp_coord[3];

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = -20;
	tmp_coord[1] = -20;
	tmp_coord[2] = 20;
	if ((sphere = ft_sphere_new(0x00AA00AA, tmp_coord, 3)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_sphere_material(0.25, 0.4, 0.8, sphere);
	sphere->shiny = 100;
	member->content = sphere;
	member->content_size = 0;
	ft_lstpushback(e->obj_list, member);
}

void	ft_add_obj_214(t_mlx *e)
{
	t_list		*member;
	t_sphere	*sphere;
	double		tmp_coord[3];

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = -20;
	tmp_coord[1] = -20;
	tmp_coord[2] = -10;
	if ((sphere = ft_sphere_new(0x00AA00AA, tmp_coord, 3)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_sphere_material(0.25, 0.4, 0.8, sphere);
	sphere->shiny = 100;
	member->content = sphere;
	member->content_size = 0;
	ft_lstpushback(e->obj_list, member);
}

void	ft_add_obj_215(t_mlx *e)
{
	t_sphere	*sphere;
	t_list		*member;
	double		tmp_coord[3];

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = -70;
	tmp_coord[1] = -20;
	tmp_coord[2] = -10;
	if ((sphere = ft_sphere_new(0x00AA00AA, tmp_coord, 3)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_sphere_material(0.25, 0.4, 0.8, sphere);
	sphere->shiny = 100;
	member->content = sphere;
	member->content_size = 0;
	ft_lstpushback(e->obj_list, member);
}
