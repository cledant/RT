/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 14:15:21 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 14:08:26 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			center(char *text)
{
	int i;
	int x;

	i = 0;
	while (text[i] != '\0')
		i++;
	x = 100 - (i / 2) * 10 - (i % 2) * 5;
	if (x < 0)
		return (0);
	return (x);
}

static int	delete_loading(t_env *e)
{
	int i;
	int j;

	j = 0;
	while (j < 200)
	{
		i = 0;
		while (i < 20)
		{
			e->addr_load[i * e->size_load + j * e->bit_load / 8] = 0;
			e->addr_load[i * e->size_load + j * e->bit_load / 8 + 1] = 0;
			e->addr_load[i * e->size_load + j * e->bit_load / 8 + 2] = 0;
			i++;
		}
		j++;
	}
	return (0);
}

void		print_loading(t_env *e)
{
	static int	nb = 0;
	int			i;
	int			j;

	j = -1;
	while (++j < 20)
	{
		i = -1;
		while (++i < 20)
		{
			e->addr_load[i * e->size_load + (nb * 20 + j) *
				e->bit_load / 8] = 255;
			e->addr_load[i * e->size_load + (nb * 20 + j) *
				e->bit_load / 8 + 1] = 255;
			e->addr_load[i * e->size_load + (nb * 20 + j) *
				e->bit_load / 8 + 2] = 255;
		}
	}
	nb++;
	mlx_put_image_to_window(e->mlx, e->win, e->img_load, 0, e->height - 110);
	if (nb == 10)
		nb = delete_loading(e);
}

int			*fill_params(int x, int y, int width, int heigth)
{
	int *ret;

	if (!(ret = (int *)malloc(sizeof(int) * 4)))
		malloc_error();
	ret[0] = x;
	ret[1] = y;
	ret[2] = width;
	ret[3] = heigth;
	return (ret);
}

void		clear_menu(t_env *e)
{
	int i;
	int j;

	j = 0;
	while (j < 200)
	{
		i = 0;
		while (i < e->height)
		{
			mlx_pixel_put(e->mlx, e->win, j, i, 0x000000);
			i++;
		}
		j++;
	}
}
