/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 10:38:16 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 08:45:03 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_light_light(int *color, float *k, t_env *env)
{
	k[0] = (env->ray_cur->vec->x * env->ray->vec->x) + (env->ray_cur->vec->y * env->ray->vec->y);
	if ((k[0] += env->ray_cur->vec->z * env->ray->vec->z) <= EPSILON)
		return ;
	if ((k[1] = k[2] * sqrtf(k[3])) <= EPSILON)
		return ;
	if ((k[0] /= k[1]) > 1)
		k[0] = 1;
	k[1] = light_LIGHT_INT * powf(k[0], light_LIGHT_POW);
	color[0] += k[1];
	color[1] += k[1];
	color[2] += k[1];
}

static void	ft_light_collision(int *color, float *k, t_env *env)
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
	k[3] = pt[3];
	return (ft_light_light(color, k, env));
}

void		ft_light_tracing(int *color, t_env *env)
{
	float	k[4];

	env->light_cur = env->light_lst;
	env->ray->crd->x = env->ray_cur->crd->x;
	env->ray->crd->y = env->ray_cur->crd->y;
	env->ray->crd->z = env->ray_cur->crd->z;
	k[2] = sqrtf(env->ray_cur->vec->pow2_x + env->ray_cur->vec->pow2_y + env->ray_cur->vec->pow2_z);
	while (env->light_cur)
	{
		env->ray->vec->x = env->light_cur->crd->x - env->ray->crd->x;
		env->ray->vec->y = env->light_cur->crd->y - env->ray->crd->y;
		env->ray->vec->z = env->light_cur->crd->z - env->ray->crd->z;
		env->ray->vec->pow2_x = powf(env->ray->vec->x, 2);
		env->ray->vec->pow2_y = powf(env->ray->vec->y, 2);
		env->ray->vec->pow2_z = powf(env->ray->vec->z, 2);
		ft_light_collision(color, k, env);
		env->light_cur = env->light_cur->next;
	}
}
