/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:18:42 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/30 17:19:24 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	get_csg(t_env *e, t_csg *csg)
{
	e->menu->obj_name = "Complexe";
	e->menu->data[0] = &(csg->crd->x);
	e->menu->data[1] = &(csg->crd->y);
	e->menu->data[2] = &(csg->crd->z);
	e->menu->data[3] = &(csg->rx[0]);
	e->menu->data[4] = &(csg->ry[0]);
	e->menu->data[5] = &(csg->rz[0]);
}

void		find_csg(t_env *e, int i)
{
	t_csg	*csg_tmp;
	t_csg	*previous;

	csg_tmp = e->csg_lst;
	previous = csg_tmp;
	while (csg_tmp && (i++ < e->menu->ind_elem || e->menu->ind_elem == -1))
	{
		previous = csg_tmp;
		csg_tmp = csg_tmp->next;
	}
	if (csg_tmp || e->menu->ind_elem == -1)
	{
		if (csg_tmp)
			get_csg(e, csg_tmp);
		else
		{
			e->menu->ind_elem = i - 1;
			get_csg(e, previous);
		}
	}
	else
	{
		e->menu->ind_elem = 0;
		get_cam(e);
	}
}

static int	ft_expose_hook(t_env *env)
{
	if (!env)
		return (1);
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
	print_menu(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 200, 0);
	raytracer(env, env->addr);
	print_menu(env);
	mlx_key_hook(env->win, ft_key_hook, env);
	mlx_expose_hook(env->win, ft_expose_hook, env);
	mlx_hook(env->win, 4, (1L << 0), &mouse_press, env);
	mlx_loop(env->mlx);
	return (0);
}
