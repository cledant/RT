/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:22:04 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/14 20:47:54 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ambient(t_color *color, t_obj *obj, float coef, t_hit_pt *hit_pt)
{
	if (obj->mat->tex != NULL && obj->mat->tex->type == 0)
		texture_ambiant(color, coef, hit_pt, obj);
	else
	{
		color->r = obj->mat->color->r * coef;
		color->g = obj->mat->color->g * coef;
		color->b = obj->mat->color->b * coef;
	}
	// color[3] = (env->obj_cur->color->r - color[0]) / env->light_nbr;
	// color[4] = (env->obj_cur->color->g - color[1]) / env->light_nbr;
	// color[5] = (env->obj_cur->color->b - color[2]) / env->light_nbr;
}

static void	specular(t_color *color, t_hit_pt *hit_pt, t_ray *light_ray, t_obj *obj)
{
	t_vector3	*refl;
  float coef_spec;

	refl = refle_vec(hit_pt->normal, hit_pt->root_ray->vec);
	coef_spec = (light_ray->vec->x * refl->x) + (light_ray->vec->y * refl->y) +
        (light_ray->vec->z * refl->z);
	if (coef_spec <= EPSILON)
		return ;
	coef_spec = pow(coef_spec, obj->mat->spec);
	color->r += coef_spec;
	color->g += coef_spec;
	color->b += coef_spec;
}

static void	diffuse(t_color *col_obj, t_color *color, t_vector3 *normal, t_ray *light_ray)
{
	float	k;

	// lux = env->ray->vec;
	k = (light_ray->vec->x * normal->x) + (light_ray->vec->y * normal->y) +
    (light_ray->vec->z * normal->z);
	if (k <= EPSILON)
		return ;
	// k[2] = sqrtf(light_ray->vec->x * light_ray->vec->x + light_ray->vec->y *
  //   light_ray->vec->y + light_ray->vec->z * light_ray->vec->z);
	// k[3] = sqrtf(normal->x * normal->x + normal->x * normal->x + normal->x * normal->x);
	// if ((k[1] = k[2] * k[3]) <= EPSILON)
	// 	return ;
	// k[0] /= k[1];
	// printf("k: %f\n", k);
	color->r += col_obj->r * k;//fonctionne pour une lumiere
	color->g += col_obj->g * k;
	color->b += col_obj->b * k;
}

static int  is_in_shadow(t_obj *obj_lst, t_ray *light_ray)
{
	t_vector3 *hit_pt;
	t_obj	*obj_tmp;

	obj_tmp = obj_lst;
	while (obj_tmp)
	{
		hit_pt = ray_collision(obj_tmp, light_ray);
		if (hit_pt)
      return (1);
		obj_tmp = obj_tmp->next;
	}
	return (0);
}

t_color   *calc_color(t_hit_pt *hit_pt, t_obj *hit_obj, t_env *e)
{
  t_color *color;
  t_light *tmp_light;
  t_ray light_ray;

  color = (t_color *)malloc(sizeof(t_color));
  light_ray.crd = (t_vector3*)malloc(sizeof(t_vector3));
  light_ray.vec = (t_vector3*)malloc(sizeof(t_vector3));
  tmp_light = e->light_lst;
  ambient(color, hit_obj, e->ambient, hit_pt);
  while (tmp_light)
  {
    light_ray.crd->x = tmp_light->crd->x;
    light_ray.crd->y = tmp_light->crd->y;
    light_ray.crd->z = tmp_light->crd->z;
    light_ray.vec->x = tmp_light->crd->x - hit_pt->crd->x;
    light_ray.vec->y = tmp_light->crd->y - hit_pt->crd->y;
    light_ray.vec->z = tmp_light->crd->z - hit_pt->crd->z;
		normalise(light_ray.vec);
  	if (!is_in_shadow(e->obj_lst, &light_ray))
    {
      diffuse(hit_obj->mat->color, color, hit_pt->normal, &light_ray);
      if (hit_obj->mat->spec > 0)
        specular(color, hit_pt, &light_ray, hit_obj);
    }
    tmp_light = tmp_light->next;
  }
  free(light_ray.crd);
  free(light_ray.vec);
  return (color);
}
