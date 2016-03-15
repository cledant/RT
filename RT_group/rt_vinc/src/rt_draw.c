/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/03/04 11:18:36 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_nearest_point(float pt[4], float *pt1, t_crd *crd)
{
	float	k;

	if (!pt1)
		return (0);
	k = powf((pt1[0] - crd->x), 2) + powf((pt1[1] - crd->y), 2);
	k += powf((pt1[2] - crd->z), 2);
	if (pt[3] <= k)
		return (0);
	pt[0] = pt1[0];
	pt[1] = pt1[1];
	pt[2] = pt1[2];
	pt[3] = k;
	return (1);
}

float		*ft_ray_collision(t_obj *obj, t_ray *ray)
{
	if (!obj || !ray)
		return (NULL);
	if (obj->type == PLANE)
		return (ft_plane(obj, ray));
	else if (obj->type == SPHERE)
		return (ft_sphere(obj, ray));
	else if (obj->type == CYLINDER)
		return (ft_cylinder(obj, ray));
	else if (obj->type == CONE)
		return (ft_cone(obj, ray));
	else if (obj->type == TORUS)
		return (ft_tore(obj, ray));
	else if (obj->type == ELLIPSOID)
		return (ft_ellipsoid(obj, ray));
	else if (obj->type == PARABOLOID)
		return (ft_paraboloid(obj, ray));
	else if (obj->type == HYPERBOLOID)
		return (ft_hyperboloid(obj, ray));
	else if (obj->type == MOBIUS_STRIP)
		return (ft_mobius_strip(obj, ray));
	return (NULL);
}

static void	ft_set_cam_vector(int i, int j, t_ray *ray, t_cam *cam)
{
	ray->crd->x = cam->crd->x;
	ray->crd->y = cam->crd->y;
	ray->crd->z = cam->crd->z;
	ray->vec->x = cam->x[i][j];
	ray->vec->y = cam->y[i][j];
	ray->vec->z = cam->z[i][j];
	ray->vec->pow2_x = cam->pow2_x[i][j];
	ray->vec->pow2_y = cam->pow2_y[i][j];
	ray->vec->pow2_z = cam->pow2_z[i][j];
}

static void	ft_ray_tracing(int *color, t_env *env)
{
	float		pt[4];
	float		*pt1;
	t_obj		*obj;

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	env->obj_cur = NULL;
	pt[3] = DBL_MAX;
	obj = env->obj_lst;
	while (obj)
	{
		pt1 = ft_ray_collision(obj, env->ray_cur);
		if (ft_nearest_point(pt, pt1, env->ray_cur->crd))
			env->obj_cur = obj;
		obj = obj->next;
	}
	return (ft_lux_tracing(color, pt, env));
}

void		ft_draw(t_env *env)
{
	int	color[6];
	int	pix;
	int	i;
	int	j;

	j = -1;
	pix = 0;
	while ((j += 1) < HEIGHT)
	{
		i = -1;
		while ((i += 1) < WIDTH)
		{
			env->nb_refle = 0;
			ft_set_cam_vector(i, j, env->ray_cur, env->cam);
			ft_ray_tracing(color, env);
			ft_light_tracing(color, env);
			ft_check_color(color);
			ft_memcpy(&env->addr[pix], &color[2], 1);
			ft_memcpy(&env->addr[pix + 1], &color[1], 1);
			ft_memcpy(&env->addr[pix + 2], &color[0], 1);
			pix += 4;
		}
	}
}
