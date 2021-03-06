/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:22:04 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 15:32:57 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ambient(t_color *color, t_obj *obj, double coef)
{
	color->r = obj->mat->color->r * coef;
	color->g = obj->mat->color->g * coef;
	color->b = obj->mat->color->b * coef;
}

static void	specular(t_color *color, t_hit_pt *hit_pt, \
					t_ray *light_ray, t_obj *obj)
{
	t_vector3	*refl;
	double		coef_spec;

	refl = refle_vec(hit_pt->normal, hit_pt->root_ray->vec);
	coef_spec = (light_ray->vec->x * refl->x) + \
				(light_ray->vec->y * refl->y) + \
				(light_ray->vec->z * refl->z);
	if (coef_spec <= EPSILON)
		return ;
	coef_spec = pow(coef_spec, obj->mat->spec);
	color->r += coef_spec * light_ray->intensity;
	color->g += coef_spec * light_ray->intensity;
	color->b += coef_spec * light_ray->intensity;
}

static void	diffuse(t_color *col_obj, t_color *color, \
					t_hit_pt *hit_pt, t_ray *light_ray)
{
	double	k;

	k = (light_ray->vec->x * hit_pt->normal->x) + \
		(light_ray->vec->y * hit_pt->normal->y) + \
		(light_ray->vec->z * hit_pt->normal->z);
	if (k <= EPSILON)
		return ;
	color->r += col_obj->r * k * light_ray->intensity * hit_pt->diff_rate;
	color->g += col_obj->g * k * light_ray->intensity * hit_pt->diff_rate;
	color->b += col_obj->b * k * light_ray->intensity * hit_pt->diff_rate;
}

static void	while_part_1(t_light *tmp_light, t_ray *light_ray, t_hit_pt *hit_pt)
{
	vec_cpy(light_ray->crd, hit_pt->crd);
	if (tmp_light->type == 0)
	{
		set_vec(light_ray->vec, hit_pt->crd, tmp_light->crd);
		light_ray->intensity = tmp_light->intensity / get_dist(hit_pt->crd,
				tmp_light->crd) / hit_pt->light_sum;
	}
	else
	{
		vec_cpy(light_ray->vec, tmp_light->vec);
		light_ray->intensity = tmp_light->intensity / hit_pt->light_sum;
	}
	normalise(light_ray->vec);
}

t_color		*calc_color(t_hit_pt *hit_pt, t_obj *hit_obj, t_env *e)
{
	t_color	*color;
	t_light	*tmp_light;
	t_ray	light_ray;

	if (!(color = (t_color *)malloc(sizeof(t_color))))
		malloc_error();
	small_malloc(&light_ray);
	tmp_light = e->light_lst;
	ambient(color, hit_obj, e->ambient);
	while (tmp_light)
	{
		while_part_1(tmp_light, &light_ray, hit_pt);
		if ((hit_pt->diff_rate = is_in_shadow(e, &light_ray, color,
						tmp_light)) > 0)
		{
			hit_obj->mat = hit_material(hit_pt, hit_obj);
			diffuse(hit_obj->mat->color, color, hit_pt, &light_ray);
			if (hit_obj->mat->spec > 0)
				specular(color, hit_pt, &light_ray, hit_obj);
		}
		tmp_light = tmp_light->next;
	}
	free(light_ray.crd);
	free(light_ray.vec);
	return (color);
}
