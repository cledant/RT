/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 09:36:58 by vlize             #+#    #+#             */
/*   Updated: 2016/03/14 15:34:57 by cledant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_mlx(t_env *e)
{
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->width, e->height, e->scene_name);
	e->img = mlx_new_image(e->mlx, e->width, e->height);
	e->addr = mlx_get_data_addr(e->img, &e->bit, &e->size, &e->end);
}

void init(char *arg, t_env *env)
{
	int fd;

	fd = open(arg, O_RDONLY);
	parsing(fd, env);
	close(fd);
}
