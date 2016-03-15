/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_lux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 09:23:06 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 08:45:53 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_ambient_light(int *color, t_env *env)
{
	color[0] = env->obj_cur->color->r * AMBIANT;
	color[1] = env->obj_cur->color->g * AMBIANT;
	color[2] = env->obj_cur->color->b * AMBIANT;
	color[3] = (env->obj_cur->color->r - color[0]) / env->light_nbr;
	color[4] = (env->obj_cur->color->g - color[1]) / env->light_nbr;
	color[5] = (env->obj_cur->color->b - color[2]) / env->light_nbr;
}

static void	ft_specular_highlight(int *color, float *k, float *n, t_env *env)
{
	float	r[3];
	float	v[3];

	v[0] = 0 - env->ray_cur->vec->x;
	v[1] = 0 - env->ray_cur->vec->y;
	v[2] = 0 - env->ray_cur->vec->z;
	k[1] = 2 * k[0] * k[2] / k[3];
	r[0] = k[1] * n[0] - env->ray->vec->x;
	r[1] = k[1] * n[1] - env->ray->vec->y;
	r[2] = k[1] * n[2] - env->ray->vec->z;
	k[0] = (v[0] * r[0]) + (v[1] * r[1]) + (v[2] * r[2]);
	if (k[0] <= EPSILON)
		return ;
	k[2] = sqrtf(env->ray_cur->vec->pow2_x + env->ray_cur->vec->pow2_y + env->ray_cur->vec->pow2_z);
	k[3] = sqrtf(env->ray->vec->pow2_x + env->ray->vec->pow2_y + env->ray->vec->pow2_z);
	if ((k[1] = k[2] * k[3]) <= EPSILON)
		return ;
	if ((k[0] /= k[1]) > 1)
		k[0] = 1;
	k[1] = (LIGHT_INT / env->light_nbr) * powf(k[0], SPECULAR_POW);
	color[0] += k[1];
	color[1] += k[1];
	color[2] += k[1];
}

static void	ft_diffuse_light(int *color, t_env *env)
{
	t_vec	*lux;
	float	n[6];
	float	k[4];

	ft_normal(n, env);
	lux = env->ray->vec;
	k[0] = (lux->x * n[0]) + (lux->y * n[1]) + (lux->z * n[2]);
	if (k[0] <= EPSILON)
		return ;
	k[2] = sqrtf(lux->pow2_x + lux->pow2_y + lux->pow2_z);
	k[3] = sqrtf(n[3] + n[4] + n[5]);
	if ((k[1] = k[2] * k[3]) <= EPSILON)
		return ;
	k[0] /= k[1];
	color[0] += color[3] * k[0];
	color[1] += color[4] * k[0];
	color[2] += color[5] * k[0];
	return (ft_specular_highlight(color, k, n, env));
}

static void	ft_lux_collision(int *color, t_env *env)
{
	float	pt[4];
	float	*pt1;
	t_obj	*obj;
	int		i;

	i = 0;
	pt[3] = env->ray->vec->pow2_x + env->ray->vec->pow2_y + env->ray->vec->pow2_z;
	obj = env->obj_lst;
	while (obj)
	{
		pt1 = ft_ray_collision(obj, env->ray);
		if (ft_nearest_point(pt, pt1, env->ray->crd))
			i = 1;
		obj = obj->next;
	}
	if (i)
		return ;
	return (ft_diffuse_light(color, env));
}

void		ft_lux_tracing(int *color, float *pt, t_env *env)
{
	if (!env->obj_cur)
		return ;
	ft_ambient_light(color, env);
	env->light_cur = env->light_lst;
	env->ray->crd->x = pt[0];
	env->ray->crd->y = pt[1];
	env->ray->crd->z = pt[2];
	while (env->light_cur)
	{
		env->ray->vec->x = env->light_cur->crd->x - pt[0];
		env->ray->vec->y = env->light_cur->crd->y - pt[1];
		env->ray->vec->z = env->light_cur->crd->z - pt[2];
		env->ray->vec->pow2_x = powf(env->ray->vec->x, 2);
		env->ray->vec->pow2_y = powf(env->ray->vec->y, 2);
		env->ray->vec->pow2_z = powf(env->ray->vec->z, 2);
		ft_lux_collision(color, env);
		env->light_cur = env->light_cur->next;
	}
}
