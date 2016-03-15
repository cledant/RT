/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_make.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 08:51:46 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 11:20:30 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void ft_set_not_null(char *str, float *nbr, t_env *env)
{
	ft_set_nbr(0, str, nbr, env);
	if (*nbr != 0)
		return ;
	env->line_nbr--;
	exit(ft_put_error(env->name, INVALID, env));
}

static void	ft_make_obj2(t_obj *obj, t_env *env)
{
	obj->sign = 1;
	if (obj->type != HYPERBOLOID)
	{
		if (!ft_strcmp(env->line, SHEET1))
			obj->sign = -1;
		else if (ft_strcmp(env->line, SHEET2))
			exit(ft_put_error(env->name, INVALID, env));
		ft_inc_gnl(env);
		return ;
	}
	if (obj->type == HYPERBOLIC)
		obj->sign = -1;
	else if (obj->type != ELLIPTIC)
		exit(ft_put_error(env->name, INVALID, env));
	ft_inc_gnl(env);
}

static void	ft_make_obj1(t_obj *obj, t_env *env)
{
	ft_set_not_null(A, &obj->a, env);
	ft_set_not_null(B, &obj->b, env);
	ft_set_not_null(C, &obj->c, env);
	obj->pow2_a = powf(obj->a, 2);
	obj->pow2_b = powf(obj->b, 2);
	obj->pow2_c = powf(obj->c, 2);
	if (obj->type != PARABOLOID)
	{
		ft_set_not_null(R, &obj->r, env);
		obj->pow2_r = powf(obj->r, 2);
	}
	if (obj->type != ELLIPSOID)
		return (ft_make_obj2(obj, env));
}

static void	ft_make_obj_cur(t_obj *obj, t_env *env)
{
	t_obj *tmp;

	if (obj->type == CONE)
	{
		ft_set_nbr(1, R, &obj->r, env);
		obj->tan_r = tan(obj->r);
		obj->tan2_r = powf(obj->tan_r, 2);
	}
	else if (obj->type == TORUS)
	{
		ft_set_nbr(0, R, &obj->r, env);
		ft_set_nbr(0, RT, &obj->rt, env);
		obj->pow2_r = powf(obj->r, 2);
		obj->pow2_rt = powf(obj->rt, 2);
	}
	else if (ft_end_with_oid(obj->type))
		ft_make_obj1(obj, env);
	else if (obj->type != PLANE)
	{
		ft_set_nbr(0, R, &obj->r, env);
		obj->pow2_r = powf(obj->r, 2);
	}
	tmp = env->obj_lst;
	env->obj_lst = obj;
	obj->next = tmp;
}

void		ft_make_obj(t_env *env)
{
	t_obj *obj;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		exit(ft_perror(MALLOC, env));
	if (!(obj->color = (t_color *)malloc(sizeof(t_color))))
		exit(ft_perror(MALLOC, env));
	if (!(obj->crd = (t_crd *)malloc(sizeof(t_crd))))
		exit(ft_perror(MALLOC, env));
	if (ft_strcmp(env->line, "cone") == 0)
		obj->type = 1;
	else if (ft_strcmp(env->line, "tore") == 0)
		obj->type = 2;
	else if (ft_strcmp(env->line, "plane") == 0)
		obj->type = 3;
	else if (ft_strcmp(env->line, "sphere") == 0)
		obj->type = 4;
	else if (ft_strcmp(env->line, "cylinder") == 0)
		obj->type = 5;
	else if (ft_strcmp(env->line, "ellipsoid") == 0)
		obj->type = 6;
	else if (ft_strcmp(env->line, "paraboloid") == 0)
		obj->type = 7;
	else if (ft_strcmp(env->line, "hyperboloid") == 0)
		obj->type = 8;
	else if (ft_strcmp(env->line, "mobius_strip") == 0)
		obj->type = 9;
	else if (ft_strcmp(env->line, "hyperbolic") == 0)
		obj->type = 10;
	else if (ft_strcmp(env->line, "elliptic") == 0)
		obj->type = 11;
	obj->next = NULL;
	obj->id = env->obj_nbr++;
	ft_inc_gnl(env);
	ft_set_hex(obj, env);
	ft_set_nbr(0, PX, &obj->crd->x, env);
	ft_set_nbr(0, PY, &obj->crd->y, env);
	ft_set_nbr(0, PZ, &obj->crd->z, env);
	if (obj->type != SPHERE)
	{
		ft_set_nbr(2, RX, obj->rx, env);
		ft_set_nbr(2, RY, obj->ry, env);
		ft_set_nbr(2, RZ, obj->rz, env);
		ft_vector_equation(obj);
	}
	return (ft_make_obj_cur(obj, env));
}
