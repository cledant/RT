/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_normal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 14:58:06 by vlize             #+#    #+#             */
/*   Updated: 2016/03/04 10:44:31 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_plane_normal(float *n, t_env *env)
{
	n[0] = env->obj_cur->a;
	n[1] = env->obj_cur->b;
	n[2] = env->obj_cur->c;
	n[3] = env->obj_cur->pow2_a;
	n[4] = env->obj_cur->pow2_b;
	n[5] = env->obj_cur->pow2_c;
}

static void	ft_sphere_normal(float *n, t_env *env)
{
	n[0] = env->ray->crd->x - env->obj_cur->crd->x;
	n[1] = env->ray->crd->y - env->obj_cur->crd->y;
	n[2] = env->ray->crd->z - env->obj_cur->crd->z;
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_cylinder_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->ray->crd, env->obj_cur, 1);
	n[2] = 0;
	ft_vector_rotation(n, NULL, env->obj_cur, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_cone_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->ray->crd, env->obj_cur, 1);
	n[3] = env->obj_cur->tan_r * hypot(n[0], n[1]);
	if (n[2] < 0)
		n[2] = n[3];
	else
		n[2] = 0 - n[3];
	ft_vector_rotation(n, NULL, env->obj_cur, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

void		ft_normal(float *n, t_env *env)
{
	if (env->obj_cur->type == PLANE)
		ft_plane_normal(n, env);
	else if (env->obj_cur->type == SPHERE)
		ft_sphere_normal(n, env);
	else if (env->obj_cur->type == CONE)
		ft_cone_normal(n, env);
	else if (env->obj_cur->type == CYLINDER)
		ft_cylinder_normal(n, env);
	else
		ft_normal2(n, env);
	ft_normal_direction(n, env->ray_cur->vec);
}
