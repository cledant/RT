/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 13:25:42 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/11 10:48:06 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_hit_pt *hit_pt_init(t_ray *ray)
{
  t_hit_pt  *hit_pt;

  hit_pt = (t_hit_pt *)malloc(sizeof(t_hit_pt));

  hit_pt->normal = (t_vector3 *)malloc(sizeof(t_vector3));
  hit_pt->root_ray = (t_ray *)malloc(sizeof(t_ray));
  hit_pt->root_ray->crd = (t_vector3 *)malloc(sizeof(t_vector3));
  hit_pt->root_ray->vec = (t_vector3 *)malloc(sizeof(t_vector3));

  hit_pt->root_ray->crd->x = ray->crd->x;
  hit_pt->root_ray->crd->y = ray->crd->y;
  hit_pt->root_ray->crd->z = ray->crd->z;
  hit_pt->root_ray->vec->x = ray->vec->x;
  hit_pt->root_ray->vec->y = ray->vec->y;
  hit_pt->root_ray->vec->z = ray->vec->z;
  return (hit_pt);
}

t_hit_pt *get_color(t_ray *ray, t_env *e)
{
    t_hit_pt  *hit_pt;
    t_obj     *hit_obj;

    hit_obj = (t_obj *)malloc(sizeof(t_obj));
    hit_obj = NULL;
    hit_pt = hit_pt_init(ray);
    hit_pt->crd = find_intersect(ray, e->obj_lst, &hit_obj);
    if (hit_pt->crd)
    {
      get_normal(hit_pt->normal, hit_obj, hit_pt->crd);
      hit_pt->color = calc_color(hit_pt, hit_obj, e);
      //reflection(e, hit_obj, hit_pt);
    }
    else
    {
      hit_pt->color = (t_color *)malloc(sizeof(t_color));
      hit_pt->color->r = e->background->b;
      hit_pt->color->g = e->background->g;
      hit_pt->color->b = e->background->r;
    }
    return (hit_pt);
}
