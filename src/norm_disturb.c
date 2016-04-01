/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_disturb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 12:54:55 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/30 14:28:24 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sin_change_normal(t_hit_pt *hit_pt, t_obj *hit_obj)
{
	vector_rotation(hit_pt->crd, hit_obj, 1);
	hit_pt->normal->z = (1 + sin(hit_obj->norm_freq * hit_pt->crd->z)) / 2.0;
	hit_pt->normal->y = (1 + sin(hit_obj->norm_freq * hit_pt->crd->y)) / 2.0;
	vector_rotation(hit_pt->crd, hit_obj, 0);
}

void	perlin_change_normal(t_hit_pt *hit_pt, t_obj *hit_obj)
{
	float		tmp;

	vector_rotation(hit_pt->crd, hit_obj, 1);
	if (hit_obj->type == 1)
		tmp = fabs(perlin_noise(hit_pt->crd->x, hit_pt->crd->y,
					hit_obj->tex->freq, hit_obj->tex->octa));
	else
		tmp = fabs(perlin_noise_3d(hit_pt->crd, hit_obj->tex->freq,
					hit_obj->tex->octa));
	hit_pt->normal->x -= 2 * tmp;
	hit_pt->normal->y -= 2 * tmp;
	hit_pt->normal->z -= 2 * tmp;
	normalise(hit_pt->normal);
	vector_rotation(hit_pt->crd, hit_obj, 0);
}

float	get_img_norm(char *addr)
{
	float	r;
	float	g;
	float	b;
	float	ret;
	char	tmp;

	ft_memcpy(&tmp, (addr + 0), 1);
	b = (unsigned char)tmp / 255.0;
	ft_memcpy(&tmp, (addr + 1), 1);
	g = (unsigned char)tmp / 255.0;
	ft_memcpy(&tmp, (addr + 2), 1);
	r = (unsigned char)tmp / 255.0;
	ret = (r + g + b) / 3.0;
	return (1 - ret);
}

void	image_change_normal(t_hit_pt *hit_pt, t_obj *hit_obj)
{
	double	uv[4];
	char	*addr;
	float	img_norm;

	uv[0] = hit_obj->bump_img->img_width;
	uv[1] = hit_obj->bump_img->img_height;
	if (hit_obj->type == 1)
		seek_uv_plane_img(hit_pt, hit_obj, &uv);
	else if (hit_obj->type == 2)
		seek_uv_sph(hit_pt, hit_obj, &uv[0], &uv[1]);
	else
		seek_uv_cyl_cone_img(hit_pt, hit_obj, &uv,
				hit_obj->bump_img->img_width);
	if (hit_obj->type != 1)
	{
		uv[2] = uv[0] * hit_obj->bump_img->img_width;
		uv[3] = uv[1] * hit_obj->bump_img->img_height;
	}
	addr = hit_obj->bump_img->data + (int)(uv[2]) * 4 + (int)(uv[3]) *
		hit_obj->bump_img->img_width * 4;
	img_norm = get_img_norm(addr);
	hit_pt->normal->x -= 2 * img_norm;
	hit_pt->normal->y -= 2 * img_norm;
	hit_pt->normal->z -= 2 * img_norm;
	normalise(hit_pt->normal);
}

void	fuse_dot_change_normal(t_hit_pt *hit_pt, t_obj *hit_obj)
{
	double	tmp_1;
	double	tmp_2;
	double	tmp_3;

	vector_rotation(hit_pt->crd, hit_obj, 1);
	tmp_1 = (1 + sin(hit_obj->norm_freq * hit_pt->crd->x)) / 2.0f;
	tmp_2 = (1 + sin(hit_obj->norm_freq * hit_pt->crd->y)) / 2.0f;
	tmp_3 = (1 + sin(hit_obj->norm_freq * hit_pt->crd->z)) / 2.0f;
	hit_pt->normal->x += tmp_1;
	hit_pt->normal->y += tmp_2;
	hit_pt->normal->z += tmp_3;
	normalise(hit_pt->normal);
	vector_rotation(hit_pt->crd, hit_obj, 0);
}
