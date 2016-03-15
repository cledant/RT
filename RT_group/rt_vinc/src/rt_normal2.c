/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_normal2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 14:16:08 by vlize             #+#    #+#             */
/*   Updated: 2016/03/04 10:42:40 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_tore_normal(float *n, t_env *env)
{
	float	k;

	ft_vector_rotation(n, env->ray->crd, env->obj_cur, 1);
	k = 0;
	if (n[0] || n[1])
		k = 1 - sqrtf(env->obj_cur->rt / (hypot(n[0], n[1])));
	n[0] *= k;
	n[1] *= k;
	ft_vector_rotation(n, NULL, env->obj_cur, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_paraboloid_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->ray->crd, env->obj_cur, 1);
	n[0] = 2 * n[0] / env->obj_cur->pow2_a;
	n[1] = env->obj_cur->sign * 2 * n[1] / env->obj_cur->pow2_b;
	n[2] = -1 / env->obj_cur->c;
	ft_vector_rotation(n, NULL, env->obj_cur, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_hyperboloid_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->ray->crd, env->obj_cur, 1);
	n[0] = 2 * n[0] / env->obj_cur->pow2_a;
	n[1] = 2 * n[1] / env->obj_cur->pow2_b;
	n[2] = -2 * n[2] / env->obj_cur->pow2_c;
	ft_vector_rotation(n, NULL, env->obj_cur, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_ellipsoid_normal(float *n, t_env *env)
{
	ft_vector_rotation(n, env->ray->crd, env->obj_cur, 1);
	n[0] = 2 * n[0] / env->obj_cur->pow2_a;
	n[1] = 2 * n[1] / env->obj_cur->pow2_b;
	n[2] = 2 * n[2] / env->obj_cur->pow2_c;
	ft_vector_rotation(n, NULL, env->obj_cur, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

static void	ft_mobius_strip_normal(float *n, t_env *env)
{
	float	p[3];
	float	pow2_p[3];

	ft_vector_rotation(p, env->ray->crd, env->obj_cur, 1);
	pow2_p[0] = powf(p[0], 2);
	pow2_p[1] = powf(p[1], 2);
	pow2_p[2] = powf(p[2], 2);
	n[0] = 2 * (p[0] * (p[1] - 2 * p[2]) - env->obj_cur->a * p[2]);
	n[1] = 3 * pow2_p[1] - 2 * p[2] * p[1] + pow2_p[0] + pow2_p[2];
	n[1] -= env->obj_cur->pow2_a;
	n[2] = 2 * (p[1] * p[2] - pow2_p[1] - pow2_p[0] - env->obj_cur->a * p[0]);
	ft_vector_rotation(n, NULL, env->obj_cur, 0);
	n[3] = powf(n[0], 2);
	n[4] = powf(n[1], 2);
	n[5] = powf(n[2], 2);
}

void		ft_normal2(float *n, t_env *env)
{
	if (env->obj_cur->type == TORUS)
		ft_tore_normal(n, env);
	else if (env->obj_cur->type == PARABOLOID)
		ft_paraboloid_normal(n, env);
	else if (env->obj_cur->type == HYPERBOLOID)
		ft_hyperboloid_normal(n, env);
	else if (env->obj_cur->type == ELLIPSOID)
		ft_ellipsoid_normal(n, env);
	else if (env->obj_cur->type == MOBIUS_STRIP)
		ft_mobius_strip_normal(n, env);
}
