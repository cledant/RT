/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:31:07 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:52:01 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			calc_cam_ray(double x, double y, t_ray *cam_ray, t_env *e)
{
	double	depth;

	depth = (e->height / 2) / FOV;
	cam_ray->vec->x = depth;
	cam_ray->vec->y = e->width / 2 - x;
	cam_ray->vec->z = e->height / 2 - y;
	rotation_matrix(&(cam_ray->vec->x), &(cam_ray->vec->y), e->cam->rz, 0);
	rotation_matrix(&(cam_ray->vec->y), &(cam_ray->vec->z), e->cam->rx, 0);
	rotation_matrix(&(cam_ray->vec->z), &(cam_ray->vec->x), e->cam->ry, 0);
	normalise(cam_ray->vec);
}

static void		loading_bar(t_env *e, int x, int y)
{
	if ((x * e->width + y) % (e->width * e->height / 10) == 0 \
			|| x * y == (e->width - 1) * (e->height - 1))
	{
		mlx_put_image_to_window(e->mlx, e->win, e->img, 200, 0);
		print_loading(e);
		mlx_do_sync(e->mlx);
	}
	e->nb_refle = 0;
}

static void		small_free(t_ray *cam_ray)
{
	free(cam_ray->vec);
	free(cam_ray);
}

static void		aa_and_color(int x, int y, t_env *e, char *addr)
{
	t_hit_pt	*hit_pt;
	t_ray		*cam_ray;

	if (!(cam_ray = (t_ray *)malloc(sizeof(t_ray))))
		malloc_error();
	if (!(cam_ray->vec = (t_vector3 *)malloc(sizeof(t_vector3))))
		malloc_error();
	cam_ray->crd = e->cam->crd;
	if (e->aa == 0)
	{
		calc_cam_ray(x, y, cam_ray, e);
		hit_pt = get_color(cam_ray, e);
	}
	else
	{
		if (!(hit_pt = (t_hit_pt*)malloc(sizeof(t_hit_pt))))
			malloc_error();
		hit_pt->color = anti_aliasing(x, y, cam_ray, e);
	}
	cap_color(hit_pt->color);
	addr[y * e->size + x * e->bit / 8] = hit_pt->color->b * 255;
	addr[y * e->size + x * e->bit / 8 + 1] = hit_pt->color->g * 255;
	addr[y * e->size + x * e->bit / 8 + 2] = hit_pt->color->r * 255;
	free_hit_pt(hit_pt, e);
	small_free(cam_ray);
}

void			raytracer(t_env *e, char *addr)
{
	int			x;
	int			y;

	x = 0;
	while (x < e->width)
	{
		y = 0;
		while (y < e->height)
		{
			loading_bar(e, x, y);
			aa_and_color(x, y, e, addr);
			y++;
		}
		x++;
	}
}
