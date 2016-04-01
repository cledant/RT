/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/28 13:38:10 by vlize             #+#    #+#             */
/*   Updated: 2016/03/30 17:42:43 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	transparency_init(t_ray *refr_ray, t_obj *hit_obj, t_hit_pt *hit_pt)
{
	hit_pt->color->r *= (100.0 - hit_obj->mat->trans) / 100.0;
	hit_pt->color->g *= (100.0 - hit_obj->mat->trans) / 100.0;
	hit_pt->color->b *= (100.0 - hit_obj->mat->trans) / 100.0;
	if (!(refr_ray->crd = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	vec_cpy(refr_ray->crd, hit_pt->crd);
	refr_ray->crd->x += hit_pt->root_ray->vec->x;
	refr_ray->crd->y += hit_pt->root_ray->vec->y;
	refr_ray->crd->z += hit_pt->root_ray->vec->z;
	refr_ray->vec = refre_vec(hit_pt->normal, hit_pt->root_ray->vec, 1, \
			hit_obj->mat->ind_trans);
}

void		transparency(t_env *env, t_obj *hit_obj, t_hit_pt *hit_pt)
{
	t_hit_pt	*hit_pt_refr;
	t_ray		refr_ray;
	t_vector3	normal;
	t_vector3	tmp;
	double		k[4];

	transparency_init(&refr_ray, hit_obj, hit_pt);
	vec_cpy(&tmp, refr_ray.vec);
	new_point(refr_ray.crd, refr_ray.vec, refr_ray.crd, k[0]);
	check_normal(env->csg_lst, &normal, refr_ray.crd, hit_obj);
	normal.x *= -1;
	normal.y *= -1;
	normal.z *= -1;
	refr_ray.vec = refre_vec(&normal, &tmp, hit_obj->mat->ind_trans, 1);
	hit_pt_refr = get_color(&refr_ray, env);
	cap_color(hit_pt_refr->color);
	hit_pt->color->r += hit_obj->mat->trans / 100.0 * hit_pt_refr->color->r;
	hit_pt->color->g += hit_obj->mat->trans / 100.0 * hit_pt_refr->color->g;
	hit_pt->color->b += hit_obj->mat->trans / 100.0 * hit_pt_refr->color->b;
	free_hit_pt(hit_pt_refr, env);
}

void		reflection(t_env *env, t_obj *hit_obj, t_hit_pt *hit_pt)
{
	t_hit_pt	*hit_pt_refl;
	t_ray		refl_ray;

	env->nb_refle++;
	hit_pt->color->r *= (100.0 - hit_obj->mat->refl) / 100.0;
	hit_pt->color->g *= (100.0 - hit_obj->mat->refl) / 100.0;
	hit_pt->color->b *= (100.0 - hit_obj->mat->refl) / 100.0;
	refl_ray.vec = refle_vec(hit_pt->normal, hit_pt->root_ray->vec);
	refl_ray.crd = hit_pt->crd;
	hit_pt_refl = get_color(&refl_ray, env);
	cap_color(hit_pt_refl->color);
	hit_pt->color->r += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->r;
	hit_pt->color->g += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->g;
	hit_pt->color->b += hit_obj->mat->refl / 100.0 * hit_pt_refl->color->b;
	if (hit_pt->diff_rate == -1)
	{
		hit_pt->color->r *= env->ambient * 2;
		hit_pt->color->g *= env->ambient * 2;
		hit_pt->color->b *= env->ambient * 2;
	}
	free(refl_ray.vec);
	free_hit_pt(hit_pt_refl, env);
}
