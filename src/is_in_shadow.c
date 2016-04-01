/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 08:38:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/31 16:01:14 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_shadow(t_env *e, t_obj *obj, t_color *color, double dist)
{
	double	amb;

	amb = 1;
	if ((obj->mat->trans == 0) && (dist < EPSILON))
		return (1);
	else if (dist < EPSILON)
	{
		if (color->r + color->g + color->b != 0.0)
			amb = e->ambient;
		color->r += obj->mat->color->r * ((50.0 - fabs(50.0 -
						obj->mat->trans)) / 100.0) * amb;
		color->g += obj->mat->color->g * ((50.0 - fabs(50.0 -
						obj->mat->trans)) / 100.0) * amb;
		color->b += obj->mat->color->b * ((50.0 - fabs(50.0 -
						obj->mat->trans)) / 100.0) * amb;
	}
	if (e->trans_tmp == 0.0)
		e->trans_tmp = (obj->mat->trans) / 100.0;
	else
		e->trans_tmp *= (obj->mat->trans) / 100.0;
	return (0);
}

static int	interval_shadow(t_env *e, t_ray *l_ray, t_interval *i,
		t_color *color)
{
	t_vector3	hit_pt;

	if (i->min > EPSILON)
	{
		new_point(&hit_pt, l_ray->vec, l_ray->crd, i->min);
		e->light_dist[1] = get_dist(l_ray->crd, &hit_pt) - e->light_dist[0];
		if (check_shadow(e, i->obj_min, color, e->light_dist[1]))
			return (1);
	}
	if (i->max > EPSILON)
	{
		new_point(&hit_pt, l_ray->vec, l_ray->crd, i->max);
		e->light_dist[1] = get_dist(l_ray->crd, &hit_pt) - e->light_dist[0];
		if (check_shadow(e, i->obj_max, color, e->light_dist[1]))
			return (1);
	}
	return (0);
}

static int	csg_shadow(t_ray *l_ray, t_env *e, t_color *color)
{
	t_ray		tmp_ray;
	t_csg		*tmp_csg;
	t_interval	*tmp_i;
	t_interval	*i;

	tmp_csg = e->csg_lst;
	while (tmp_csg)
	{
		make_csg_ray(&tmp_ray, l_ray, tmp_csg);
		i = get_interval(tmp_csg->tree, &tmp_ray);
		tmp_i = i;
		while (tmp_i)
		{
			if (interval_shadow(e, &tmp_ray, tmp_i, color))
				return (free_tmp_interval(i, &tmp_ray));
			tmp_i = tmp_i->next;
		}
		free_tmp_interval(i, &tmp_ray);
		tmp_csg = tmp_csg->next;
	}
	return (0);
}

static int	obj_shadow(t_ray *l_ray, t_env *e, t_color *color)
{
	t_obj		*obj_tmp;
	t_hit_pt	hit_pt;
	double		k[4];

	hit_pt.crd = (t_vector3 *)malloc(sizeof(t_vector3));
	obj_tmp = e->obj_lst;
	while (obj_tmp)
	{
		if (smallest_k(obj_tmp, l_ray, k))
		{
			new_point(hit_pt.crd, l_ray->vec, l_ray->crd, k[0]);
			obj_tmp->mat = hit_material(&hit_pt, obj_tmp);
			e->light_dist[1] = get_dist(l_ray->crd, hit_pt.crd) -
				e->light_dist[0];
			if (check_shadow(e, obj_tmp, color, e->light_dist[1]))
				return (1);
		}
		obj_tmp = obj_tmp->next;
	}
	free(hit_pt.crd);
	return (0);
}

int			is_in_shadow(t_env *env, t_ray *light_ray, \
		t_color *color, t_light *light)
{
	t_color	color_tmp;

	color_tmp.r = 0;
	color_tmp.g = 0;
	color_tmp.b = 0;
	if (light->type == 0)
		env->light_dist[0] = get_dist(light->crd, light_ray->crd);
	else
		env->light_dist[0] = DBL_MAX;
	if (obj_shadow(light_ray, env, &color_tmp))
		return (-1);
	if (csg_shadow(light_ray, env, &color_tmp))
		return (-1);
	color->r += color_tmp.r;
	color->g += color_tmp.g;
	color->b += color_tmp.b;
	if (color_tmp.r + color_tmp.g + color_tmp.b != 0.0)
		return (env->trans_tmp);
	return (1);
}
