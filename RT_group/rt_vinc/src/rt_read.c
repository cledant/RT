/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2016/02/29 11:11:09 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_make_light(t_env *env)
{
	t_light	*light;
	t_light	*tmp;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		exit(ft_perror(MALLOC, env));
	if (!(light->crd = (t_crd *)malloc(sizeof(t_crd))))
		exit(ft_perror(MALLOC, env));
	light->next = NULL;
	ft_inc_gnl(env);
	ft_set_nbr(0, PX, &light->crd->x, env);
	ft_set_nbr(0, PY, &light->crd->y, env);
	ft_set_nbr(0, PZ, &light->crd->z, env);
	env->light_nbr++;
	tmp = env->light_lst;
	env->light_lst = light;
	light->next = tmp;
}

static void	ft_make_cam(t_cam *cam, t_env *env)
{
	while ((ft_inc_gnl(env) > 0) && ft_strcmp(env->line, CAM))
	{
		if (env->line && (env->line[0] != '\0') && (env->line[0] != '#'))
			exit(ft_put_error(env->name, INVALID, env));
	}
	if (env->gnl < 0)
		exit(ft_perror(GNL, env));
	else if (env->gnl == 0)
		exit(ft_put_error(env->name, INVALID, env));
	ft_inc_gnl(env);
	ft_set_nbr(0, PX, &cam->crd->x, env);
	ft_set_nbr(0, PY, &cam->crd->y, env);
	ft_set_nbr(0, PZ, &cam->crd->z, env);
	ft_set_nbr(2, RX, cam->rx, env);
	ft_set_nbr(2, RY, cam->ry, env);
	ft_set_nbr(2, RZ, cam->rz, env);
	//cam->pow2_crd->x = powf(cam->crd->x, 2);
	//cam->pow2_crd->y = powf(cam->crd->y, 2);
	//cam->pow2_crd->z = powf(cam->crd->z, 2);
}

void		ft_read_file(t_env *env)
{
	ft_make_cam(env->cam, env);
	while (ft_inc_gnl(env) > 0)
	{
		if (!ft_strcmp(env->line, "light"))
			ft_make_light(env);
		else if (ft_is_object_char(env->line))
			ft_make_obj(env);
		if (env->line && (env->line[0] != '\0') && (env->line[0] != '#'))
			exit(ft_put_error(env->name, INVALID, env));
	}
	if (env->gnl < 0)
		exit(ft_perror(GNL, env));
	if (!env->light_nbr)
		env->light_nbr++;
}
