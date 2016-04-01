/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:40:22 by cledant           #+#    #+#             */
/*   Updated: 2016/03/30 14:05:13 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		add_color_to_mat(t_obj *hit_obj, float color)
{
	if (hit_obj->tex->grad_r == 1)
		hit_obj->tex->mat_2->color->r += color;
	else if (hit_obj->tex->grad_r == -1)
		hit_obj->tex->mat_2->color->r -= color;
	if (hit_obj->tex->grad_g == 1)
		hit_obj->tex->mat_2->color->g += color;
	else if (hit_obj->tex->grad_g == -1)
		hit_obj->tex->mat_2->color->g -= color;
	if (hit_obj->tex->grad_b == 1)
		hit_obj->tex->mat_2->color->b += color;
	else if (hit_obj->tex->grad_b == -1)
		hit_obj->tex->mat_2->color->b -= color;
	if (hit_obj->tex->mat_2->color->r > 1)
		hit_obj->tex->mat_2->color->r = 1;
	if (hit_obj->tex->mat_2->color->g > 1)
		hit_obj->tex->mat_2->color->g = 1;
	if (hit_obj->tex->mat_2->color->b > 1)
		hit_obj->tex->mat_2->color->b = 1;
	if (hit_obj->tex->mat_2->color->r < 0)
		hit_obj->tex->mat_2->color->r = 0;
	if (hit_obj->tex->mat_2->color->g < 0)
		hit_obj->tex->mat_2->color->g = 0;
	if (hit_obj->tex->mat_2->color->b < 0)
		hit_obj->tex->mat_2->color->b = 0;
}

static t_mat	*perlin_plane(t_hit_pt *hit_pt, t_obj *hit_obj)
{
	float	tmp;

	vector_rotation(hit_pt->crd, hit_obj, 1);
	hit_obj->tex->mat_2->color->r = hit_obj->tex->mat_1->color->r;
	hit_obj->tex->mat_2->color->g = hit_obj->tex->mat_1->color->g;
	hit_obj->tex->mat_2->color->b = hit_obj->tex->mat_1->color->b;
	tmp = fabs(perlin_noise(hit_pt->crd->x, hit_pt->crd->y,
				hit_obj->tex->freq, hit_obj->tex->octa));
	add_color_to_mat(hit_obj, tmp);
	vector_rotation(hit_pt->crd, hit_obj, 0);
	return (hit_obj->tex->mat_2);
}

static t_mat	*perlin_sph_cyl_cone(t_hit_pt *hit_pt, t_obj *hit_obj)
{
	float	tmp;

	vector_rotation(hit_pt->crd, hit_obj, 1);
	hit_obj->tex->mat_2->color->r = hit_obj->tex->mat_1->color->r;
	hit_obj->tex->mat_2->color->g = hit_obj->tex->mat_1->color->g;
	hit_obj->tex->mat_2->color->b = hit_obj->tex->mat_1->color->b;
	tmp = fabs(perlin_noise_3d(hit_pt->crd, hit_obj->tex->freq,
				hit_obj->tex->octa));
	add_color_to_mat(hit_obj, tmp);
	vector_rotation(hit_pt->crd, hit_obj, 0);
	return (hit_obj->tex->mat_2);
}

static t_mat	*fuse_dot_plane(t_hit_pt *hit_pt, t_obj *hit_obj)
{
	float	tmp_1;
	float	tmp_2;
	float	tmp_3;

	vector_rotation(hit_pt->crd, hit_obj, 1);
	tmp_1 = (1 + sin(hit_obj->norm_freq * hit_pt->crd->x)) / 2.0;
	tmp_2 = (1 + sin(hit_obj->norm_freq * hit_pt->crd->y)) / 2.0;
	tmp_3 = (1 + sin(hit_obj->norm_freq * hit_pt->crd->z)) / 2.0;
	if ((hit_obj->tex->mat_2->color->r = (hit_obj->tex->mat_1->color->r *
			tmp_1 + hit_obj->tex->mat_img->color->r * tmp_2) * tmp_3) > 1)
		hit_obj->tex->mat_2->color->r = 1;
	if ((hit_obj->tex->mat_2->color->g = (hit_obj->tex->mat_1->color->g *
			tmp_1 + hit_obj->tex->mat_img->color->g * tmp_2) * tmp_3) > 1)
		hit_obj->tex->mat_2->color->g = 1;
	if ((hit_obj->tex->mat_2->color->b = (hit_obj->tex->mat_1->color->b *
			tmp_1 + hit_obj->tex->mat_img->color->b * tmp_2) * tmp_3) > 1)
		hit_obj->tex->mat_2->color->b = 1;
	vector_rotation(hit_pt->crd, hit_obj, 0);
	return (hit_obj->tex->mat_2);
}

t_mat			*hit_material(t_hit_pt *hit_pt, t_obj *obj)
{
	if (obj->tex->type == 2)
	{
		if (obj->type == 1)
			return (checker_xy_plane(hit_pt, obj));
		else
			return (checker_xy_sph_cyl_cone(hit_pt, obj));
	}
	else if (obj->tex->type == 3)
	{
		if (obj->type == 1)
			return (img_xy_plane(hit_pt, obj));
		else
			return (img_xy_sph_cyl_cone(hit_pt, obj));
	}
	else if (obj->tex->type == 4)
	{
		if (obj->type == 1)
			return (perlin_plane(hit_pt, obj));
		else
			return (perlin_sph_cyl_cone(hit_pt, obj));
	}
	else if (obj->tex->type == 5)
		return (fuse_dot_plane(hit_pt, obj));
	else
		return (obj->tex->mat_1);
}
