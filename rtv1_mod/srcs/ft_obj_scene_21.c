/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_scene_21.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 18:44:40 by cledant           #+#    #+#             */
/*   Updated: 2016/03/06 19:03:37 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	ft_add_obj_26(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl)
{
	t_list		*member;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	if ((cyl = ft_cylinder_new(0x00AA00AA, tmp_coord, 2, tmp_vec)) == NULL)
	{
		free(member);
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_cylinder_material(0.25, 0.4, 0.8, cyl);
	cyl->shiny = 1000;
	member->content = cyl;
	member->content_size = 2;
	ft_lstpushback(e->obj_list, member);
}

void	ft_add_obj_27(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl)
{
	t_list		*member;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	if ((cyl = ft_cylinder_new(0x00AA00AA, tmp_coord, 2, tmp_vec)) == NULL)
	{
		free(member);
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_cylinder_material(0.25, 0.4, 0.8, cyl);
	cyl->shiny = 1000;
	member->content = cyl;
	member->content_size = 2;
	ft_lstpushback(e->obj_list, member);
}

void	ft_add_obj_28(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
					t_cylinder *cyl)
{
	t_list		*member;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	if ((cyl = ft_cylinder_new(0x00AA00AA, tmp_coord, 2, tmp_vec)) == NULL)
	{
		free(member);
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_cylinder_material(0.25, 0.4, 0.8, cyl);
	cyl->shiny = 1000;
	member->content = cyl;
	member->content_size = 2;
	ft_lstpushback(e->obj_list, member);
}

void	ft_add_obj_29(t_mlx *e)
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

void	ft_add_obj_210(t_mlx *e)
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
