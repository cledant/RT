/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/21 15:45:00 by vlize             #+#    #+#             */
/*   Updated: 2015/12/28 16:36:38 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	ft_expose_hook(t_env *env)
{
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

static int	ft_key_hook(int keycode, t_env *env)
{
	if (keycode == 53)
		exit(ft_free_env(env));
	return (0);
}

static void	ft_check_arg(int ac, char **av, t_env *env)
{
	env->fd = 0;
	if (ac < 2)
		exit(ft_put_error(NULL, "File name missing", env));
	else if (ac > 2)
		exit(ft_put_error(NULL, "Too many arguments", env));
	if ((env->fd = open(av[1], O_RDWR)) <= 2)
		exit(ft_perror(av[1], env));
	env->name = av[1];
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		return (ft_perror(MALLOC, env));
	ft_check_arg(ac, av, env);
	ft_init_env(env);
	ft_read_file(env);
	if ((env->fd = close(env->fd)))
		ft_perror(CLOSE, env);
	ft_init_vector(env->cam);
	ft_draw(env);
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_expose_hook(env->win, ft_expose_hook, env);
	return (mlx_loop(env->mlx));
}
