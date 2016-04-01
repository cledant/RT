/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:25:42 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:26:19 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		get_light_sum(t_hit_pt *hit_pt, t_light *light_lst)
{
	t_light	*tmp_light;

	hit_pt->light_sum = 0;
	tmp_light = light_lst;
	while (tmp_light)
	{
		if (tmp_light->type == 0)
			hit_pt->light_sum += tmp_light->intensity \
								/ get_dist(hit_pt->crd, tmp_light->crd);
		else
			hit_pt->light_sum += tmp_light->intensity;
		tmp_light = tmp_light->next;
	}
}

static void		change_normal(t_obj *hit_obj, t_hit_pt *hit_pt)
{
	if (hit_obj->type == 1 && hit_obj->norm_type == 1)
		sin_change_normal(hit_pt, hit_obj);
	if (hit_obj->norm_type == 2)
		perlin_change_normal(hit_pt, hit_obj);
	if (hit_obj->norm_type == 3)
		fuse_dot_change_normal(hit_pt, hit_obj);
	if (hit_obj->norm_type == 4)
		image_change_normal(hit_pt, hit_obj);
}

t_hit_pt		*get_color(t_ray *ray, t_env *e)
{
	t_hit_pt	*hit_pt;
	t_obj		*hit_obj;

	e->nb_rays += 1 + e->nb_lights;
	hit_pt = hit_pt_init(ray);
	if ((hit_pt->crd = find_intersect(ray, e, &hit_obj)))
	{
		hit_pt->hit_obj_id = hit_obj->id;
		get_light_sum(hit_pt, e->light_lst);
		check_normal(e->csg_lst, hit_pt->normal, hit_pt->crd, hit_obj);
		normal_direction(hit_pt->normal, ray->vec);
		change_normal(hit_obj, hit_pt);
		hit_obj->mat = hit_material(hit_pt, hit_obj);
		hit_pt->color = calc_color(hit_pt, hit_obj, e);
		if (hit_obj->mat->refl > 0 && e->nb_refle < MAX_REFLE)
			reflection(e, hit_obj, hit_pt);
		if (hit_obj->mat->trans > 0)
			transparency(e, hit_obj, hit_pt);
		return (hit_pt);
	}
	if (!(hit_pt->color = (t_color *)malloc(sizeof(t_color))))
		malloc_error();
	color_init_null(hit_pt->color);
	add_color(hit_pt->color, e->background, 0);
	return (hit_pt);
}
