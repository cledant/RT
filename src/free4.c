/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 11:53:52 by vlize             #+#    #+#             */
/*   Updated: 2016/03/31 13:33:26 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_img_lst(t_env *e)
{
	t_img	*prev;

	while (e->img_lst != NULL)
	{
		prev = e->img_lst;
		e->img_lst = e->img_lst->next;
		free(prev->img);
		free(prev->data);
		free(prev);
	}
	free_tex_lst(e);
}

void		free_env(t_env *e)
{
	mlx_destroy_window(e->mlx, e->win);
	free(e->mlx);
	free(e->img);
	free(e->addr);
	free(e->img_load);
	free(e->addr_load);
	free(e->img_aa);
	free(e->addr_aa);
	free(e->img_cpy);
	free(e->addr_cpy);
	free(e->scene_name);
	free(e->background);
	free(e->menu->data);
	free(e->menu);
	free(e->cam->crd);
	free(e->cam);
	free_img_lst(e);
	free(e);
	exit(0);
}
