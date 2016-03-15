/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_scene_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 18:43:21 by cledant           #+#    #+#             */
/*   Updated: 2016/03/11 19:21:49 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_add_obj_21(t_mlx *e, double tmp_coord[3], double tmp_vec[3])
{
	t_list		*member;
	t_plane		*plane;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = -10;
	tmp_coord[1] = 0;
	tmp_coord[2] = 0;
	tmp_vec[0] = 1;
	tmp_vec[1] = 0;
	tmp_vec[2] = 0;
	if ((plane = ft_plane_new(0x00AA0000, tmp_coord, tmp_vec)) == NULL)
	{
		free(member);
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_plane_material(0.25, 0.4, 0.8, plane);
	plane->shiny = 1000;
	member->content = plane;
	member->content_size = 1;
	ft_lstpushback(e->obj_list, member);
}

void		ft_add_obj_22(t_mlx *e, double tmp_coord[3], double tmp_vec[3])
{
	t_list		*member;
	t_plane		*plane;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = 0;
	tmp_coord[1] = 0;
	tmp_coord[2] = -10;
	tmp_vec[0] = 0;
	tmp_vec[1] = 0;
	tmp_vec[2] = 1;
	if ((plane = ft_plane_new(0x0000AA00, tmp_coord, tmp_vec)) == NULL)
	{
		free(member);
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_plane_material(0.25, 0.4, 0.8, plane);
	plane->shiny = 1000;
	member->content = plane;
	member->content_size = 1;
	ft_lstpushback(e->obj_list, member);
}

void		ft_add_obj_23(t_mlx *e, double tmp_coord[3], double tmp_vec[3])
{
	t_list		*member;
	t_plane		*plane;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = 0;
	tmp_coord[1] = -10;
	tmp_coord[2] = 0;
	tmp_vec[0] = 0;
	tmp_vec[1] = 1;
	tmp_vec[2] = 0;
	if ((plane = ft_plane_new(0x000000AA, tmp_coord, tmp_vec)) == NULL)
	{
		free(member);
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_plane_material(0.25, 0.4, 0.8, plane);
	plane->shiny = 1000;
	member->content = plane;
	member->content_size = 1;
	ft_lstpushback(e->obj_list, member);
}

void		ft_add_obj_24(t_mlx *e, double tmp_coord[3], double tmp_vec[3])
{
	t_list		*member;
	t_plane		*plane;

	if ((member = ft_lstnew(NULL, 0)) == NULL)
	{
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	tmp_coord[0] = 0;
	tmp_coord[1] = -100;
	tmp_coord[2] = 0;
	tmp_vec[0] = 0;
	tmp_vec[1] = 1;
	tmp_vec[2] = 0;
	if ((plane = ft_plane_new(0x00AAAA00, tmp_coord, tmp_vec)) == NULL)
	{
		free(member);
		ft_putendl("Not enough memory");
		key_hook(MLX_KEY_ESC, e);
	}
	ft_plane_material(0.25, 0.4, 0.8, plane);
	plane->shiny = 75;
	member->content = plane;
	member->content_size = 1;
	ft_lstpushback(e->obj_list, member);
}

void		ft_add_obj_25(t_mlx *e, double tmp_coord[3], double tmp_vec[3],
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
