/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:19:13 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/11 09:42:30 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	nearest_point(t_vector3 *pt1, t_vector3 *pt2, t_vector3 *ori)
{
	float	a;
  float b;

	if (!pt1 && !pt2)
		return (0);
  else if (!pt1 && pt2)
    return (1);
  else if (pt1 && !pt2)
    return (0);
	a = powf((pt1->x - ori->x), 2) + powf((pt1->y - ori->y), 2) + \
      powf((pt1->z - ori->z), 2);
  b = powf((pt2->x - ori->x), 2) + powf((pt2->y - ori->y), 2) + \
      powf((pt2->z - ori->z), 2);
  if (a >= b)
	  return (1);
  return (0);
}

t_vector3		*ray_collision(t_obj *obj, t_ray *ray)
{
	if (!obj || !ray)
		return (NULL);
	if (obj->type == PLANE)
		return (plane(obj, ray));
	else if (obj->type == SPHERE)
		return (sphere(obj, ray));
	else if (obj->type == CYLINDER)
	 	return (cylinder(obj, ray));
	else if (obj->type == CONE)
		return (cone(obj, ray));
	// else if (obj->type == ELLIPSOID)
	// 	return (ellipsoid(obj, ray));
	// else if (obj->type == PARABOLOID)
	// 	return (paraboloid(obj, ray));
	// else if (obj->type == HYPERBOLOID)
	// 	return (hyperboloid(obj, ray));
	return (NULL);
}

t_vector3 *find_intersect(t_ray *ray, t_obj *obj_lst, t_obj **hit_obj)
{
  t_obj     *tmp_lst;
  t_vector3 *pt;
  t_vector3 *tmp;

  tmp_lst = obj_lst;
	pt = NULL;
  while (tmp_lst)
  {
    tmp = ray_collision(tmp_lst, ray);
    if (nearest_point(pt, tmp, ray->crd))
    {
      pt = tmp;
      *hit_obj = tmp_lst;
    }
    tmp_lst = tmp_lst->next;
  }
  return (pt);
}
