/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2015/12/28 16:58:39 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_free_light(t_light *light)
{
	t_light *tmp;

	while (light)
	{
		tmp = light->next;
		free(light);
		light = tmp;
	}
}

static void	ft_free_obj(t_obj *obj)
{
	t_obj *tmp;

	while (obj)
	{
		tmp = obj->next;
		free(obj);
		obj = tmp;
	}
}

int			ft_free_env(t_env *env)
{
	if (!env)
		return (0);
	if (env->mlx && env->img)
		mlx_destroy_image(env->mlx, env->img);
	if (env->mlx && env->win)
		mlx_destroy_window(env->mlx, env->win);
	ft_free_light(env->light_lst);
	ft_free_obj(env->obj_lst);
	if (env->ray_cur)
		free(env->ray_cur);
	if (env->ray)
		free(env->ray);
	if (env->cam)
		free(env->cam);
	if ((env->fd > 2) && close(env->fd))
		ft_perror(CLOSE, NULL);
	ft_free(env);
	return (0);
}

int			ft_perror(char *name, t_env *env)
{
	ft_putstr_fd(PROG, 2);
	ft_putstr_fd(": ", 2);
	perror(name);
	return (ft_free_env(env));
}

int			ft_put_error(char *name, char *msg, t_env *env)
{
	ft_putstr_fd(PROG, 2);
	ft_putstr_fd(": ", 2);
	if (name)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	if (!ft_strcmp(msg, INVALID))
	{
		ft_putstr_fd(" (error line ", 2);
		ft_putnbr_fd(env->line_nbr, 2);
		ft_putchar_fd(')', 2);
	}
	write(1, "\n", 1);
	return (ft_free_env(env));
}
