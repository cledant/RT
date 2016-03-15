/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:18:42 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/14 20:34:59 by cledant          ###   ########.fr       */
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
	env->aa += 1;
	if (keycode == 53)
		// exit(ft_free_env(env));
		exit(0);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	*env;

	if (!(env = (t_env *)malloc(sizeof(t_env))))
		malloc_error();
	if (ac != 2)
		arg_error(ac);
	init(av[1], env);
	debug(env);
	raytracer(env);
	// ft_draw(env);
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_expose_hook(env->win, ft_expose_hook, env);
	mlx_loop(env->mlx);
	return (0);
}
