/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cledant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 14:08:37 by cledant           #+#    #+#             */
/*   Updated: 2016/03/30 14:15:46 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mat			*checker_xy_plane(t_hit_pt *hit_pt, t_obj *obj)
{
	double	x;
	double	y;
	double	size;

	size = obj->tex->size;
	seek_uv_plane(hit_pt, obj, &x, &y);
	if ((x >= 0 && x <= size / 2) && (y >= 0 && y <= size / 2))
		return (obj->tex->mat_2);
	else if ((x > size / 2 && x <= size) && (y >= 0 && y <= size / 2))
		return (obj->tex->mat_1);
	else if ((x >= 0 && x <= size / 2) && (y > size / 2 && y <= size))
		return (obj->tex->mat_1);
	else
		return (obj->tex->mat_2);
}

t_mat			*checker_xy_sph_cyl_cone(t_hit_pt *hit_pt, t_obj *obj)
{
	int		x;
	int		y;
	double	sub;
	double	uv[2];

	sub = obj->tex->size;
	if (obj->type == 2)
		seek_uv_sph(hit_pt, obj, &uv[0], &uv[1]);
	else
		seek_uv_cyl_cone(hit_pt, obj, &uv[0], &uv[1]);
	x = uv[0] * sub;
	y = uv[1] * sub;
	if (fmod(x, 2) == 0 && fmod(y, 2) == 0)
		return (obj->tex->mat_2);
	else if (fmod(x, 2) == 0 && fmod(y, 2) == 1)
		return (obj->tex->mat_1);
	else if (fmod(x, 2) == 1 && fmod(y, 2) == 0)
		return (obj->tex->mat_1);
	else
		return (obj->tex->mat_2);
}

static void		cpy_color(char *addr, t_obj *obj)
{
	char	tmp;

	ft_memcpy(&tmp, (addr + 0), 1);
	obj->tex->mat_img->color->b = (unsigned char)tmp / 255.0;
	ft_memcpy(&tmp, (addr + 1), 1);
	obj->tex->mat_img->color->g = (unsigned char)tmp / 255.0;
	ft_memcpy(&tmp, (addr + 2), 1);
	obj->tex->mat_img->color->r = (unsigned char)tmp / 255.0;
}

t_mat			*img_xy_plane(t_hit_pt *hit_pt, t_obj *obj)
{
	double	uv[4];
	char	*addr;

	uv[0] = obj->tex->img->img_width;
	uv[1] = obj->tex->img->img_height;
	seek_uv_plane_img(hit_pt, obj, &uv);
	addr = obj->tex->img->data + (int)(uv[2]) * 4 + (int)(uv[3]) *
		(int)(uv[0]) * 4;
	cpy_color(addr, obj);
	return (obj->tex->mat_img);
}

t_mat			*img_xy_sph_cyl_cone(t_hit_pt *hit_pt, t_obj *obj)
{
	double	uv[4];
	char	*addr;

	if (obj->type == 2)
		seek_uv_sph(hit_pt, obj, &uv[0], &uv[1]);
	else
		seek_uv_cyl_cone_img(hit_pt, obj, &uv, obj->tex->img->img_width);
	uv[2] = uv[0] * obj->tex->img->img_width;
	uv[3] = uv[1] * obj->tex->img->img_height;
	addr = obj->tex->img->data + (int)(uv[2]) * 4 + (int)(uv[3]) *
		obj->tex->img->img_width * 4;
	cpy_color(addr, obj);
	return (obj->tex->mat_img);
}
