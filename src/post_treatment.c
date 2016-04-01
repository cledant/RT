/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_treatment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpierron <tpierron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 09:11:12 by tpierron          #+#    #+#             */
/*   Updated: 2016/03/31 12:55:50 by tpierron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		black_and_white(t_env *e)
{
	int				x;
	int				y;
	unsigned char	tmp;

	x = -1;
	while (++x < e->width)
	{
		y = -1;
		while (++y < e->height)
		{
			if (e->menu->aa_button == 1)
				tmp = ((unsigned char)e->addr_aa[y * e->size + x * e->bit / 8] \
				+ (unsigned char)e->addr_aa[y * e->size + x * e->bit / 8 + 1] \
				+ (unsigned char)e->addr_aa[y * e->size + x * e->bit / 8 + 2]) \
				/ 3;
			else
				tmp = ((unsigned char)e->addr[y * e->size + x * e->bit / 8] \
				+ (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 1] \
				+ (unsigned char)e->addr[y * e->size + x * e->bit / 8 + 2]) / 3;
			e->addr_cpy[y * e->size + x * e->bit / 8] = tmp;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 1] = tmp;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 2] = tmp;
		}
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img_cpy, 200, 0);
}

static int	sepia_sub(int x, int y, int i, t_env *e)
{
	int		ret;
	char	*addr;

	addr = (e->menu->aa_button == 1) ? e->addr_aa : e->addr;
	if (i == 0)
	{
		ret = ((unsigned char)addr[y * e->size + x * e->bit / 8] * 0.131 + \
				(unsigned char)addr[y * e->size + x * e->bit / 8 + 1] * 0.534 +\
				(unsigned char)addr[y * e->size + x * e->bit / 8 + 2] * 0.272);
		return (ret);
	}
	if (i == 1)
	{
		ret = ((unsigned char)addr[y * e->size + x * e->bit / 8] * 0.168 + \
				(unsigned char)addr[y * e->size + x * e->bit / 8 + 1] * 0.686 +\
				(unsigned char)addr[y * e->size + x * e->bit / 8 + 2] * 0.349);
		return (ret);
	}
	else
	{
		ret = ((unsigned char)addr[y * e->size + x * e->bit / 8] * 0.189 + \
				(unsigned char)addr[y * e->size + x * e->bit / 8 + 1] * 0.769 +\
				(unsigned char)addr[y * e->size + x * e->bit / 8 + 2] * 0.393);
		return (ret);
	}
}

void		sepia(t_env *e)
{
	int x;
	int y;
	int tmp_b;
	int tmp_g;
	int tmp_r;

	x = -1;
	while (++x < e->width)
	{
		y = -1;
		while (++y < e->height)
		{
			tmp_b = sepia_sub(x, y, 0, e);
			tmp_g = sepia_sub(x, y, 1, e);
			tmp_r = sepia_sub(x, y, 2, e);
			tmp_b = (tmp_b > 255) ? 255 : tmp_b;
			tmp_g = (tmp_g > 255) ? 255 : tmp_g;
			tmp_r = (tmp_r > 255) ? 255 : tmp_r;
			e->addr_cpy[y * e->size + x * e->bit / 8] = tmp_b;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 1] = tmp_g;
			e->addr_cpy[y * e->size + x * e->bit / 8 + 2] = tmp_r;
		}
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img_cpy, 200, 0);
	mlx_do_sync(e->mlx);
}
