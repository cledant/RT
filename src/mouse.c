/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/06 09:18:42 by thibautp          #+#    #+#             */
/*   Updated: 2016/03/30 14:02:13 by mbragard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	filter(t_env *e, int ind)
{
	e->menu->filter_button = ind;
	if (ind == 1)
		black_and_white(e);
	else if (ind == 2)
		sepia(e);
	else
	{
		if (e->menu->aa_button == 1)
			mlx_put_image_to_window(e->mlx, e->win, e->img_aa, 200, 0);
		else
			mlx_put_image_to_window(e->mlx, e->win, e->img, 200, 0);
	}
	print_menu(e);
}

static void	aa_option(t_env *e, int ind)
{
	e->menu->aa_button = ind;
	e->menu->filter_button = 0;
	if (ind == 1)
	{
		if (e->aa != 1)
		{
			e->aa = 1;
			raytracer(e, e->addr_aa);
		}
		mlx_put_image_to_window(e->mlx, e->win, e->img_aa, 200, 0);
	}
	else
		mlx_put_image_to_window(e->mlx, e->win, e->img, 200, 0);
	print_menu(e);
}

static void	reload(t_env *e)
{
	e->aa = 0;
	e->menu->aa_button = 0;
	e->menu->filter_button = 0;
	print_menu(e);
	raytracer(e, e->addr);
	print_menu(e);
}

static void	save(t_env *e)
{
	if (e->menu->filter_button != 0)
		save_image(e->addr_cpy, e);
	else if (e->menu->aa_button == 0)
		save_image(e->addr, e);
	else
		save_image(e->addr_aa, e);
}

int			mouse_press(int button, int x, int y, t_env *e)
{
	if (e->menu->selected != 0 || button != 1)
		return (0);
	if (x >= 11 && x <= 35 && y >= 40 && y <= 70)
		switch_obj(e, -1);
	if (x >= 161 && x <= 185 && y >= 40 && y <= 70)
		switch_obj(e, 1);
	if (x >= 61 && x <= 130 && y >= 283 && y <= 312)
		reload(e);
	if (x >= 21 && x <= 90 && y >= 362 && y <= 391)
		filter(e, 1);
	if (x >= 111 && x <= 180 && y >= 362 && y <= 391)
		filter(e, 2);
	if (x >= 61 && x <= 130 && y >= 403 && y <= 432)
		filter(e, 0);
	if (x >= 21 && x <= 90 && y >= 483 && y <= 512)
		aa_option(e, 1);
	if (x >= 111 && x <= 180 && y >= 483 && y <= 512)
		aa_option(e, 0);
	if (x >= 0 && x <= 200 && ((y >= 200 && y <= 260)
		|| (y >= 100 && y <= 160)))
		selection(e, y);
	if (x >= 26 && x <= 175 && y >= 562 && y <= 592)
		save(e);
	return (0);
}
