/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:31:07 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/14 13:36:46 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void cap_color(t_color *color)
{
  if (color->r > 1)
    color->r = 1;
  if (color->g > 1)
    color->g = 1;
  if (color->b > 1)
    color->b = 1;
}

static void calc_cam_ray(int x, int y, t_ray *cam_ray, t_env *e)
{
  float   depth;

  depth = (e->height / 2) / FOV;
  cam_ray->vec->x = depth;
  cam_ray->vec->y = e->width / 2 - x;
  cam_ray->vec->z = e->height / 2 - y;
  normalise(cam_ray->vec);
}

void raytracer(t_env *e)
{
  int x;
  int y;
  t_ray *cam_ray;
  t_hit_pt *hit_pt;

  x = 0;
  cam_ray = (t_ray *)malloc(sizeof(t_ray));
  cam_ray->vec = (t_vector3 *)malloc(sizeof(t_vector3));
  cam_ray->crd = e->cam->crd;
  while (x < e->width)
  {
    y = 0;
    while (y < e->height)
    {
      if ((x * e->width + y) % (e->width * e->height / 100) == 0)
        printf("|");
      e->nb_refle = 0;
      calc_cam_ray(x, y, cam_ray, e);
      hit_pt = get_color(cam_ray, e);
      cap_color(hit_pt->color);
      e->addr[y * e->size + x * e->bit / 8] = hit_pt->color->b * 255;
      e->addr[y * e->size + x * e->bit / 8 + 1] = hit_pt->color->g * 255;
      e->addr[y * e->size + x * e->bit / 8 + 2] = hit_pt->color->r * 255;
      y++;
    }
    x++;
  }
  printf("DONE\n");
}
